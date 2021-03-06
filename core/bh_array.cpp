/*
This file is part of Bohrium and copyright (c) 2012 the Bohrium
team <http://www.bh107.org>.

Bohrium is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation, either version 3
of the License, or (at your option) any later version.

Bohrium is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the
GNU Lesser General Public License along with Bohrium.

If not, see <http://www.gnu.org/licenses/>.
*/

#include <map>
#include <string>
#include <algorithm>
#include <tuple>
#include <iostream>
#include <sstream>

#include <bh_array.hpp>
#include <bh_memory.h>
#include <bh_pprint.hpp>

using namespace std;

/** Create a new base array.
 *
 * @param type The type of data in the array
 * @param nelements The number of elements
 * @param new_base The handler for the newly created base
 * @return Error code (BH_SUCCESS, BH_OUT_OF_MEMORY)
 */
bh_error bh_create_base(bh_type    type,
                        bh_index   nelements,
                        bh_base**  new_base)
{

    bh_base *base = (bh_base *) malloc(sizeof(bh_base));
    if(base == NULL)
        return BH_OUT_OF_MEMORY;
    base->type = type;
    base->nelem = nelements;
    base->data = NULL;
    *new_base = base;

    return BH_SUCCESS;
}

/** Destroy the base array.
 *
 * @param base  The base array in question
 */
void bh_destroy_base(bh_base**  base)
{
    bh_base *b = *base;
    free(b);
    b = NULL;
}

// Returns the label of this base array
// NB: generated a new label if necessary
static map<const bh_base*, unsigned int>label_map;
unsigned int bh_base::get_label() const
{
   if(label_map.find(this) == label_map.end())
       label_map[this] = label_map.size();
   return label_map[this];
}

ostream& operator<<(ostream& out, const bh_base& b)
{
    unsigned int label = b.get_label();
    out << "a" << label << "{dtype: " << bh_type_text(b.type) << ", nelem: " \
        << b.nelem << ", address: " << &b << "}";
    return out;
}

string bh_base::str() const
{
    stringstream ss;
    ss << *this;
    return ss.str();
}

void bh_view::insert_axis(bh_index dim, bh_index size, bh_index stride) {
    assert(dim <= ndim);
    if (dim == ndim) { // Appending
        this->shape[dim] = size;
        this->stride[dim] = stride;
    } else { // Inserting
        for (bh_index i=ndim-1; i >= 0; --i) {
            if (i >= dim) { // Move shape and stride one to the right
                this->shape[i+1] = this->shape[i];
                this->stride[i+1] = this->stride[i];
                if (i == dim) { // Insert the new dimension
                    this->shape[i] = size;
                    this->stride[i] = stride;
                }
            }
        }
    }
    ++ndim;
}

void bh_view::remove_axis(bh_index dim) {
    assert(1 < ndim);
    assert(dim < ndim);
    for (bh_index i=dim; i < ndim-1; ++i) {
        shape[i] = shape[i+1];
        stride[i] = stride[i+1];
    }
    --ndim;
}

void bh_view::transpose(int64_t axis1, int64_t axis2) {
    assert(0 <= axis1 and axis1 < ndim);
    assert(0 <= axis2 and axis2 < ndim);
    assert(not bh_is_constant(this));

    std::swap(shape[axis1], shape[axis2]);
    std::swap(stride[axis1], stride[axis2]);
}

vector<tuple<int64_t, int64_t, int64_t> > bh_view::python_notation() const
{
    //stride&shape&index for each dimension (in that order)
    vector<tuple<int64_t, int64_t, int64_t> > sns;
    for(int64_t i=0; i<this->ndim; ++i)
    {
        sns.push_back(make_tuple(this->stride[i], this->shape[i], i));
    }
    //Let's sort them such that the greatest strides comes first
    sort(sns.begin(), sns.end(), greater<tuple<int64_t, int64_t, int64_t> >());

    //Now let's compute start&end&stride of each dimension, which
    //makes up the python notation e.g. [2:4:1]
    vector<tuple<int64_t, int64_t, int64_t> > sne(sns.size());
    int64_t offset = this->start;
    for(size_t i=0; i<sns.size(); ++i)
    {
        const int64_t stride = std::get<0>(sns[i]);
        const int64_t shape  = std::get<1>(sns[i]);
        const int64_t index  = std::get<2>(sns[i]);

        int64_t start = 0;
        if (stride > 0)//avoid division by zero
            start = offset / stride;
        int64_t end = start + shape;
        offset -= start * stride;
        assert(offset >= 0);
        sne[index] = make_tuple(start, end, stride);
    }

    // If 'offset' wasn't reduced to zero, we have to append a singleton dimension
    // with the stride of 'offset'
    if (offset > 0) {
        sne.push_back(make_tuple(1, 2, offset));
    }

    /*
    //Find the contiguous strides, that is the stride of each dimension
    //assuming the view is contiguous.
    int64_t cont_stride = 1;
    for(int64_t i=sns.size()-1; i >= 0; --i)
    {
        int64_t stride = std::get<0>(sns[i]);
        int64_t shape  = std::get<1>(sns[i]);
        int64_t index  = std::get<2>(sns[i]);

        if(stride == cont_stride)
            std::get<2>(sne[index]) = -1;//Flag it as unnecessary
        cont_stride *= shape;
    }
    */
    return sne;
}

string bh_view::pprint(bool py_notation) const {
    stringstream ss;
    ss << "a" << base->get_label() << "[";
    if (bh_is_constant(this)) {
        ss << "CONST";
    } else if (py_notation) {
        const vector<tuple<int64_t, int64_t, int64_t> > sne = python_notation();
        for(size_t i=0; i<sne.size(); ++i)
        {
            int64_t start  = std::get<0>(sne[i]);
            int64_t end    = std::get<1>(sne[i]);
            int64_t stride = std::get<2>(sne[i]);
            ss << start << ":" << end << ":" << stride;
            if(i < sne.size()-1)//Not the last iteration
                ss << ",";
        }
    } else {
        ss << "start: " << start;
        ss << ", ndim: " << ndim;
        ss << ", shape: " << pprint_carray(shape, ndim);
        ss << ", stride: " << pprint_carray(stride, ndim);
        ss << ", base: " << base;
    }
    ss << "]";
    return ss.str();
}

ostream& operator<<(ostream& out, const bh_view& v) {
    out << v.pprint(true);
    return out;
}

inline int64_t gcd(int64_t a, int64_t b)
{
    if (b==0)
        return a;
    int64_t c = a % b;
    while(c != 0)
    {
        a = b;
        b = c;
        c = a % b;
    }
    return b;
}

/* Returns the simplest view (fewest dimensions) that access
 * the same elements in the same pattern
 *
 * @view The view
 * @return The simplified view
 */
bh_view bh_view_simplify(const bh_view& view)
{
    bh_view res;
    res.base = view.base;
    res.ndim = 0;
    res.start = view.start;
    bh_intp i = 0;
    while (view.shape[i] == 1 && i < view.ndim-1)
        ++i;
    res.shape[0] = view.shape[i];
    res.stride[0] = view.stride[i];
    for (++i; i < view.ndim; ++i)
    {
        if (view.shape[i] == 0)
        {
            res.ndim = 1;
            res.shape[0] = 0;
            return res;
        }
        if (view.shape[i] == 1)
            continue;
        if (view.shape[i]*view.stride[i] == res.stride[res.ndim])
        {
            res.shape[res.ndim] *= view.shape[i];
            res.stride[res.ndim] = view.stride[i];
        } else {
            ++res.ndim;
            res.shape[res.ndim]  = view.shape[i];
            res.stride[res.ndim] = view.stride[i];
        }
    }
    if (res.ndim == 0 || res.shape[res.ndim] > 1)
        ++res.ndim;
    return res;
}

/* Simplifies the given view down to the given shape.
 * If that is not possible an std::invalid_argument exception is thrown
 *
 * @view The view
 * @return The simplified view
 */
bh_view bh_view_simplify(const bh_view& view, const std::vector<bh_index>& shape)
{
    assert(false); // TODO: complete rewrite under the assumption the cleandim has been run
    if (view.ndim < (bh_intp)shape.size())
    {
        std::stringstream ss;
        ss << "Can not simplify to more dimensions: ";
        ss << "shape: " << shape << " view: " << view;
        throw std::invalid_argument(ss.str());
    }
    bh_view res;
    res.base = view.base;
    res.ndim = 0;
    res.start = view.start;
    bh_intp i = 0;
    while (view.shape[i] == 1 && i < view.ndim-1)
        ++i;
    res.shape[0] = view.shape[i];
    res.stride[0] = view.stride[i];
    for (++i; i < view.ndim; ++i)
    {
        if (shape[res.ndim] == 0)
        {
            if (view.shape[i] != 0)
            {
                continue;
            } else {
                res.shape[res.ndim++] = 0;
                return res;
            }
        }
        if ((bh_intp)shape.size() == res.ndim)
        {
            if (view.shape[i] == 1)
            {
                continue;
            } else {
                std::stringstream ss;
                ss << "Can not remove trailing dimensions of size > 1: ";
                ss << "shape: " << shape << " view: " << view;
                throw std::invalid_argument(ss.str());
            }
        }
        if (view.shape[i-1] > shape[res.ndim])
        {
            std::stringstream ss;
            ss << "Can not simplify to lower dimension size: ";
            ss << "shape: " << shape << " view: " << view;
            throw std::invalid_argument(ss.str());
        }
        if (view.shape[i-1] == shape[res.ndim])
        {
            res.shape[++res.ndim]  = view.shape[i];
            res.stride[res.ndim] = view.stride[i];
            continue;
        }
        if (view.shape[i] == 1)
            continue;
        if (view.shape[i]*view.stride[i] == res.stride[res.ndim])
        {
            res.shape[res.ndim] *= view.shape[i];
            res.stride[res.ndim] = view.stride[i];
        } else {
            res.shape[++res.ndim]  = view.shape[i];
            res.stride[res.ndim] = view.stride[i];
        }
    }
    if (res.ndim == 0 || res.shape[res.ndim] > 1)
        ++res.ndim;
    if (res.ndim != (bh_intp)shape.size())
    {
        std::stringstream ss;
        ss << "Can not simplify to given shape: ";
        ss << "shape: " << shape << " view: " << view;
        throw std::invalid_argument(ss.str());
    }

    return res;
}

/* Number of non-broadcasted elements in a given view
 *
 * @view    The view in question.
 * @return  Number of elements.
 */
bh_index bh_nelements_nbcast(const bh_view *view)
{
    bh_index res = 1;
    for (int i = 0; i < view->ndim; ++i)
    {
        if(view->stride[i] != 0)
            res *= view->shape[i];
    }
    return res;
}

/* Number of element in a given shape
 *
 * @ndim     Number of dimentions
 * @shape[]  Number of elements in each dimention.
 * @return   Number of element operations
 */
bh_index bh_nelements(bh_intp ndim,
                      const bh_index shape[])
{
    assert (ndim > 0);
    bh_index res = 1;
    for (int i = 0; i < ndim; ++i)
    {
        res *= shape[i];
    }
    return res;
}

bh_index bh_nelements(const bh_view& view)
{
    return bh_nelements(view.ndim,view.shape);
}

/* Size of the base array in bytes
 *
 * @base    The base in question
 * @return  The size of the base array in bytes
 */
bh_index bh_base_size(const bh_base *base)
{
    return base->nelem * bh_type_size(base->type);
}


/* Set the view stride to contiguous row-major
 *
 * @view    The view in question
 * @return  The total number of elements in view
 */
bh_intp bh_set_contiguous_stride(bh_view *view)
{
    bh_intp s = 1;
    for(bh_intp i=view->ndim-1; i >= 0; --i)
    {
        view->stride[i] = s;
        s *= view->shape[i];
    }
    return s;
}

/* Updates the view with the complete base
 *
 * @view    The view to update (in-/out-put)
 * @base    The base assign to the view
 * @return  The total number of elements in view
 */
void bh_assign_complete_base(bh_view *view, bh_base *base)
{
    view->base = base;
    view->ndim = 1;
    view->start = 0;
    view->shape[0] = view->base->nelem;
    view->stride[0] = 1;
}

/* Set the data pointer for the view.
 * Can only set to non-NULL if the data ptr is already NULL
 *
 * @view   The view in question
 * @data   The new data pointer
 * @return Error code (BH_SUCCESS, BH_ERROR)
 */
bh_error bh_data_set(bh_view* view, bh_data_ptr data)
{
    bh_base* base;

    if(view == NULL)
    {
        fprintf(stderr, "Attempt to set data pointer for a null view\n");
        return BH_ERROR;
    }

    base = bh_base_array(view);

    if(base->data != NULL && data != NULL)
    {
        fprintf(stderr, "Attempt to set data pointer an array with existing data pointer\n");
        return BH_ERROR;
    }

    base->data = data;

    return BH_SUCCESS;
}

/* Get the data pointer for the view.
 *
 * @view    The view in question
 * @result  Output data pointer
 * @return  Error code (BH_SUCCESS, BH_ERROR)
 */
bh_error bh_data_get(bh_view* view, bh_data_ptr* result)
{
    bh_base* base;

    if(view == NULL)
    {
        fprintf(stderr, "Attempt to get data pointer for a null view\n");
        return BH_ERROR;
    }

    base = bh_base_array(view);

    *result = base->data;

    return BH_SUCCESS;
}

/* Allocate data memory for the given base if not already allocated.
 * For convenience, the base is allowed to be NULL.
 *
 * @base    The base in question
 * @return  Error code (BH_SUCCESS, BH_ERROR, BH_OUT_OF_MEMORY)
 */
bh_error bh_data_malloc(bh_base* base)
{
    bh_intp bytes;

    if(base == NULL)
        return BH_SUCCESS;

    if(base->data != NULL)
        return BH_SUCCESS;

    bytes = bh_base_size(base);
    if(bytes == 0)//We allow zero sized arrays.
        return BH_SUCCESS;

    if(bytes < 0)
        return BH_ERROR;

    base->data = bh_memory_malloc(bytes);
    if(base->data == NULL)
    {
        int errsv = errno;//mmap() sets the errno.
        printf("bh_data_malloc() could not allocate a data region. "
               "Returned error code: %s.\n", strerror(errsv));
        return BH_OUT_OF_MEMORY;
    }

    return BH_SUCCESS;
}

/* Frees data memory for the given view.
 * For convenience, the view is allowed to be NULL.
 *
 * @base    The base in question
 * @return  Error code (BH_SUCCESS, BH_ERROR)
 */
bh_error bh_data_free(bh_base* base)
{
    bh_intp bytes;

    if(base == NULL)
        return BH_SUCCESS;

    if(base->data == NULL)
        return BH_SUCCESS;

    bytes = bh_base_size(base);

    if(bh_memory_free(base->data, bytes) != 0)
    {
        int errsv = errno;//munmmap() sets the errno.
        printf("bh_data_free() could not free a data region. "
               "Returned error code: %s.\n", strerror(errsv));
        return BH_ERROR;
    }
    base->data = NULL;
    return BH_SUCCESS;
}



/* Determines whether the base array is a scalar.
 *
 * @view The view
 * @return The boolean answer
 */
bool bh_is_scalar(const bh_view* view)
{
    return bh_nelements(*view) == 1;
}

/* Determines whether the operand is a constant
 *
 * @o The operand
 * @return The boolean answer
 */
bool bh_is_constant(const bh_view* o)
{
    return (o->base == NULL);
}

/* Flag operand as a constant
 *
 * @o      The operand
 */
void bh_flag_constant(bh_view* o)
{
    o->base = NULL;
}

/* Determines whether two views have same shape.
 *
 * @a The first view
 * @b The second view
 * @return The boolean answer
 */
bool bh_view_same_shape(const bh_view *a, const bh_view *b)
{
    if(a->ndim != b->ndim)
        return false;
    for(int i=0; i<a->ndim; ++i)
    {
        if(a->shape[i] != b->shape[i])
            return false;
    }
    return true;
}

/* Determines whether two views are identical and points
 * to the same base array.
 *
 * @a The first view
 * @b The second view
 * @return The boolean answer
 */
bool bh_view_same(const bh_view *a, const bh_view *b)
{
    if(bh_is_constant(a) || bh_is_constant(b))
        return false;
    return *a == *b;
}

/* Determines whether a view is contiguous
 *
 * @a The view
 * @return The boolean answer
 */
bool bh_is_contiguous(const bh_view* a)
{
    if (bh_is_constant(a)) {
        return false;
    }

    bh_index weight = 1;
    for(bh_index dim = a->ndim-1; dim >= 0; --dim) {
        if (a->stride[dim] != weight) {
            return false;
        }

        weight *= a->shape[dim];
    }
    return true;
}

/* Determines whether two views are aligned and points
 * to the same base array.
 *
 * @a The first view
 * @b The second view
 * @return The boolean answer
 */
bool bh_view_aligned(const bh_view *a, const bh_view *b)
{
    if(bh_is_constant(a) || bh_is_constant(b))
        return true;
    bh_view sa = bh_view_simplify(*a);
    bh_view sb = bh_view_simplify(*b);
    return sa == sb;
}

/* Determines whether two views are aligned, points
 * to the same base array, and have same shape.
 *
 * @a The first view
 * @b The second view
 * @return The boolean answer
 */
bool bh_view_aligned_and_same_shape(const bh_view *a, const bh_view *b)
{
    if(a->ndim != b->ndim)
        return false;
    if(not bh_view_aligned(a, b))
        return false;

    for(int i=0; i<a->ndim; ++i)
    {
        if(a->shape[i] != b->shape[i])
            return false;
    }
    return true;
}

/* Determines whether two views access some of the same data points or not
 * NB: This functions may return True on two non-overlapping views.
 *     But will always return False on overlapping views.
 *
 * @a The first view
 * @b The second view
 * @return The boolean answer
 */
bool bh_view_disjoint(const bh_view *a, const bh_view *b)
{
    // TODO: In order to fixed BUG like <https://github.com/bh107/bohrium/issues/178>, we say that sharing
    //       the same base makes the views overlapping for now.
    return bh_base_array(a) != bh_base_array(b);
/*


    if (bh_is_constant(a) || bh_is_constant(b)) // One is a constant
        return true;
    if(bh_base_array(a) != bh_base_array(b)) //different base
        return true;
    if(a->ndim != b->ndim) // we dont handle views of differenr dimensions yet
        return false;

    int64_t astart = a->start;
    int64_t bstart = b->start;
    int64_t stride = 1;
    for (int i = 0; i < a->ndim; ++i)
    {
        //Negative strides is always an overlap
        if(a->stride[i] < 0 or b->stride[i] < 0)
            return false;

        stride = gcd(a->stride[i], b->stride[i]);
        if (stride == 0) // stride is 0 in both views: dimension is virtual
            continue;
        int64_t as = astart / stride;
        int64_t bs = bstart / stride;
        int64_t ae = as + a->shape[i] * (a->stride[i]/stride);
        int64_t be = bs + b->shape[i] * (b->stride[i]/stride);
        if (ae < bs || be < as)
            return true;
        astart %= stride;
        bstart %= stride;
    }
    return stride > 1 && a->start % stride != b->start % stride;
*/
}

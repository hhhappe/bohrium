/*
This file is part of cphVB and copyright (c) 2012 the cphVB team:
http://cphvb.bitbucket.org

cphVB is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as 
published by the Free Software Foundation, either version 3 
of the License, or (at your option) any later version.

cphVB is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the 
GNU Lesser General Public License along with cphVB. 

If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __CPHVB_BRIDGE_CPP
#define __CPHVB_BRIDGE_CPP
#include "cphvb.h"

namespace cphvb {

template <typename T>
class Vector {

public:
    cphvb_array* array;

    Vector( Vector const& vector );
    Vector( int d0 );
    Vector( int d0, int d1 );

    // Operators: =, [], (), -> must be nonstatic member functions.
    // These are defined in cphvb_cppb_vector.hpp 
    // The remaining are defined externally in *_operators.hpp
    Vector& operator=( const T rhs );
    Vector& operator=( Vector & rhs );

};

}

#include "cphvb_cppb_state.hpp"
#include "cphvb_cppb_traits.hpp"
#include "cphvb_cppb_operators.hpp"
#include "cphvb_cppb_functions.hpp"
#include "cphvb_cppb_vector.hpp"

#endif

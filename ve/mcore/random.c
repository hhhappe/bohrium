/*
 * Copyright 2011 Simon A. F. Lund <safl@safl.dk>
 *
 * This file is part of cphVB.
 *
 * cphVB is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cphVB is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cphVB. If not, see <http://www.gnu.org/licenses/>.
 */
#include <cphvb.h>
#include "cphvb_ve_mcore.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif
#include <pthread.h>
#include <limits.h>

// We use the same Mersenne Twister implementation as NumPy
typedef struct
{
    unsigned long key[624];
    int pos;
} rk_state;

/* Magic Mersenne Twister constants */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL
#define UPPER_MASK 0x80000000UL
#define LOWER_MASK 0x7fffffffUL
#define RK_STATE_LEN 624

/* Slightly optimised reference implementation of the Mersenne Twister */
unsigned long
rk_random(rk_state *state)
{
    unsigned long y;

    if (state->pos == RK_STATE_LEN) {
        int i;

        for (i = 0; i < N - M; i++) {
            y = (state->key[i] & UPPER_MASK) | (state->key[i+1] & LOWER_MASK);
            state->key[i] = state->key[i+M] ^ (y>>1) ^ (-(y & 1) & MATRIX_A);
        }
        for (; i < N - 1; i++) {
            y = (state->key[i] & UPPER_MASK) | (state->key[i+1] & LOWER_MASK);
            state->key[i] = state->key[i+(M-N)] ^ (y>>1) ^ (-(y & 1) & MATRIX_A);
        }
        y = (state->key[N - 1] & UPPER_MASK) | (state->key[0] & LOWER_MASK);
        state->key[N - 1] = state->key[M - 1] ^ (y >> 1) ^ (-(y & 1) & MATRIX_A);

        state->pos = 0;
    }
    y = state->key[state->pos++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}
int8_t
rk_int8(rk_state *state)
{
    return (int8_t)(rk_random(state) & 0x7f);
}

int16_t
rk_int16(rk_state *state)
{
    return (int16_t)(rk_random(state) & 0x7fff);
}

int32_t
rk_int32(rk_state *state)
{
    return rk_random(state) & 0x7fffffff;
}

int64_t
rk_int64(rk_state *state)
{
    int64_t res = rk_random(state) & 0x7fffffff;
    res = (res << 32) | rk_random(state);
    return res;
}

uint8_t
rk_uint8(rk_state *state)
{
    return (uint8_t)(rk_random(state) & 0xff);
}

uint16_t
rk_uint16(rk_state *state)
{
    return (uint16_t)(rk_random(state) & 0xffff);
}

uint32_t
rk_uint32(rk_state *state)
{
    return rk_random(state);
}

uint64_t
rk_uint64(rk_state *state)
{
    uint64_t res = rk_random(state); 
    res = (res << 32) | rk_random(state);
    return res;
}

float
rk_float(rk_state *state)
{
    return rk_random(state) * 2.3283064365387e-10;
}

double
rk_double(rk_state *state)
{
    /* shifts : 67108864 = 0x4000000, 9007199254740992 = 0x20000000000000 */
    long a = rk_random(state) >> 5, b = rk_random(state) >> 6;
    return (a * 67108864.0 + b) / 9007199254740992.0;
}
void
rk_seed(unsigned long seed, rk_state *state)
{
    int pos;
    seed &= 0xffffffffUL;

    /* Knuth's PRNG as used in the Mersenne Twister reference implementation */
    for (pos = 0; pos < RK_STATE_LEN; pos++) {
        state->key[pos] = seed;
        seed = (1812433253UL * (seed ^ (seed >> 30)) + pos + 1) & 0xffffffffUL;
    }
    state->pos = RK_STATE_LEN;
}
/* Thomas Wang 32 bits integer hash function */
unsigned long
rk_hash(unsigned long key)
{
    key += ~(key << 15);
    key ^=  (key >> 10);
    key +=  (key << 3);
    key ^=  (key >> 6);
    key += ~(key << 11);
    key ^=  (key >> 16);
    return key;
}
int
rk_initseed(rk_state *state)
{
#ifdef _WIN32
	time_t ltime;
	time(&ltime);
	//Essentially time_t is a int64
	rk_seed(rk_hash(GetCurrentProcessId()) ^ rk_hash(ltime), state);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    rk_seed(rk_hash(getpid()) ^ rk_hash(tv.tv_sec) ^ rk_hash(tv.tv_usec), state);
#endif
    return 0;
}

//Thread function and it's ID.
typedef struct
{
    int myid;
    cphvb_intp nthds;
    cphvb_intp size;
    cphvb_type type;
    void *data;
}thd_id;

void *thd_do_random(void *msg)
{
    thd_id *id = (thd_id *) msg;
    int myid           = id->myid;
    cphvb_intp size    = id->size;
    cphvb_intp nthds   = id->nthds;

    cphvb_intp length = size / nthds; // Find this thread's length of work.
    cphvb_intp start = myid * length; // Find this thread's start block.
    if(myid == nthds-1)
        length += size % nthds;       // The last thread gets the remainder.

    rk_state state;
    rk_initseed(&state);
    
    switch (id->type)
    {
    	case CPHVB_INT8:
		{
			cphvb_int8* data = (cphvb_int8*)id->data;
			for(cphvb_intp i=start; i<start+length; ++i)
				data[i] = rk_int8(&state);
		}
		break;

    	case CPHVB_INT16:
		{
			cphvb_int16* data = (cphvb_int16*)id->data;
			for(cphvb_intp i=start; i<start+length; ++i)
				data[i] = rk_int16(&state);
		}
		break;

    	case CPHVB_INT32:
		{
			cphvb_int32* data = (cphvb_int32*)id->data;
			for(cphvb_intp i=start; i<start+length; ++i)
				data[i] = rk_int32(&state);
		}
		break;

    	case CPHVB_INT64:
		{
			cphvb_int64* data = (cphvb_int64*)id->data;
			for(cphvb_intp i=start; i<start+length; ++i)
				data[i] = rk_int64(&state);
		}
		break;
		
		case CPHVB_UINT8:
		{
			cphvb_uint8* data = (cphvb_uint8*)id->data;
			for(cphvb_intp i=start; i<start+length; ++i)
				data[i] = rk_uint8(&state);
		}
		break;

    	case CPHVB_UINT16:
		{
			cphvb_uint16* data = (cphvb_uint16*)id->data;
			for(cphvb_intp i=start; i<start+length; ++i)
				data[i] = rk_uint16(&state);
		}
		break;

    	case CPHVB_UINT32:
		{
			cphvb_uint32* data = (cphvb_uint32*)id->data;
			for(cphvb_intp i=start; i<start+length; ++i)
				data[i] = rk_uint32(&state);
		}
		break;

    	case CPHVB_UINT64:
		{
			cphvb_uint64* data = (cphvb_uint64*)id->data;
			for(cphvb_intp i=start; i<start+length; ++i)
				data[i] = rk_uint64(&state);
		}
		break;

    	case CPHVB_FLOAT32:
		{
			cphvb_float32* data = (cphvb_float32*)id->data;
			for(cphvb_intp i=start; i<start+length; ++i)
				data[i] = rk_float(&state);
		}
		break;

    	case CPHVB_FLOAT64:
		{
			cphvb_float64* data = (cphvb_float64*)id->data;
			for(cphvb_intp i=start; i<start+length; ++i)
				data[i] = rk_double(&state);
		}
		break;

	}		
	
    return NULL;
}
//Implementation of the user-defined funtion "random". Note that we
//follows the function signature defined by cphvb_userfunc_impl.
cphvb_error cphvb_random(cphvb_userfunc *arg, void* ve_arg)
{
    cphvb_random_type *a = (cphvb_random_type *) arg;
    cphvb_array *ary = a->operand[0];
    cphvb_intp size = cphvb_nelements(ary->ndim, ary->shape);
    cphvb_intp nthds = 1;

    //Make sure that the array memory is allocated.
    if(cphvb_data_malloc(ary) != CPHVB_SUCCESS)
        return CPHVB_OUT_OF_MEMORY;
        
    switch(ary->type)
    {
    	case CPHVB_INT8:
    	case CPHVB_INT16:
    	case CPHVB_INT32:
    	case CPHVB_INT64:
    	case CPHVB_UINT8:
    	case CPHVB_UINT16:
    	case CPHVB_UINT32:
    	case CPHVB_UINT64:
    	case CPHVB_FLOAT32:
    	case CPHVB_FLOAT64:
    		break;
    	
    	default:
	        return CPHVB_TYPE_NOT_SUPPORTED;
    }

    //We divide the blocks between the threads.
    {//Find number of threads to use.
        char *env = getenv("CPHVB_NUM_THREADS");
        if(env != NULL)
            nthds = atoi(env);

        if(nthds > size)
            nthds = size;//Minimum one block per thread.
        if(nthds > 32)
        {
            printf("CPHVB_NUM_THREADS greater than 32!\n");
            nthds = 32;//MAX 32 thds.
        }
    }

    //Start threads.
    thd_id ids[32];
    pthread_t tid[32];
    for(cphvb_intp i=0; i<nthds; ++i)
    {
        ids[i].myid        = i;
        ids[i].nthds       = nthds;
        ids[i].size        = size;
        ids[i].data        = ary->data;
        ids[i].type        = ary->type;
        pthread_create(&tid[i], NULL, thd_do_random, (void *) (&ids[i]));
    }
    //Wait for threads to complete
    for(cphvb_intp i=0; i<nthds; ++i)
        pthread_join(tid[i], NULL);

    return CPHVB_SUCCESS;
}
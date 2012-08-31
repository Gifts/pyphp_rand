//#include "stdio.h"
#include "php_rand.h"
//#include "php_lcg.h"


#define N             MT_N                 /* length of state vector */
#define M             (397)                /* a period parameter */
#define hiBit(u)      ((u) & 0x80000000U)  /* mask all but highest   bit of u */
#define loBit(u)      ((u) & 0x00000001U)  /* mask all but lowest    bit of u */
#define loBits(u)     ((u) & 0x7FFFFFFFU)  /* mask     the highest   bit of u */
#define mixBits(u, v) (hiBit(u)|loBits(v)) /* move hi bit of u to hi bit of v */

#define twist(m,u,v)  (m ^ (mixBits(u,v)>>1) ^ ((unsigned int)(-(unsigned int)(loBit(u))) & 0x9908b0dfU))

static inline void php_mt_initialize(unsigned int seed, unsigned int *state)
{
	/* Initialize generator state with seed
	   See Knuth TAOCP Vol 2, 3rd Ed, p.106 for multiplier.
	   In previous versions, most significant bits (MSBs) of the seed affect
	   only MSBs of the state array.  Modified 9 Jan 2002 by Makoto Matsumoto. */

	register unsigned int *s = state;
	register unsigned int *r = state;
	int i = 1;

	*s++ = seed & 0xffffffffU;
	for( ; i < N; ++i ) {
		*s++ = ( 1812433253U * ( *r ^ (*r >> 30) ) + i ) & 0xffffffffU;
		r++;
	}
}

static inline void php_mt_reload()
{
	/* Generate N new values in state
	   Made clearer and faster by Matthew Bellew (matthew.bellew@home.com) */

	register unsigned int *state2 = state;
	register unsigned int *p = state2;
	register int i;
    left = 0;
	for (i = N - M; i--; ++p)
		*p = twist(p[M], p[0], p[1]);
	for (i = M; --i; ++p)
		*p = twist(p[M-N], p[0], p[1]);
	*p = twist(p[M-N], p[0], state2[0]);
	left = N;
	next = state2;
}

int php_mt_srand(unsigned int seed)
{
	/* Seed the generator with a simple uint32 */
	php_mt_initialize(seed, state);
	php_mt_reload();
	/* Seed only once */
	mt_rand_is_seeded = 1;
	return 1;
}


long php_mt_rand()
{
	/* Pull a 32-bit integer from the generator state
	   Every other access function simply transforms the numbers extracted here */

	register unsigned int s1;

    /*if (  !mt_rand_is_seeded)
    {
        php_mt_srand(321); // TODO: GENERATE_SEED());
    }*/

	if (left == 0) {
		php_mt_reload();
	}
	--left;
	s1 = *next++;

	s1 ^= (s1 >> 11);
	s1 ^= (s1 <<  7) & 0x9d2c5680U;
	s1 ^= (s1 << 15) & 0xefc60000U;
	return (long) (( s1 ^ (s1 >> 18)) >> 1);
}

long detemper(long x)
{
   x = x << 1;
   x ^= (x >> 18);
   x ^= (x << 15) & 0xEFC60000;
   x ^= (x << 7) & 0x1680;
   x ^= (x << 7) & 0xC4000;
   x ^= (x << 7) & 0xD200000;
   x ^= (x << 7) & 0x90000000;
   x ^= (x >> 11) & 0xFFC00000;
   x ^= (x >> 11) & 0x3FF800;
   x ^= (x >> 11) & 0x7FF;

   return x;
}

long php_mt_rand_a_b(unsigned int a, unsigned int b)
{
    long number = php_mt_rand();
    RAND_RANGE(number, a, b, PHP_RAND_MAX);
    return number;
}

#ifndef PHP_RAND_H
#define	PHP_RAND_H

#include <stdbool.h>
#define php_int32 int
//#define zend_bool bool

#include <stdlib.h>

#define MT_N 624

/* rand.c */
unsigned int   state[MT_N+1];  /* state vector + 1 extra to not violate ANSI C */
unsigned int   *next;       /* next random value is computed from here */
int      left;        /* can *next++ this many times before reloading */

unsigned int rand_seed; /* Seed for rand(), in ts version */

bool rand_is_seeded; /* Whether rand() has been seeded */
bool mt_rand_is_seeded; /* Whether mt_rand() has been seeded */


/* System Rand functions */
#ifndef RAND_MAX
#define RAND_MAX (1<<15)
#endif
/* In ZTS mode we rely on rand_r() so we must use RAND_MAX. */
#define PHP_RAND_MAX 2147483647

#define RAND_RANGE(__n, __min, __max, __tmax) \
    (__n) = (__min) + (long) ((double) ( (double) (__max) - (__min) + 1.0) * ((__n) / ((__tmax) + 1.0)))

/* MT Rand */
#define PHP_MT_RAND_MAX ((long) (0x7FFFFFFF)) /* (1<<31) - 1 */

/*#ifdef PHP_WIN32
#define GENERATE_SEED() (((long) (time(0) * GetCurrentProcessId())) ^ ((long) (1000000.0 * php_combined_lcg(TSRMLS_C))))
#else
#define GENERATE_SEED() (((long) (time(0) * getpid())) ^ ((long) (1000000.0 * php_combined_lcg(TSRMLS_C))))
#endif*/

int php_mt_srand(unsigned int seed);
long php_mt_rand();
long php_mt_rand_a_b(unsigned int a, unsigned int b);
long detemper(long x);

#endif	/* PHP_RAND_H */

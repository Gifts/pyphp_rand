#coding: utf8

cdef extern from "php_rand.h":
    long php_mt_rand() nogil
    long php_mt_rand_a_b(unsigned int a, unsigned int b) nogil
    void php_mt_srand(unsigned int seed) nogil
    long detemper(long x) nogil
    int PHP_MT_RAND_MAX

__author__ = 'gifts'

cpdef long mt_rand_orig() nogil:
    return php_mt_rand()

cpdef long mt_rand_ab(unsigned int a, unsigned int b) nogil:
    return php_mt_rand_a_b(a, b)

cpdef mt_rand(a=None,b=None):
    if a is None:
        return php_mt_rand()
    else:
        return mt_rand_ab(a,b)

cpdef int mt_srand(unsigned int val=0) nogil:
    php_mt_srand(val)

def test_mt():
    cdef int i
    cdef int a
    mt_srand(12345)
    for i in xrange(1000000):
        a += mt_rand()
    return a

def brute_string(char* alpha, char* target, int cnt):
    cdef int i
    cdef int a_len = len(alpha) - 1
    cdef int STEP = 10000000
    cdef int seed_shift
    cdef int stopit

    with nogil:
        # For-loop
        seed_shift = -STEP
        while seed_shift < PHP_MT_RAND_MAX:
            seed_shift += STEP

            for i in xrange(STEP):
                mt_srand(i+seed_shift)
                stopit = 0
                while stopit < cnt and alpha[mt_rand_ab(0, a_len)]==target[stopit]:
                    stopit += 1

                if stopit == cnt:
                    with gil:
                        return 'OK', seed_shift + i
                        #yield 'OK', seed_shift + i
                        #raise StopIteration()
            #with gil:
            #    yield 'NO', seed_shift
#TODO: SEGFAULT error using generator

def detemp(val):
    return detemper(val)
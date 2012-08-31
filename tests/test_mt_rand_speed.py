#coding: utf8

__author__ = 'gifts'

import php_rand

for i in xrange(10000000):
    php_rand.mt_srand(i)
    php_rand.mt_rand()

print php_rand.mt_rand()
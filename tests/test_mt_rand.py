#!/usr/bin/env python
#coding: utf8

import unittest
import php_rand

__author__ = 'gifts'

class MyTestCase(unittest.TestCase):
    def test_same_srand(self):
        php_rand.mt_srand(12345)
        a = [php_rand.mt_rand() for i in xrange(10)]

        php_rand.mt_srand(12345)
        b = [php_rand.mt_rand() for i in xrange(10)]

        self.assertEqual(a, b)

    def test_different_srand(self):
        php_rand.mt_srand(12345)
        a = [php_rand.mt_rand() for i in xrange(10)]

        php_rand.mt_srand(12346)
        b = [php_rand.mt_rand() for i in xrange(10)]

        self.assertNotEqual(a, b)

    def test_with_php(self):
        php_result = [1863022934, 1105767797, 2076010745, 1928709656,
                      559367964, 622044451, 1926800759, 1672524053,
                      1332912347, 2000644112]

        php_rand.mt_srand(123456)
        my_result = [php_rand.mt_rand() for i in xrange(10)]

        self.assertEqual(php_result, my_result)

    def test_with_php_range(self):
        php_result = [76, 54, 1, 37, 99, 7, 32, 93, 91, 95]

        php_rand.mt_srand(1234567)
        my_result = [php_rand.mt_rand_ab(1, 100) for i in xrange(10)]

        self.assertEqual(php_result, my_result)

if __name__ == '__main__':
    unittest.main()

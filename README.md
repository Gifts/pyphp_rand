Cython implementation of mt_rand and mt_srand functions

Installation
============

<code>
pip install Cython<br>
python setup.py install<br>
</code>

Speed tests
===========

<code>$ time php test_rand.php<br>
1706479894<br>
real	0m39.513s<br>
user	0m39.377s<br>
sys	0m0.007s<br>
<br>
$ time python test_mt_rand_speed.py<br>
1706479894<br>
real	0m18.820s<br>
user	0m18.259s<br>
sys	0m0.063s<br>
</code>
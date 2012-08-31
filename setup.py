#coding: utf8

from distutils.core import setup
from distutils.extension import Extension
try:
    from Cython.Distutils import build_ext
except ImportError:
    print 'Cython package should be installed'
    exit(1)


setup(
    name='MT_RAND stream bruteforce',
    version='0.1',
    packages=[''],
    url='http://github.com/Gifts/mt_rand',
    license='MIT License',
    author='gifts',
    author_email='gifts.antichat@gmail.com',
    description='', requires=['Cython'],
    cmdclass= {'build_ext': build_ext},
    ext_modules = [
        #Extension('mt_rand', ["mt_rand.pyx"])
        Extension('php_rand', ["php_rand/mt_rand.pyx", "php_rand/rand.c"],
            include_dirs=["php_rand/"],
            extra_compile_args=['-O3']
        )
    ]
)

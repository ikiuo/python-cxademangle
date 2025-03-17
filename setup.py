#!/usr/bin/env python3

import os
from setuptools import setup, Extension


def getenv(name, defval=None):
    if name in os.environ:
        return os.environ[name]
    return defval


def bool_getenv(name):
    return getenv(name, '').lower() in ('ok', 'true', 'yes')


DEBUG = bool_getenv('DEBUG')

MAJOR_VERSION = 0
MINOR_VERSION = 1
DEBUG_VERSION = 0
VERSION = '%d.%d.%d' % (MAJOR_VERSION, MINOR_VERSION, DEBUG_VERSION)

DEFINE_MACROS = [
    ('MAJOR_VERSION', MAJOR_VERSION),
    ('MINOR_VERSION', MINOR_VERSION),
    ('DEBUG_VERSION', DEBUG_VERSION),
]
UNDEF_MACROS = []

EXTRA_COMPILE_ARGS = [
    '-W',
    '-Wall',
    '-Wextra',
]

if DEBUG:
    DEFINE_MACROS.append(('DEBUG', 1))
    UNDEF_MACROS.append('NDEBUG')
    EXTRA_COMPILE_ARGS.append('-O0')

MODULE_NAME = 'cxademangle'
EXTMOD_NAME = MODULE_NAME
SOURCES = ['demangle.cpp']
PACKAGES = None

setup(name=MODULE_NAME, version=VERSION, packages=PACKAGES,
      ext_modules=[Extension(name=EXTMOD_NAME, sources=SOURCES)])

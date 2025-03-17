# GNUmakefile

DEBUG ?= false
DISTUTILS ?= false

ifeq ($(DEBUG), true)
BUILD_OPT = --debug
endif

PYTHON ?= python3

ENVPARAM = DEBUG=$(DEBUG)

MODNAME = cxademangle

.PHONY: all clean install

all:
	@echo "Usage: make install"

install:
	env $(ENVPARAM) $(PYTHON) -m pip wheel .
	env $(ENVPARAM) $(PYTHON) -m pip install --user cxademangle-*.whl

clean:
	rm -rf build dist $(MODNAME).egg-info
	rm -f *.dll *.so *.whl *.pyc *~

-include GNUmakefile.local

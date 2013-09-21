SUBDIRS = utils regression unit stress

tests = unit_tests fast_regression

if USE_PYTHON
tests += with_bindings_regression
endif

$(tests):
	./run.sh $@

check-am: $(tests)

.PHONY: $(tests)

dist_noinst_SCRIPTS = run.sh unit_tests fast_regression long_regression root_regression with_bindings_regression
EXTRA_DIST = run.sh unit_tests fast_regression long_regression root_regression with_bindings_regression

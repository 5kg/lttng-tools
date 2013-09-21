SUBDIRS = utils regression unit stress

TESTS = unit_tests fast_regression

if USE_PYTHON
TESTS += with_bindings_regression
endif

if HAVE_UST_DYNAMIC_INSTRUMENT
TESTS += dynamic_instrument_regression
endif

check-am:
	$(foreach test,$(TESTS),./run.sh $(test);)

dist_noinst_SCRIPTS = run.sh unit_tests fast_regression long_regression \
					  root_regression with_bindings_regression \
					  dynamic_instrument_regression
EXTRA_DIST = run.sh unit_tests fast_regression long_regression root_regression \
			 with_bindings_regression dynamic_instrument_regression

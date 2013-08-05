TESTS = run-test.sh
TESTS_ENVIRONMENT = NO_MAKE=yes CUTTER="$(CUTTER)"

noinst_LTLIBRARIES = test-tuishogi.la

INCLUDES = $(CPPCUTTER_CFLAGS) -l$(top_srcdir)/src
LIBS = -losl $(CPPCUTTER_LIBS) $(top_builddir)/src/libtuishogi.la

LDFLAGS = -module -rpath $(libdir) -avoid-version -no-undefined

test_tuishogi_la_SOURCES = test-tuishogi.cpp

echo-cutter:
	@echo	$(CUTTER)

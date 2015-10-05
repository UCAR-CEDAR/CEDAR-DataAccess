# Tests

AUTOMAKE_OPTIONS = foreign

# Headers in 'tests' are used by the arrayT unit tests.

AM_CPPFLAGS = -I$(top_srcdir)/library
AM_LDADD = 
if CPPUNIT
AM_CPPFLAGS += $(CPPUNIT_CFLAGS)
AM_LDADD += $(CPPUNIT_LIBS)
endif

# These are not used by automake but are often useful for certain types of
# debugging. Set CXXFLAGS to this in the nightly build using export ...
CXXFLAGS_DEBUG = -g3 -O0 -fno-defer-pop -Wall -W -Wcast-align -Werror
TEST_COV_FLAGS = -ftest-coverage -fprofile-arcs

# This determines what gets built by make check
check_PROGRAMS = $(UNIT_TESTS)

# This determines what gets run by 'make check.'
TESTS = $(UNIT_TESTS)

DIRS_EXTRA = 

EXTRA_DIST = $(DIRS_EXTRA) 

CLEANFILES =

############################################################################
# Unit Tests
#

if CPPUNIT
UNIT_TESTS = strConvertT exceptT errHandlerT arrayT
else
UNIT_TESTS =

check-local:
	@echo ""
	@echo "**********************************************************"
	@echo "You must have cppunit 1.12.x or greater installed to run *"
	@echo "check target in ppt unit-tests directory                 *"
	@echo "**********************************************************"
	@echo ""
endif


strConvertT_SOURCES = strConvertT.cc
strConvertT_CPPFLAGS = $(AM_CPPFLAGS)
strConvertT_LDADD = ../library/libCedar.la $(AM_LDADD)

exceptT_SOURCES = exceptT.cc
exceptT_CPPFLAGS = $(AM_CPPFLAGS)
exceptT_LDADD = ../library/libCedar.la $(AM_LDADD)

errHandlerT_SOURCES = errHandlerT.cc
errHandlerT_CPPFLAGS = $(AM_CPPFLAGS)
errHandlerT_LDADD = ../library/libCedar.la $(AM_LDADD)

arrayT_SOURCES = arrayT.cc
arrayT_CPPFLAGS = $(AM_CPPFLAGS)
arrayT_LDADD = ../library/libCedar.la $(AM_LDADD)


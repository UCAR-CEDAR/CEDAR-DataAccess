
AUTOMAKE_OPTIONS = foreign dejagnu

DEJATOOL=cedar

AM_CPPFLAGS = -I$(top_srcdir)/library

# These are not used by automake but are often useful for certain types of
# debugging. The best way to use these is to run configure as:
#     export CXXFLAGS='...'; ./configure --disable-shared
# the --disable-shared is not required, but it seems to help with debuggers.
CXXFLAGS_DEBUG = -g3 -O0 -fno-defer-pop -Wall -W -Wcast-align -Werror
TEST_COV_FLAGS = -ftest-coverage -fprofile-arcs

CLEANFILES = *.log *.sum site.exp

EXTRA_DIST = cedar cedar.0 data config



# Build Cedar++
#

AUTOMAKE_OPTIONS = foreign check-news
ACLOCAL_AMFLAGS = -I conf

SUBDIRS = library unit-tests testsuite
DIST_SUBDIRS = library unit-tests testsuite

bin_SCRIPTS = cedar-config

#########################################################################
#
# docs

.PHONY: docs
docs:
	doxygen doxy.conf


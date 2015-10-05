
# Build libdap, libtest-types.a, getdap and deflate

AUTOMAKE_OPTIONS = foreign check-news
ACLOCAL_AMFLAGS = -I ../conf

aclocaldir=$(datadir)/aclocal

# These are not used by automake but are often useful for certain types of
# debugging. The best way to use these is to run configure as:
#     export CXXFLAGS='...'; ./configure --disable-shared
# the --disable-shared is not required, but it seems to help with debuggers.
CXXFLAGS_DEBUG = -g3 -O0 -fno-defer-pop -Wall -W -Wcast-align -Werror
TEST_COV_FLAGS = -ftest-coverage -fprofile-arcs

lib_LTLIBRARIES = libCedar.la 

bin_PROGRAMS = cedardump nrecords

libCedar_la_SOURCES = $(CEDAR_SRC)
libCedar_la_LDFLAGS = -version-info $(LIBCEDAR_VERSION)

pkginclude_HEADERS = $(CEDAR_HDR) CedarArray.cc

cedardump_SOURCES = cedardumper.cc
cedardump_LDADD = libCedar.la

nrecords_SOURCES = nrecords.cc
nrecords_LDADD = libCedar.la

EXTRA_DIST = 

# MAINTAINERCLEANFILES = $(LEX_YACC_FILES)

.PHONY: docs
docs:
	doxygen doxy.conf
	(cd docs && tar -czf html.tar.gz html)
	
###########################################################################

# Build linux RPMs

srpm: dist
	rpmbuild -ts @PACKAGE@-@PACKAGE_VERSION@.tar.gz

rpm: dist
	rpmbuild -tb @PACKAGE@-@PACKAGE_VERSION@.tar.gz

#############################################################################
# Library sources
# 

CEDAR_SRC = CedarArray.cc CedarArray_CedarBlock_tpl.cc \
	CedarArray_CedarParameter_tpl.cc CedarArray_CedarRecordType_tpl.cc \
	CedarArray_CedarString_tpl.cc CedarArray_byte_tpl.cc \
	CedarArray_char_tpl.cc CedarArray_field_tpl.cc CedarArray_int_tpl.cc \
	CedarBlock.cc CedarCatalogRecord.cc CedarConstraintEvaluator.cc \
	CedarCrayBlockingFormat.cc CedarCrayServices.cc CedarCursor.cc \
	CedarDataRecord.cc CedarDate.cc CedarDump.cc CedarErrorHandler.cc \
	CedarException.cc CedarFile.cc CedarGroup.cc CedarHeaderRecord.cc \
	CedarLogicalRecord.cc CedarLogicalRecordBuilder.cc \
	CedarMadrigalFormat.cc CedarParameter.cc CedarRecordType.cc \
	CedarString.cc CedarStringConversions.cc CedarValidDate.cc \
	CedarVersion.cc

CEDAR_HDR = CedarArray.h CedarBlock.h CedarCatalogRecord.h CedarConfig.h \
	CedarConstraintEvaluator.h CedarCrayBlockingFormat.h \
	CedarCrayBlockingStructures.h CedarCrayServices.h CedarCursor.h \
	CedarDataRecord.h CedarDataTypes.h CedarDate.h CedarDump.h \
	CedarErrorHandler.h CedarErrors.h CedarException.h CedarFile.h \
	CedarGroup.h CedarHeaderRecord.h CedarLogicalRecord.h \
	CedarLogicalRecordBuilder.h CedarMadrigalFormat.h CedarMessages.h \
	CedarParameter.h CedarPhysicalFile.h CedarRecordType.h CedarString.h \
	CedarStringConversions.h CedarValidDate.h CedarVersion.h


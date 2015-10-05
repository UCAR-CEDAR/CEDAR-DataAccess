# -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([cedar], [2.2.2], [westp@rpi.edu])
AC_CONFIG_AUX_DIR([conf])
AC_CONFIG_MACRO_DIR([conf])

AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([configure.ac])
AM_CONFIG_HEADER([library/CedarConfig.h])

AC_CANONICAL_HOST
AC_SUBST(host)

dnl library visioning: Update these when the interface changes. Generally,
dnl assume that the interface tracks the major and minor release numbers.
LIB_CEDAR_CURRENT=2
LIB_CEDAR_AGE=0
LIB_CEDAR_REVISION=0
AC_SUBST(LIB_CEDAR_CURRENT)
AC_SUBST(LIB_CEDAR_AGE)
AC_SUBST(LIB_CEDAR_REVISION)
LIBCEDAR_VERSION="$LIB_CEDAR_CURRENT:$LIB_CEDAR_REVISION:$LIB_CEDAR_AGE"
AC_SUBST(LIBCEDAR_VERSION)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_TIME 
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T
AC_STRUCT_TM
AC_FUNC_STRFTIME
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_CHECK_FUNCS([strchr getcwd])

AH_TOP([#ifndef _CedarConfig_h
#define _CedarConfig_h

/**
  Usage and justification for the macro ENDL.

  ENDL is an easy way to use '\n', end of lines, characters and can be as
  familiar to the programmer as endl.
  
  You may say; Why not use "endl" directly? The answer is: for performance
  reasons.

  When the API is instantiated, at any given moment messages are being
  dumped into CedarDump objects and many of those messages are in the in
  memory and not committed to disk. Every time you use endl, you insert an
  '\n' character and you flush the stream, therefore I/O operations are
  perform. I/O is usually time consuming and by not fully using the capacity
  of the buffer stream, you get performance degradation.

  The problem that we faced with ENDL is the lost of messages. The API uses
  exit if an error is encounter and that can happen when messages are
  sitting in memory waiting to get written to file. when using exit
  you must be aware that no all destructors for all the objects existing in
  that given moment will called therefore there is not guarantee that the
  CedarDump objects buffer is flushed so many  messages will be lost.

  That is even worse when you realize that the last messages are the ones
  that matter since they contain the status of the API at the moment exit
  was call. To get over this we have the possible solutions:
  \item 1.- All CedarDump objects across the API can be declared static
            because static object's destructor are called when exit is used.
  \item 2.- We can use the at_exit mechanism to register the destructor for
            CedarDump objects.
  \item 3.- We can use C++ exception handling. 
  \item 4.- We make CedarDump objects streaming capabilities static, that is:
            the ofstream object file_buffer in CedarDump is static so its
	    destructor, which flushes the stream, is clean called when using
	    exit.

  The option 4.- is the most elegant and efficient solution. All objects in
  the API share the same streaming buffer so they write to the same file,
  I/O operations are reduced, number of file handles for dumping are reduced
  to one and we get better performance. The coordination for the CedarDump
  objects share the same ofstream object is base on the nifty counter
  technique.
  
  */

#define ENDL "\n"

#ifdef CEDAR_ANSI
#define ansi
#endif 

])

AH_BOTTOM([

#if defined(CEDAR_DEBUG_LEVEL1) || defined(CEDAR_DEBUG_LEVEL2)
#define COUT(p) p
#else
#define COUT(p) 
#endif 


#ifdef CEDAR_DEBUG_LEVEL2
#define LOGGING_WITH_CEDARDUMP
#endif

#endif /* _config_h */])

AC_ARG_ENABLE(exceptions,
	      [AS_HELP_STRING([--enable-exceptions],[throw exceptions instead of exiting with errors])],
	      USE_EXCEPTIONS=$enableval, USE_EXCEPTIONS=yes)

case "$USE_EXCEPTIONS" in
yes)
  AC_DEFINE([CEDAR_USE_EXCEPTIONS], [1], [Define this to throw exceptions instead of exiting, default is to throw exceptions])
  ;;
esac

AC_ARG_ENABLE(cedardebug,
	      [AS_HELP_STRING([--enable-cedardebug],[set debugging to 1 or 2])],
	      USE_CEDARDEBUG=$enableval, USE_CEDARDEBUG=0)

case "$USE_CEDARDEBUG" in
1)
  AC_DEFINE([CEDAR_DEBUG_LEVEL1],[1],[Define this for level 1 debugging])
  ;;
2)
  AC_DEFINE([CEDAR_DEBUG_LEVEL2],[1],[Define this for level 2 debugging])
  ;;
esac

AM_PATH_CPPUNIT(1.12.0,
	[AM_CONDITIONAL([CPPUNIT], [true])],
	[AM_CONDITIONAL([CPPUNIT], [false])])

AC_CONFIG_FILES([Makefile
		 library/Makefile
		 unit-tests/Makefile
		 testsuite/Makefile
		 testsuite/config/unix.exp
		 testsuite/common_tests.exp])

AC_CONFIG_FILES([cedar-config], [chmod +x cedar-config]) 

AC_OUTPUT

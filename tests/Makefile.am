# tests/Makefile.am

gmockdir = $(top_srcdir)/thirdparty/gmock
gtestdir = $(gmockdir)/gtest

airballdir = $(top_srcdir)/src

AM_CPPFLAGS = \
	-I$(gmockdir) \
	-I$(gmockdir)/include \
	-I$(gtestdir) \
	-I$(gtestdir)/include \
	-I $(airballdir)

AM_CXXFLAGS = @PTHREAD_CFLAGS@
AM_LIBS = @PTHREAD_LIBS@

LDADD = \
	$(airballdir)/game/libgame.a

TESTS = airball_ut
check_PROGRAMS = airball_ut

airball_ut_SOURCES = \
	ObjectTests.cpp \
	main.cpp \
	${gtestdir}/src/gtest-all.cc

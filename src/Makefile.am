# src/Makefile.am

SUBDIRS = physics

bin_PROGRAMS = airball

LDADD = physics/libphysics.a
AM_CPPFLAGS = -I${srcdir}/physics

airball_SOURCES = \
	main.cpp

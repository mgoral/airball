AC_INIT([Airball], [0.1.0], [https://github.com/mgoral/airball/issues])
AM_INIT_AUTOMAKE([foreign -Wall])

AC_PREFIX_DEFAULT([/usr])

AC_LANG([C++])
AC_PROG_CXX
AC_PROG_CPP
AX_CXX_COMPILE_STDCXX_11
AC_PROG_RANLIB
AM_PROG_AR

AC_PROG_LN_S
AC_PROG_MKDIR_P

AC_SUBST([AM_CXXFLAGS], ["-Wall -Wextra -Werror -pedantic"])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/game/Makefile
])

AC_OUTPUT

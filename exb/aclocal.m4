#
# Include the TEA standard macro set
#

builtin(include,tclconfig/tcl.m4)

#
# Add here whatever m4 macros you want to define for your package
#

AC_DEFUN([EXA_STUBS], [
	if test "${STUBS_BUILD}" = "1"; then
		AC_DEFINE(USE_EXA_STUBS, 1, [Use Exa Stubs])
	fi
])

AC_DEFUN([TIP445], [
    AC_MSG_CHECKING([whether we need to polyfill TIP 445])
    saved_CFLAGS="$CFLAGS"
    CFLAGS="$CFLAGS $TCL_INCLUDE_SPEC"
    AC_TRY_COMPILE([#include <tcl.h>], [Tcl_ObjIntRep ir;],
	have_tcl_objintrep=yes, have_tcl_objintrep=no)
    CFLAGS="$saved_CFLAGS"

    if test "$have_tcl_objintrep" = yes; then
	AC_DEFINE(TIP445_SHIM, 0, [Do we need to polyfill TIP 445?])
	AC_MSG_RESULT([no])
    else
	AC_DEFINE(TIP445_SHIM, 1, [Do we need to polyfill TIP 445?])
	AC_MSG_RESULT([yes])
    fi])

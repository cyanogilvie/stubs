#undef USE_TCL_STUBS
#undef USE_EXA_STUBS
#define USE_TCL_STUBS 1
#define USE_EXA_STUBS 1

#include "exa.h"

MODULE_SCOPE const ExaStubs*	exaStubsPtr;
const ExaStubs*					exaStubsPtr = NULL;

#undef ExaInitializeStubs
MODULE_SCOPE const char* ExaInitializeStubs(Tcl_Interp* interp)
{
	const char*	got = NULL;
	fprintf(stderr, "In ExaInitializeStubs, verion: (%s)\n", PACKAGE_VERSION);
	got = Tcl_PkgRequireEx(interp, PACKAGE_NAME, PACKAGE_VERSION, 0, &exaStubsPtr);
	fprintf(stderr, "Got ver: (%s), exaStubsPtr: %p\n", got, exaStubsPtr);
	return got;
}

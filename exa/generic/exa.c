#include "exaInt.h"

// Internal API {{{
struct exa_data* ExaGetData(ExaData* data)
{
	return (struct exa_data*)data;
}

//}}}
// Stubs API {{{
ExaData* Exa_NewData(const char* name, int foo, int bar)
{
	struct exa_data*	d = ckalloc(sizeof(struct exa_data));

	d->pub.name = name;
	d->foo = foo;
	d->bar = bar;

	fprintf(stderr, "In Exa_NewData, returning %p\n", d);
	return (ExaData*)d;
}


void Exa_FreeData(ExaData** data)
{
	ckfree(*data);
	*data = NULL;
}


int Exa_GetFoo(ExaData* data)
{
	struct exa_data*	d = ExaGetData(data);
	fprintf(stderr, "In Exa_GetFoo, returning %d from exa_data: %p\n", d->foo, d);
	return d->foo;
}


int Exa_GetBar(ExaData* data)
{
	struct exa_data*	d = ExaGetData(data);
	return d->bar;
}

//}}}

extern const TclStubs* const exaConstStubsPtr;

#ifdef __cplusplus
extern "C" {
#endif
DLLEXPORT int Exa_Init(Tcl_Interp* interp)
{
	int		code = TCL_OK;

#if USE_TCL_STUBS
	if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL)
		return TCL_ERROR;
#endif

	fprintf(stderr, "Exa_Init, providing package version (%s) with stubsPtr: %p\n", PACKAGE_VERSION, exaConstStubsPtr);
	code = Tcl_PkgProvideEx(interp, PACKAGE_NAME, PACKAGE_VERSION, exaConstStubsPtr);
	if (code != TCL_OK) goto finally;

finally:
	return code;
}

#ifdef __cplusplus
}
#endif

#include "exc.h"

struct exa_data* ExaGetData(ExaData* data)
{
	return (struct exa_data*)data;
}

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


#ifdef __cplusplus
extern "C" {
#endif
DLLEXPORT int Exc_Init(Tcl_Interp* interp)
{
#if USE_TCL_STUBS
	if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL)
		return TCL_ERROR;
#endif

	code = Tcl_PkgProvide(interp, PACKAGE_NAME, PACKAGE_VERSION);
	if (code != TCL_OK) goto finally;

	return TCL_OK;
}

#ifdef __cplusplus
}
#endif

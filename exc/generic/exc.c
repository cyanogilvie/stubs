#include "exc.h"

struct exc_data* ExcGetData(ExcData* data)
{
	return (struct exc_data*)data;
}

ExcData* Exc_NewData(const char* name, int foo, int bar)
{
	struct exc_data*	d = ckalloc(sizeof(struct exc_data));

	d->pub.name = name;
	d->foo = foo;
	d->bar = bar;

	fprintf(stderr, "In Exc_NewData, returning %p\n", d);
	return (ExcData*)d;
}


void Exc_FreeData(ExcData** data)
{
	ckfree(*data);
	*data = NULL;
}


int Exc_GetFoo(ExcData* data)
{
	struct exc_data*	d = ExcGetData(data);
	fprintf(stderr, "In Exc_GetFoo, returning %d from exc_data: %p\n", d->foo, d);
	return d->foo;
}


int Exc_GetBar(ExcData* data)
{
	struct exc_data*	d = ExcGetData(data);
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

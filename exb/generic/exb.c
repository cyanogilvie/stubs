#include <tcl.h>
#include "exa.h"
#include "tip445.h"

#include <string.h>

// ExaData handle management {{{
static void free_exadata_handle(Tcl_Obj* obj);
static void update_exadata_handle_string_rep(Tcl_Obj* obj);

Tcl_ObjType exadata_handle = {
	"exadata_handle",
	free_exadata_handle,
	NULL,
	update_exadata_handle_string_rep
};

static void free_exadata_handle(Tcl_Obj* obj) //{{{
{
	Tcl_ObjIntRep*	ir = Tcl_FetchIntRep(obj, &exadata_handle);

	if (ir != NULL) {
		fprintf(stderr, "Freeing ExData %p\n", ir->twoPtrValue.ptr1);
		Exa_FreeData((ExaData**)&ir->twoPtrValue.ptr1);
	}
}

//}}}
static void update_exadata_handle_string_rep(Tcl_Obj* obj) //{{{
{
	Tcl_ObjIntRep*	ir = Tcl_FetchIntRep(obj, &exadata_handle);
	char			buf[64];

	sprintf(buf, "exadata_handle%p", ir->twoPtrValue.ptr1);
	fprintf(stderr, "buf: (%s)\n", buf);

	Tcl_InitStringRep(obj, buf, strlen(buf));
}

//}}}
Tcl_Obj* new_exadata_handle(ExaData* data) //{{{
{
	Tcl_Obj*		res = Tcl_NewObj();
	Tcl_ObjIntRep	ir;

	ir.twoPtrValue.ptr1 = data;
	ir.twoPtrValue.ptr2 = NULL;
	Tcl_StoreIntRep(res, &exadata_handle, &ir);
	Tcl_InvalidateStringRep(res);

	return res;
}

//}}}
static int get_exadata_from_obj(Tcl_Interp* interp, Tcl_Obj* obj, ExaData** data) //{{{
{
	int		code = TCL_OK;

	Tcl_ObjIntRep*	ir = Tcl_FetchIntRep(obj, &exadata_handle);
	if (ir == NULL) {
		Tcl_SetObjResult(interp, Tcl_ObjPrintf("Could not fetch exadata ref"));
		code = TCL_ERROR;
		goto finally;
	}

	*data = ir->twoPtrValue.ptr1;

finally:
	return code;
}

//}}}
// ExaData handle management }}}

static int newexa(ClientData cdata, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[]) //{{{
{
	int			code = TCL_OK;
	const char*	name = NULL;
	int			foo, bar;

	if (objc != 4) {
		Tcl_WrongNumArgs(interp, 1, objv, "name foo bar");
		code = TCL_ERROR;
		goto finally;
	}

	name = Tcl_GetString(objv[1]);
	if (TCL_OK != (code = Tcl_GetIntFromObj(interp, objv[2], &foo))) goto finally;
	if (TCL_OK != (code = Tcl_GetIntFromObj(interp, objv[3], &bar))) goto finally;

	fprintf(stderr, "Calling Exa_NewData\n");
	Tcl_SetObjResult(interp, new_exadata_handle(Exa_NewData(name, foo, bar)));
	fprintf(stderr, "Exa_NewData returned\n");

finally:
	return code;
}

//}}}
static int getfoo(ClientData cdata, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[]) //{{{
{
	int			code = TCL_OK;
	ExaData*	data = NULL;
	int			foo;

	if (objc != 2) {
		Tcl_WrongNumArgs(interp, 1, objv, "exahandle");
		code = TCL_ERROR;
		goto finally;
	}

	if (TCL_OK != (code = get_exadata_from_obj(interp, objv[1], &data))) goto finally;

	fprintf(stderr, "Calling Exa_GetFoo\n");
	foo = Exa_GetFoo(data);
	fprintf(stderr, "Exa_GetFoo returned\n");

	Tcl_SetObjResult(interp, Tcl_NewIntObj(foo));

finally:
	return code;
}

//}}}

#define NS	"::exb"

struct cmd {
	char*			name;
	Tcl_ObjCmdProc*	proc;
} cmds[] = {
	{NS "::newexa",	newexa},
	{NS "::getfoo", getfoo},
	{NULL,			NULL}
};

#ifdef __cplusplus
extern "C" {
#endif
DLLEXPORT int Exb_Init(Tcl_Interp* interp) //{{{
{
	int				code = TCL_OK;
	Tcl_Namespace*	ns = NULL;

#if USE_TCL_STUBS
	if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL)
		return TCL_ERROR;
#endif
#if USE_EXA_STUBS
	if (Exa_InitStubs(interp) == NULL)
		return TCL_ERROR;
#endif

	ns = Tcl_CreateNamespace(interp, NS, NULL, NULL);
	if (TCL_OK != (code = Tcl_Export(interp, ns, "*", 0)))
		goto finally;

	{
		struct cmd* c = cmds;

		while(c->name != NULL) {
			if (NULL == Tcl_CreateObjCommand(interp, c->name, c->proc, NULL, NULL)) {
				Tcl_SetObjResult(interp, Tcl_ObjPrintf("Could not create command %s", c->name));
				code = TCL_ERROR;
				goto finally;
			}
			c++;
		}
	}


	code = Tcl_PkgProvide(interp, PACKAGE_NAME, PACKAGE_VERSION);
	if (code != TCL_OK) goto finally;

finally:
	return code;
}

//}}}
#ifdef __cplusplus
}
#endif

// vim: foldmethod=marker foldmarker={{{,}}} ts=4 shiftwidth=4

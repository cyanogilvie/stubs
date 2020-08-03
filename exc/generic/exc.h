#include <tcl.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILD_exc
#undef TCL_STORAGE_CLASS
#define TCL_STORAGE_CLASS DLLEXPORT
#endif

typedef struct ExaData {
	const char*	name;
} ExaData;

struct exa_data {
	// Public members
	ExaData	pub;

	// Private members
	int		foo;
	int		bar;
};

struct exa_data* ExaGetData(ExaData* data);

EXTERN int Exc_Init _ANSI_ARGS_((Tcl_Interp * interp));

#ifdef __cplusplus
}
#endif

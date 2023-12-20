#include <tcl.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILD_exc
#undef TCL_STORAGE_CLASS
#define TCL_STORAGE_CLASS DLLEXPORT
#endif

typedef struct ExcData {
	const char*	name;
} ExcData;

struct exc_data {
	// Public members
	ExcData	pub;

	// Private members
	int		foo;
	int		bar;
};

struct exc_data* ExcGetData(ExcData* data);

EXTERN int Exc_Init _ANSI_ARGS_((Tcl_Interp * interp));

#ifdef __cplusplus
}
#endif

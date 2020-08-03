#include "exa.h"

/* !BEGIN!: Do not edit below this line. */

const ExaStubs exaStubs = {
    TCL_STUB_MAGIC,
    0,
    Exa_NewData, /* 0 */
    Exa_FreeData, /* 1 */
    Exa_GetFoo, /* 2 */
    Exa_GetBar, /* 3 */
};

/* !END!: Do not edit above this line. */


const ExaStubs* ExaStubsPtr = NULL;
MODULE_SCOPE const ExaStubs* const exaConstStubsPtr;
const ExaStubs* const exaConstStubsPtr = &exaStubs;

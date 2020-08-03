
/* !BEGIN!: Do not edit below this line. */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Exported function declarations:
 */

/* 0 */
EXTERN ExaData*		Exa_NewData(const char*name, int foo, int bar);
/* 1 */
EXTERN void		Exa_FreeData(ExaData**data);
/* 2 */
EXTERN int		Exa_GetFoo(ExaData*data);
/* 3 */
EXTERN int		Exa_GetBar(ExaData*data);

typedef struct ExaStubs {
    int magic;
    void *hooks;

    ExaData* (*exa_NewData) (const char*name, int foo, int bar); /* 0 */
    void (*exa_FreeData) (ExaData**data); /* 1 */
    int (*exa_GetFoo) (ExaData*data); /* 2 */
    int (*exa_GetBar) (ExaData*data); /* 3 */
} ExaStubs;

extern const ExaStubs *exaStubsPtr;

#ifdef __cplusplus
}
#endif

#if defined(USE_EXA_STUBS)

/*
 * Inline function declarations:
 */

#define Exa_NewData \
	(exaStubsPtr->exa_NewData) /* 0 */
#define Exa_FreeData \
	(exaStubsPtr->exa_FreeData) /* 1 */
#define Exa_GetFoo \
	(exaStubsPtr->exa_GetFoo) /* 2 */
#define Exa_GetBar \
	(exaStubsPtr->exa_GetBar) /* 3 */

#endif /* defined(USE_EXA_STUBS) */

/* !END!: Do not edit above this line. */

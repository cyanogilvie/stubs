library exa
interface exa

declare 0 generic {
	ExaData* Exa_NewData(const char* name, int foo, int bar)
}
declare 1 generic {
	void Exa_FreeData(ExaData** data)
}
declare 2 generic {
	int Exa_GetFoo(ExaData* data)
}
declare 3 generic {
	int Exa_GetBar(ExaData* data)
}

# vim: ft=tcl foldmethod=marker foldmarker=<<<,>>>

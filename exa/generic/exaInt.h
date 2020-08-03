#include "exa.h"

struct exa_data {
	// Public members
	ExaData	pub;

	// Private members
	int		foo;
	int		bar;
};

struct exa_data* ExaGetData(ExaData* data);

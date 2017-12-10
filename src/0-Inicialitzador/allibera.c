#include "../1-Executor/descriptor.h"
#include "../9-Útils/bàsic.h"

void
alliberar_variables (struct variables *vs)
{
	vs->mida = 0;
	vs->punter = basic_free (vs->punter);
}

void
alliberar_descriptors_funcio_globals (void)
{
	alliberar_variables (&variables_globals);
}

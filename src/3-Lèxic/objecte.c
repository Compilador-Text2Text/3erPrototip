#include <stdio.h>

#include "objecte.h"
#include "maquina_estats.h"

#include "../1-Executor/descriptor.h"

enum cert_fals verbos_objecte; // Per saber si continuem sent verbosos.

void
lexic_variables_i_declarar (char b, struct variables *vs, char *missatge, int lloc)
{
	int mida;

if (verbos_objecte) printf ("L: Variables i declarar → %s.\n", missatge);
	maquina_estats_llegir_inici_final ('-', b, missatge, lloc);

	vs->mida = mida = maquina_estats_llegir_enter_positiu (missatge, lloc);
if (verbos_objecte) printf ("L: Un total de: %d variables.\n", mida);
}

enum cert_fals
lexic_llegir_objecte (char (*funcio) (void), enum cert_fals fem_verbos, enum cert_fals maquina_estats)
{
	// Definim.
	verbos_objecte = fem_verbos;
	maquina_estats_inicialitza (funcio, maquina_estats);

	// Lèxic.
if (verbos_objecte) printf ("L: Llegir objecte.\n");
	lexic_variables_i_declarar ('v', &variables_globals, "Variables globals", -1);

	maquina_estats_finalitza ();
	return CF_fals;
}

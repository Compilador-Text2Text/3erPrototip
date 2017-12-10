#include <stdio.h>
#include <string.h>

#include "objecte.h"
#include "maquina_estats.h"

#include "../1-Executor/descriptor.h"
#include "../6-Depurador/depurador.h"

enum cert_fals verbos_objecte; // Per saber si continuem sent verbosos.

enum tipus
lexic_definir_tipu (char *t, char *missatge, int lloc)
{
	int i;

	for (i = 0; i < Tipus_END; i++)
		if (!strcmp (t, string_tipu (i)))
			return i;

	printf ("Error: entrat: %s i esperat:\n", t);
	mostra_tipus ();
	maquina_error_procedencia (missatge, lloc);
	return Tipus_cap;
}

void
lexic_definir_variable (struct variable *v, int lloc)
{
	char c, *t;

	v->usat = CF_fals;
	v->nom = strdup (maquina_estats_cadena_caracters ("Definint nom", lloc));
	t = maquina_estats_cadena_caracters ("Definint tipus", lloc);
	v->descriptor.tipus = lexic_definir_tipu (t, "Investigant el tipus", lloc);
	v->descriptor.vegades_punter = maquina_estats_llegir_enter ("Vegades punter", lloc);

	switch ((c = maquina_estats_caracter_sense_comentaris ("Mirant si inicialitza la variable", lloc)))
	{
	case ':':
		printf ("\nTODO\n\n");
		v->inicialitzat = CF_cert;
		break;
	case ';':
		v->inicialitzat = CF_fals;
		break;
	default:
		printf ("ERROR: Entrat: %c\n", c);
		maquina_error_procedencia ("Esperàvem si inicialitzava la variable, llavors tenia que entrar: [:;]", lloc);
	}
if (verbos_objecte)
{
	printf ("L: Variable: nom: \"%s\" \"%s\"(%ld).\n", v->nom, string_tipu (v->descriptor.tipus), v->descriptor.vegades_punter);
	if (v->inicialitzat)
		; // TODO
}
}

void
lexic_variables_i_declarar (char b, struct variables *vs, char *missatge, int lloc)
{
	int mida;
	struct variable *v;

if (verbos_objecte) printf ("L: Variables i declarar → %s.\n", missatge);
	maquina_estats_llegir_inici_final ('-', b, missatge, lloc);

	vs->mida = mida = maquina_estats_llegir_enter_positiu ("Definint el nombre de variables", lloc);
	vs->punter = basic_malloc ( mida * sizeof (struct variable) );
if (verbos_objecte) printf ("L: Un total de: %d variables.\n", mida);

	for (v = vs->punter; v < vs->punter +mida; v++)
		lexic_definir_variable (v, lloc);
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

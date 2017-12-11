#include <stdio.h>
#include <string.h>

#include "objecte.h"
#include "maquina_estats.h"

#include "../1-Executor/descriptor.h"
#include "../6-Depurador/depurador.h"

enum cert_fals verbos_objecte; // Per saber si continuem sent verbosos.

union valor
lexic_definir_valor (struct descriptor d, char *missatge, int lloc)
{
	union valor v;

	if (d.vegades_punter)
	{
		if ((d.tipus == Tipus_char) && (d.vegades_punter == 1))
			v.punter = strdup (maquina_estats_cadena_caracters ("Definint valor \"strings\"", lloc));
		else
		{
			printf ("ERROR: No sabem definir el valor de: %s(%ld).\n", string_tipu(d.tipus), d.vegades_punter);
			maquina_error_procedencia (missatge, lloc);
		}
		return v;
	}

	switch (d.tipus)
	{
	case Tipus_char:
		v.caracter = maquina_estats_llegir_caracter ("Definint un caràcter", lloc);
		break;
	case Tipus_int:
		v.enter = maquina_estats_llegir_enter ("Definint un enter", lloc);
		break;
	default:
		printf ("ERROR: No sabem definir el valor de: %s(%ld).\n", string_tipu(d.tipus), d.vegades_punter);
		maquina_error_procedencia (missatge, lloc);
	}

	return v;
}

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

struct descriptor
lexic_definir_descriptor (int lloc)
{
	char *t;
	struct descriptor d;

	t = maquina_estats_cadena_caracters ("Definint tipus", lloc);
	d.tipus = lexic_definir_tipu (t, "Investigant el tipus", lloc);
	maquina_estats_comprovacio_caracter ('(', "Parèntesis per les vegades punter", lloc);
	d.vegades_punter = maquina_estats_llegir_enter ("Vegades punter", lloc);
	maquina_estats_comprovacio_caracter (')', "Parèntesis per les vegades punter", lloc);
	return d;
}

void
lexic_definir_variable (struct variable *v, int lloc)
{
	char c;

	v->usat = CF_fals;
	v->nom = strdup (maquina_estats_cadena_caracters ("Definint nom", lloc));
	v->descriptor = lexic_definir_descriptor (lloc);

	switch ((c = maquina_estats_caracter_sense_comentaris ("Mirant si inicialitza la variable", lloc)))
	{
	case ':':
		v->valor = lexic_definir_valor (v->descriptor, "Definint valor de variable", lloc);
		maquina_estats_comprovacio_caracter (';', "Per saber que hem acabat amb la variable", lloc);
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
	printf ("L: Variable: nom: \"%s\" \"%s\"(%ld)", v->nom, string_tipu (v->descriptor.tipus), v->descriptor.vegades_punter);
	if (v->inicialitzat)
		mostra_valor (v->descriptor, v->valor);
	else
		printf ("No inicialitzat");
	printf (".\n");
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

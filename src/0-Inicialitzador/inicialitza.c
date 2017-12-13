#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "allibera.h"

#include "../2-Sistema/inicialitza.h"
#include "../3-Lèxic/objecte.h"
#include "../4-Sintàctic/shunting-yard_algorithm.h"
#include "../6-Depurador/depurador.h"
#include "../9-Útils/bàsic.h"
#include "../9-Útils/pila.h"

FILE *g_pf;			// punter de fitxer, variable global.

/************************************************/
/*	Funcions privades			*/
/************************************************/
FILE *
inicialitza_inicialitza_lectura_fitxer (char *nom)
{
	FILE *pf;
	struct stat s;

	if ( stat (nom, &s) )
		basic_error ("El fitxer: \"%s\"\nNo existeix o no tenim permisos d'accés", nom);

	if (!S_ISREG (s.st_mode))
		basic_error ("No és un fitxer: \"%s\"\nNomés podem interpretar fitxers", nom);

	pf = fopen (nom, "r");
	if (pf == NULL) // Crec que no pot acabar aquí, però mai està de més.
		basic_error_perror ();

	return pf;
}

void
inicialitza_finalitza_lectura_fitxer (FILE *pf)
{
	fclose (pf);
}

char
inicialitza_lectura_fitxer (void)
{
	return getc (g_pf);
}

/************************************************/
/*	Funcions públiques			*/
/************************************************/
int
inicialitza_lectura_objecte (char *nom, int argc, char **argv,
	enum cert_fals vl, enum cert_fals vm, enum cert_fals vs, enum cert_fals ve)
{
	int out, reservar;

	g_pf = inicialitza_inicialitza_lectura_fitxer (nom);
		reservar = lexic_llegir_objecte (inicialitza_lectura_fitxer, vl, vm);
		shunting_yard_algorithm (reservar, vs);
	inicialitza_finalitza_lectura_fitxer (g_pf);

	// Executa el codi.
	out = 1;

	// Alliberem en memòria.
	alliberar_descriptors_funcio_globals ();

	return out;
}

void
inicialitza_inicialitza_funcions_sistema (void)
{
	sistema_inicialitza ();
}

void
inicialitza_finalitza_funcions_sistema (void)
{
	sistema_finalitza ();
}

void
inicialitza_mostra_sistema ()
{
inicialitza_inicialitza_funcions_sistema ();
	mostra_localitzacions	();
	mostra_tipus		();
	mostra_sistema		();
inicialitza_finalitza_funcions_sistema ();
}

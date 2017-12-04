#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "../9-Útils/bàsic.h"
#include "../9-Útils/pila.h"

FILE *g_pf;			// punter de fitxer, variable global.
int e_cf;			// extern, comptador de files.
struct pila e_ps;		// Pila externa de string.
enum cert_fals bolea_lectura;	// Saber quan reiniciar e_ps.

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

	e_cf		= 1;
	e_ps		= pila_inicialitzar (100, sizeof (char));
	bolea_lectura	= CF_fals;
	return pf;
}

void
inicialitza_finalitza_lectura_fitxer (FILE *pf)
{
	fclose (pf);
	pila_alliberar (&e_ps);
}

char
inicialitza_lectura_fitxer (void)
{
	char c = getc (g_pf);

	if ( c == EOF )
		exit (EXIT_FAILURE);
		// TODO error

	if ( c == '\n' )
		bolea_lectura = CF_cert;
	else if (bolea_lectura)
	{
		bolea_lectura = CF_fals;
		e_cf++;
		e_ps.us = 0;
	}

	pila_afegir (&e_ps, &c);
	return c;
}

/************************************************/
/*	Funcions publiques			*/
/************************************************/
int
inicializa_lectura_objecte (char *nom, int argc, char **argv, int vl, int vs, int ve)
{
	int out;

	g_pf = inicialitza_inicialitza_lectura_fitxer (nom);
	inicialitza_finalitza_lectura_fitxer (g_pf);

	// Executa el codi.
	out = 1;

	return out;
}

void
inicialitza_mostra_sistema ()
{
}

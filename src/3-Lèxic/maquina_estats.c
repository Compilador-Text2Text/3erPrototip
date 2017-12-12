#include <ctype.h>
#include <stdio.h>

#include "maquina_estats.h"

#include "../9-Útils/pila.h"

char (*seguent_me_caracter) (void);
enum cert_fals verbos_maquina;	// Per saber si continuem sent verbosos.
int g_me_f, g_me_c;		// Variables globals fila i columna.
enum cert_fals bool_me_lectura;	// Saber si ha llegit un \n.
struct pila g_me_cc;		// Pila de cadena de caràcters.
char end_char = '\0';		// Afegir correctament al final de g_me_cc.

/************************************************/
/*	Funcions bàsiques			*/
/************************************************/
void
maquina_error_procedencia (char *general, int lloc)
{
	printf ("E: Error detectat a la funció: %d\nE: -general- %s.\n", lloc, general);
	printf ("E: Localitzat a la línia:%d:%d:\n", g_me_f, g_me_c);
	exit (EXIT_FAILURE);
}

void
maquina_error_final (char *general, int lloc)
{
	if ((g_me_f == 1) && (g_me_c == 1)) printf ("E: El fitxer està buit.\n");
	printf ("E: Necessitat de llegir més informació però el document ha acabat.\nI: Per més informació premi -vm i/o -vl.\n");
	maquina_error_procedencia (general, lloc);
}

char
maquina_seguent_caracter (char *general, int lloc)
{
	char c = seguent_me_caracter ();

	g_me_c++;
	if ( c == EOF )
	{
		if (bool_me_lectura) g_me_c = 0;
		maquina_error_final (general, lloc);
	}
	else if ( c == '\n' )
	{
		bool_me_lectura = CF_cert;
		g_me_f++;
	}
	else if ( bool_me_lectura )
	{
		bool_me_lectura = CF_fals;
		g_me_c = 1;
	}
	return c;
}
/************************************************/
/*	Funcions privades			*/
/************************************************/

// On 'f' és el caràcter entrat.
// [^'f'\\n]*'f'
void
maquina_estats_llegir_fins (char f, char *general, int lloc)
{
	char c;

if (verbos_maquina) printf ("M: Llegir fins: '%c'.\n", f);
	while ((c = maquina_seguent_caracter (general, lloc)) != EOF)
		if	(c == f	  ) return;
		else if	(c == '\n') break;

	maquina_error_procedencia (general, lloc);
}

// On 'o' és el que retorna.
// (#[^\n]*\n|[ \t\n])*'o'
char
maquina_estats_caracter_sense_comentaris (char *general, int lloc)
{
	char c;

	while ((c = maquina_seguent_caracter (general, lloc)) != EOF)
		switch (c)
		{
		case '#': maquina_estats_llegir_fins ('\n', general, lloc);
		case ' ':
		case '\t':
		case '\n':
			break;
		default:
			return c;
		}
	return c;
}

void
maquina_estats_comprovacio_caracter_amb_2 (char esperat, char entrat, char *missatge, int lloc)
{
if (verbos_maquina) printf ("M: Comprova si '%c ≠ %c'.\n", esperat, entrat);
	if ( esperat == entrat ) return;
	printf ("ERROR: Caràcter esperat i entrat: %c ≠ %c.\n", esperat, entrat);
	maquina_error_procedencia (missatge, lloc);
}

/************************************************/
/*	Funcions públiques			*/
/************************************************/
void
maquina_estats_inicialitza (char (*funcio) (void), enum cert_fals fem_verbos)
{
	seguent_me_caracter = funcio;
	verbos_maquina = fem_verbos;

	// Millorar els missatges d'errors.
	g_me_f = 1;
	g_me_c = 0;
	bool_me_lectura = CF_fals;
	g_me_cc = pila_inicialitzar (100, sizeof (char));
}

void
maquina_estats_finalitza (void)
{
	pila_alliberar (&g_me_cc);
}

// (comentaris)'esperat'
void
maquina_estats_comprovacio_caracter (char e, char *general, int lloc)
{
	char c;

	c = maquina_estats_caracter_sense_comentaris (general, lloc);
	maquina_estats_comprovacio_caracter_amb_2 (e, c, general, lloc);
}

// On 'p' és el primer caràcter, 's' el següent.
// (comentaris)'p'(comentaris)'s'[^:\\n]*:
void
maquina_estats_llegir_inici_final (char p, char s, char *missatge, int lloc)
{
if (verbos_maquina) printf ("M: Espera: \"%c%c[^:\\n]*:\".\n", p, s);

	maquina_estats_comprovacio_caracter (p, missatge, lloc);
	maquina_estats_comprovacio_caracter (s, missatge, lloc);
	maquina_estats_llegir_fins (':', missatge, lloc);
}

int
maquina_estats_llegir_enter (char *missatge, int lloc)
{
	char c;
if (verbos_maquina) printf("M: Espera: \"\\d+e\".\n");

	// Comprovem errors.
	if ( !isdigit((c = maquina_estats_caracter_sense_comentaris (missatge, lloc))) )
		if ( c != '-' )
		{
			printf ("E: Volíem un dígit: [0-9], i ha entrat: \'%c\'.\n", c);
			maquina_error_procedencia (missatge, lloc);
		}

	g_me_cc.us = 0;
	pila_afegir (&g_me_cc, &c);
	while ( isdigit ((c = maquina_seguent_caracter (missatge, lloc))) )
		pila_afegir (&g_me_cc, &c);

	maquina_estats_comprovacio_caracter_amb_2 ('e', c, missatge, lloc);
	pila_afegir (&g_me_cc, &end_char);
	g_me_cc.us = 0;
return atoi (g_me_cc.punter);
}

int
maquina_estats_llegir_enter_positiu (char *missatge, int lloc)
{
	int i = maquina_estats_llegir_enter (missatge, lloc);
	if ( i >= 0 ) return i;
	printf ("E: Esperàvem un dígit positiu i hem llegit: %d.\n", i);
	maquina_error_procedencia (missatge, lloc);
return i; // Treure els warnings.
}

char *
maquina_estats_cadena_caracters (char *missatge, int lloc)
{
	char c;
	enum cert_fals reverse_solidus = CF_fals;
if (verbos_maquina) printf("M: Espera: \"\"([^\\\"]|\\.)*\"\".\n");

	g_me_cc.us = 0;

	maquina_estats_comprovacio_caracter ('"', missatge, lloc);
	while ((c = maquina_seguent_caracter (missatge, lloc)) != EOF)
		if ( reverse_solidus )
		{
			reverse_solidus = CF_fals;
			pila_afegir (&g_me_cc, &c);
		}
		else if ( c == '\\' ) reverse_solidus = CF_cert;
		else if ( c == '"' ) break;
		else pila_afegir (&g_me_cc, &c);

	pila_afegir (&g_me_cc, &end_char);
	g_me_cc.us = 0;
	return g_me_cc.punter;
}

char
maquina_estats_llegir_caracter (char *missatge, int lloc)
{
	char c;

	maquina_estats_comprovacio_caracter ('\'', missatge, lloc);
	c = maquina_seguent_caracter (missatge, lloc);
	maquina_estats_comprovacio_caracter_amb_2 ('\'', maquina_seguent_caracter (missatge, lloc), missatge, lloc);

	return c;
}

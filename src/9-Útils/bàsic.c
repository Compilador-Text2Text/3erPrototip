#include <errno.h>
#include <stdarg.h>
#include <stdio.h>

#include "bàsic.h"

/************************************************/
/*	Errors					*/
/************************************************/
void // ✓
basic_error_perror (void)
{
	perror("Error:\nMostrat per perror");
	exit (EXIT_FAILURE);
}

void // ✓
basic_error (char *m, ...)
{
	va_list arg;

	fprintf (stderr, "Error:\n");

	va_start (arg, m);
	vfprintf (stderr, m, arg);
	va_end (arg);

	fprintf (stderr, ".\n");
	exit (EXIT_FAILURE);
}

/************************************************/
/*	Depurar					*/
/************************************************/
char * // ✓
basic_depurar_cert_fals (enum cert_fals e)
{
	if (e == CF_cert)
		return "Cert";
	return "Fals";
}

/************************************************/
/*	Control de memòria			*/
/************************************************/
void * // ✓
basic_malloc (size_t s)
{
	void *p;

	if (!s) return NULL;

	p = malloc (s);
	if (p != NULL) return p;

	printf ("Intent de reservar: %zu byts.\n", s);
	basic_error_perror ();
	return p; // Evitar warnings, tot i que no té sentit aquí.
}

void *
basic_realloc (void *p, size_t s)
{
	if (!s) return NULL;

	p = realloc (p, s);
	if (p != NULL) return p;

	printf ("Intent de reservar més espai: %zu byts.\n", s);
	basic_error_perror ();
	return p; // Evitar warnings, tot i que no té sentit aquí.
}

void*
basic_free (void *p)
{
	if (p != NULL) free (p);
	return NULL;
}

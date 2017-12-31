#include <stdarg.h>

#include "salts.h"
#include "sistema.h"
#include "operadors.h"
#include "mostra.h"

#include "../1-Executor/descriptor.h"
#include "../9-Útils/bàsic.h"

struct variables
sistema_definir_arguments (int num, ...)
{
	int i;
	struct variables d;
	va_list valist;

	d.mida = num;
	d.punter = basic_malloc ( num * sizeof (struct variable) );

	va_start (valist, num);
		for (i = 0; i < num; i++)
		{
			d.punter[i].nom = va_arg (valist, char *);
			d.punter[i].descriptor = va_arg (valist, struct descriptor);
			d.punter[i].usat = CF_fals;

			// Inicialitzem les variables.
			if (va_arg(valist, enum cert_fals ))
			{
				d.punter[i].valor = va_arg (valist, union valor);
				d.punter[i].inicialitzat = CF_cert;
			} else
				d.punter[i].inicialitzat = CF_fals;
		}
	va_end (valist);

	return d;
}

void
sistema_definir_funcio (enum sistema r, char *nom, int (*exec) (size_t, struct element_execucio *, struct pila *, struct base_funcio *),
	struct variables a, struct descriptor d, enum SYA s, int p, enum cert_fals o)
{
	sistemes.punter[r].funcio.nom		= nom;
	sistemes.punter[r].funcio.arguments	= a;
	sistemes.punter[r].funcio.retorn	= d;
	sistemes.punter[r].funcio.SYA		= s;
	sistemes.punter[r].funcio.precedencia	= p;
	sistemes.punter[r].funcio.optimitzable	= o;
	sistemes.punter[r].exec			= exec;
}

	/*
	SYA_funcio,
	SYA_esquerra,
	SYA_dreta
	*/
void
sistema_inicialitza (void)
{
	int i;

	sistemes.mida = Sistema_END;
	sistemes.punter = basic_malloc ( Sistema_END * sizeof (struct descriptor_sistema) );

	// Inicialitzem els nom com a referència de que no hi ha nom.
	for (i = 0; i < Sistema_END; i++)
		sistemes.punter[i].funcio.nom = NULL;

	sistema_sistema_inicialitza_sistema ();
	sistema_salts_inicialitza_sistema ();
	sistema_operadors_inicialitza_sistema ();
	sistema_mostra_inicialitza_sistema ();
}

void
sistema_finalitza (void)
{
	int i;

	for (i = 0; i < Sistema_END; i++)
		if (sistemes.punter[i].funcio.nom)
			free (sistemes.punter[i].funcio.arguments.punter);

	sistemes.mida = 0;
	free (sistemes.punter);
}

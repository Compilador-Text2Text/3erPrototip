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

	// Sistema.
	sistema_definir_funcio (Sistema_return, "return", sistema_retorn,
		sistema_definir_arguments (1,
			"retorn",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_cert, (union valor){.enter = 0}
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_exit, "exit", sistema_exit,
		sistema_definir_arguments (1,
			"sortir",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_cert, (union valor){.enter = 0}
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_obtenir_punter_de_punter, "*pp", sistema_obtenir_punter_de_punter,
		sistema_definir_arguments (1,
			"punter(2)",	(struct descriptor){.tipus = Tipus_void, .vegades_punter = 2}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 1},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_atoi, "atoi", sistema_atoi,
		sistema_definir_arguments (1,
			"convertir",	(struct descriptor){.tipus = Tipus_char, .vegades_punter = 1}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	// Salts.
	sistema_definir_funcio (Sistema_goto, "goto", sistema_goto,
		sistema_definir_arguments (1,
			"línia salt",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_gotoZ, "gotoZ", sistema_gotoZ,
		sistema_definir_arguments (2,
			"línia salt",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"condició",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_gotoNZ, "gotoNZ", sistema_gotoNZ,
		sistema_definir_arguments (2,
			"línia salt",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"condició",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	// Operacions binaries.
	sistema_definir_funcio (Sistema_igual, "=", sistema_igual,
		sistema_definir_arguments (2,
			"a",	(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0}, CF_fals,
			"b",	(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0},
		SYA_esquerra, 0, CF_cert);

	sistema_definir_funcio (Sistema_suma, "+", sistema_suma,
		sistema_definir_arguments (2,
			"a",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"b",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_dreta, 2, CF_cert);

	sistema_definir_funcio (Sistema_resta, "-", sistema_resta,
		sistema_definir_arguments (2,
			"a",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"b",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_dreta, 2, CF_cert);

	sistema_definir_funcio (Sistema_producte, "*", sistema_producte,
		sistema_definir_arguments (2,
			"a",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"b",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_dreta, 3, CF_cert);

	sistema_definir_funcio (Sistema_divisio, "/", sistema_divisio,
		sistema_definir_arguments (2,
			"a",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"b",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_dreta, 3, CF_cert);

	sistema_definir_funcio (Sistema_modul, "%", sistema_modul,
		sistema_definir_arguments (2,
			"a",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"b",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_dreta, 3, CF_cert);

	sistema_definir_funcio (Sistema_potencia, "^", sistema_potencia,
		sistema_definir_arguments (2,
			"a",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"b",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_esquerra, 4, CF_cert);

	sistema_definir_funcio (Sistema_suma_punter_punters_amb_enter, "pp+e", sistema_suma_punter_punters_amb_enter,
		sistema_definir_arguments (2,
			"p",	(struct descriptor){.tipus = Tipus_void, .vegades_punter = 1}, CF_fals,
			"e",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 1},
		SYA_esquerra, 2, CF_cert);

	sistema_definir_funcio (Sistema_mes_petit_que, "<", sistema_mes_petit_que,
		sistema_definir_arguments (2,
			"a",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals,
			"b",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_primer_resta, "--v", sistema_primer_resta,
		sistema_definir_arguments (1,
			"v",	(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	// Mostrar dades
	sistema_definir_funcio (Sistema_mostra_cadena_caracters, "printChar1", sistema_mostra_cadena_caracters,
		sistema_definir_arguments (1,
			"i",	(struct descriptor){.tipus = Tipus_char, .vegades_punter = 1}, CF_fals
			),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	/*
	Sistema_mostra_cadena_caracters,
	// Operacions infixes. (Per defecte int, si vols diferent, amb la semàntica)

		// Accés només amb la semàntica.
	Sistema_suma_float,
	Sistema_resta_float,
	Sistema_producte_float,
	Sistema_divisio_float,
	Sistema_potencia_float,

	Sistema_suma_putner_int,
	Sistema_resta_punter_int,

	// Funcions

	Sistema_END
	*/
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

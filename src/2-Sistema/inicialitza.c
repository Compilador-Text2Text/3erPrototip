#include <stdarg.h>

#include "salts.h"
#include "sistema.h"
#include "operadors.h"

#include "../1-Executor/descriptor.h"
#include "../9-Útils/bàsic.h"

struct descriptor_argument
sistema_definir_arguments (int num, ...)
{
	int i;
	struct descriptor_argument d;
	va_list valist;

	d.mida = num;
	d.punter = basic_malloc ( num * sizeof (struct descriptor) );

	va_start (valist, num);
		for (i = 0; i < num; i++)
			d.punter[i] = va_arg (valist, struct descriptor);
	va_end (valist);

	return d;
}

void
sistema_definir_funcio (enum sistema r, char *nom, int (*exec) (size_t, struct element_execucio *, struct pila *),
	struct descriptor_argument a, struct descriptor d, enum SYA s, int p, enum cert_fals o)
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
		sistema_definir_arguments (1, (struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_exit, "exit", sistema_exit,
		sistema_definir_arguments (1, (struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	// Salts.
	sistema_definir_funcio (Sistema_goto, "goto", sistema_goto,
		sistema_definir_arguments (2, (struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
			(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}),
		(struct descriptor){.tipus = Tipus_cap, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_gotoZ, "gotoZ", sistema_gotoZ,
		sistema_definir_arguments (2, (struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
			(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}),
		(struct descriptor){.tipus = Tipus_cap, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	sistema_definir_funcio (Sistema_gotoNZ, "gotoNZ", sistema_gotoNZ,
		sistema_definir_arguments (2, (struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
			(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}),
		(struct descriptor){.tipus = Tipus_cap, .vegades_punter = 0},
		SYA_funcio, 0, CF_cert);

	// Operacions binaries.
	sistema_definir_funcio (Sistema_igual, "=", sistema_igual,
		sistema_definir_arguments (2, (struct descriptor){.tipus = Tipus_void, .vegades_punter = 0},
			(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0}),
		(struct descriptor){.tipus = Tipus_void, .vegades_punter = 0},
		SYA_dreta, 2, CF_cert);

	sistema_definir_funcio (Sistema_suma, "+", sistema_suma,
		sistema_definir_arguments (2, (struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
			(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0}),
		(struct descriptor){.tipus = Tipus_int, .vegades_punter = 0},
		SYA_dreta, 2, CF_cert);

	/*
	Sistema_igual,
	// Gestió pila.
	Sistema_buit,

	// Operacions infixes. (Per defecte int, si vols diferent, amb la semàntica)
	Sistema_suma,
	Sistema_resta,
	Sistema_producte,
	Sistema_divisio,
	Sistema_potencia,

		// Accés només amb la semàntica.
	Sistema_suma_float,
	Sistema_resta_float,
	Sistema_producte_float,
	Sistema_divisio_float,
	Sistema_potencia_float,

	Sistema_suma_putner_int,
	Sistema_resta_punter_int,

	// Funcions
	Sistema_modul,

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
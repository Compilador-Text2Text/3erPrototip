#ifndef EXECUTOR_DESCRIPTOR_H_
#define EXECUTOR_DESCRIPTOR_H_

#include "../9-Útils/bàsic.h"
#include "../9-Útils/pila.h"

/************************************************/
/*	Elements bàsics				*/
/************************************************/
union
valor
{
	char caracter;
	int enter;
	float decimal;
	void *punter;
};

enum
tipus
{
	Tipus_void,
	Tipus_char,
	Tipus_int,
	Tipus_float,

	Tipus_END
};

enum
localitzacions
{
	// Dades a la paraula.
	Localitzacio_codi,

	// Dades a les variables.
	Localitzacio_arguments,
	Localitzacio_locals,
	Localitzacio_globals,

	// Crides a funcions.
	Localitzacio_funcions,
	Localitzacio_sistema,

	// Informació que no executa. (Sintaxis)
	Localitzacio_preexecucio,

	Localitzacio_END
};

enum
sistema
{
	// Retorns.
	Sistema_return,
	Sistema_exit,
	// Valors dels punters.
	Sistema_obtenir_punter_de_punter,
	// String a dígit.
	Sistema_atoi,

	// Salts.
	Sistema_goto,	// Sempre.
	Sistema_gotoZ,	// Només si és zero farà el salt.
	Sistema_gotoNZ,	// Només si no és zero farà el salt.

	// Gestió pila.
	Sistema_buit,

	// Operacions infixes. (Per defecte int, si vols diferent, amb la semàntica)
	Sistema_igual,
	Sistema_suma,
	Sistema_resta,
	Sistema_producte,
	Sistema_divisio,
	Sistema_modul,
	Sistema_potencia,
	Sistema_suma_punter_punters_amb_enter,
	// Comparadors
	Sistema_mes_petit_que,
	// Operacions d'un valor
	Sistema_primer_resta,
	Sistema_segon_resta,

	// Accés només amb la semàntica.
	Sistema_suma_float,
	Sistema_resta_float,
	Sistema_producte_float,
	Sistema_divisio_float,
	Sistema_potencia_float,

	Sistema_suma_putner_int,
	Sistema_resta_punter_int,

	// Mostrar resultats.
	Sistema_mostra_cadena_caracters,
	Sistema_mostra_enter,

	Sistema_END
};

enum
SYA
{
	SYA_funcio,
	SYA_esquerra,
	SYA_dreta,
	SYA_END
};

enum
preexecucio
{
	Preexecucio_obert, // (
	Preexecucio_coma,  // ,
	Preexecucio_tancat,// )

	Preexecucio_END
};

/************************************************/
/*	Elements avançats			*/
/************************************************/
struct
localitzat
{
	enum localitzacions on;
	size_t relatiu;
};

struct
descriptor
{
	enum tipus tipus;
	size_t vegades_punter;
};

struct
variable
{
	char *nom;			// Lèxic i depurar.

	union valor valor;		// Executar.
	struct descriptor descriptor;	// Semàntica.

	enum cert_fals inicialitzat;	// Semàntica.
	enum cert_fals usat;		// Semàntica.
};

struct
element_execucio
{
	union valor valor;		// Execució.
	struct descriptor descriptor;	// Depurar.
	void *punter;			// Execució. TODO ??
};


struct
paraula
{
	struct localitzat lloc;		// Execució, lèxic, sintaxis i semàntic.
	union valor auxiliar;		// Execució.
	struct descriptor descriptor;	// Depurar i semàntic.
};


struct
variables
{
	size_t mida;
	struct variable *punter;
};

struct
memoria_execucio
{
	size_t mida;
	size_t us;
	struct element_execucio *punter;
};

struct
frase
{
	size_t mida;
	struct paraula *punter;
};

struct
codi
{
	size_t mida;
	struct frase *punter;
};

/************************************************/
/*	Funcions				*/
/************************************************/
struct
base_funcio
{
	char *nom;				// Lèxic i depurar.

	// Semàntic.
	struct variables arguments;		// La mida ho fa anar també l'execució.
	struct descriptor retorn;

	// Shunting-yard algorithm
	enum SYA SYA;
	int precedencia;

	enum cert_fals optimitzable;		// Semàntic.
};

struct
descriptor_funcio
{
	struct base_funcio funcio;
	struct variables locals;
	size_t mida_memoria_execucio;		// Saber quanta memòria tenir preparada.
	struct codi codi;
};

struct
descriptor_sistema
{
	struct base_funcio funcio;
	int (*exec) (size_t, struct element_execucio *, struct pila *, struct base_funcio *);
};

struct
funcio_dinamica
{
	struct element_execucio *retorn;
	struct variables arguments;
	struct variables locals;
	struct memoria_execucio memoria;
	size_t cf, cp; // Comptador frase i paraula.
	struct descriptor_funcio *descriptor;
};

/************************************************/
/*	Globals					*/
/************************************************/
extern struct variables variables_globals;
extern struct llista_funcions {size_t mida; struct descriptor_funcio*punter; } funcions;
extern struct llista_sistemes {size_t mida; struct descriptor_sistema*punter;} sistemes;

#endif // EXECUTOR_DESCRIPTOR_H_

#ifndef EXECUTOR_DESCRIPTOR_H_
#define EXECUTOR_DESCRIPTOR_H_

#include "../9-Útils/bàsic.h"
#include "../9-Útils/pila.h"

/**
 * Són tots els objectes que necessitem per a fer el compilador.
 * Estan separats en diferents nivells de complexitat.
 * Al final, l'objectiu és poder treballar amb funcions i
 * que aquestes tinguin el seu codi i variables (molt resumit).
 *
 * La dificultat que hi ha, és que C no és un llenguatge
 * orientat objecte.
 */

/************************************************/
/*	Elements bàsics				*/
/************************************************/

// Valors que podem emmagatzemar.
union
valor
{
	char caracter;
	int enter;
	float decimal;
	void *punter;
};

// Elements que tindrà capacitat de treballar el intèrpret.
enum
tipus
{
	Tipus_void,
	Tipus_char,
	Tipus_int,
	Tipus_float,

	Tipus_END
};

// Permet saber dins del codi, on està la informació.
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

// Totes les funcions que té el compilador.
enum
sistema
{
	// Retorns.
	Sistema_return,
	Sistema_exit,
	// Tamany
	Sistema_sizeof,
	// Memòria
	Sistema_malloc,
	Sistema_free,
	// Valors dels punters.
	Sistema_obtenir_punter,
	Sistema_obtenir_punter_de_punter,
	Sistema_obtenir_caracter_de_punter,
	// String a dígit.
	Sistema_atoi,
	// Canvis de tipus.
	Sistema_canvi_int_char,
	Sistema_canvi_char_int,

	// Salts.
	Sistema_goto,	// Sempre.
	Sistema_gotoZ,	// Només si és zero farà el salt.
	Sistema_gotoNZ,	// Només si no és zero farà el salt.

	// Operacions infixes. (Per defecte int, si vols diferent, amb la semàntica)
	Sistema_igual,		// Variables.
	Sistema_igual_caracter,	// Accés directe a memòria.
	Sistema_suma,
	Sistema_resta,
	Sistema_producte,
	Sistema_divisio,
	Sistema_modul,
	Sistema_potencia,
	Sistema_suma_punter_punters_amb_enter,
	Sistema_suma_punter_de_cacarters,
	// Comparadors
	Sistema_mes_petit_que,
	Sistema_mes_o_igual_que,
	Sistema_igual_que,
	Sistema_diferent_que,
	Sistema_or,
	// Operacions d'un valor
	Sistema_primer_resta,
	Sistema_segon_resta,
	Sistema_sqrt,

	// Mostrar resultats.
	Sistema_mostra_cadena_caracters,
	Sistema_mostra_enter,

	Sistema_END
};

// Saber com ordenar les operacions binàries i funcions.
enum
SYA
{
	SYA_funcio,
	SYA_esquerra,
	SYA_dreta,
	SYA_END
};

// Elements que no pertanyen a l'execució del programa.
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
// Exactament on es troba.
struct
localitzat
{
	enum localitzacions on;
	size_t relatiu;
};

// Defineix que és. Si un element o un punter i quantes vegades.
struct
descriptor
{
	enum tipus tipus;
	size_t vegades_punter;
};

// Variables dins del intèrpret.
struct
variable
{
	char *nom;			// Lèxic i depurar.

	union valor valor;		// Executar.
	struct descriptor descriptor;	// Semàntica.

	enum cert_fals inicialitzat;	// Semàntica.
	enum cert_fals usat;		// Semàntica.
};

// Element per guardar els resultats de les funcions i valors del codi.
struct
element_execucio
{
	union valor valor;		// Execució.
	struct descriptor descriptor;	// Depurar.

// Quan és tracta d'una variable, escriu quina és.
// Això es fa perquè la funció de sistema (=), pugui operar correctament.
	void *punter;			// Execució.
};

// Element per saber exactament on està la informació.
// És on és guarden totes les instruccions.
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

// És una pila.
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
// Elements necessaris per la sintaxis, semàntica
// i execució en cas d'estar relacionat amb un descriptor de funció.
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

// Tota la informació estàtica per a poder ajudar a les funcions dinàmiques.
struct
descriptor_funcio
{
	struct base_funcio funcio;
	struct variables locals;
	size_t mida_memoria_execucio;		// Saber quanta memòria tenir preparada.
	struct codi codi;
};

// Funcions pròpies del intèrpret.
struct
descriptor_sistema
{
	struct base_funcio funcio;
	int (*exec) (size_t, struct element_execucio *, struct pila *, struct base_funcio *);
};

// Totes les dades que emmagatzemem per fer les funcions dinàmiques.
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

#include <stdio.h>
#include <string.h>

#include "objecte.h"
#include "maquina_estats.h"

#include "../1-Executor/descriptor.h"
#include "../6-Depurador/depurador.h"
#include "../9-Útils/bàsic.h"

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
	return Tipus_void;
}

int
lexic_definir_index_funcio (int lloc)
{
	int i;
	char *t = maquina_estats_cadena_caracters ("Buscant nom definit a funció", lloc);

	for (i = 0; i < funcions.mida; i++)
		if (funcions.punter[i].funcio.nom)
		{
			if (!strcmp (t, funcions.punter[i].funcio.nom))
				return i;
		}
		else break;

	printf ("Error: entrat: %s i esperat:\n", t);
	mostra_funcions_nom ();
	maquina_error_procedencia ("Extraient l'índex de funció", lloc);
	return 0; // Warnings.
}

enum sistema
lexic_definir_index_sistema (int lloc)
{
	int i;
	char *t = maquina_estats_cadena_caracters ("Buscant nom definit pel sistema", lloc);

	for (i = 0; i < Sistema_END; i++)
		if (sistemes.punter[i].funcio.nom)
		if (!strcmp (t, sistemes.punter[i].funcio.nom))
			return i;

	printf ("Error: entrat: %s i esperat:\n", t);
	mostra_sistema ();
	maquina_error_procedencia ("Extraient l'índex de la funció de sistema", lloc);
	return 0; // Warnings.
}

enum preexecucio
lexic_definir_index_preexecucio (int lloc)
{
	int i;
	char *t = maquina_estats_cadena_caracters ("Buscant nom definit de preexecució", lloc);

	for (i = 0; i < Preexecucio_END; i++)
		if (!strcmp (t, string_preexecucio (i)))
			return i;

	printf ("Error: entrat: %s i esperat:\n", t);
	mostra_preexecucio ();
	maquina_error_procedencia ("Extraient l'índex de la preexecució", lloc);
	return 0; // Warnings.
}

enum SYA
lexic_definir_SYA (char *t, int lloc)
{
	int i;

	for (i = 0; i < SYA_END; i++)
		if (!strcmp(t, string_SYA (i)))
			return i;

	printf ("ERROR: Entrat: \"%s\" i esperat:\n", t);
	mostra_SYA ();
	maquina_error_procedencia ("Extraient com és comporta amb el SYA", lloc);
	return 0;
}

enum localitzacions
lexic_definir_localitzacio (int lloc)
{
	int i;
	char *t = maquina_estats_cadena_caracters ("Localització", lloc);

	for (i = 0; i < Localitzacio_END; i++)
		if (!strcmp(t, string_localitzacio (i)))
			return i;

	printf ("ERROR: Entrat: \"%s\" i esperat:\n", t);
	mostra_localitzacions ();
	maquina_error_procedencia ("Saben de on és la informació", lloc);
	return 0;
}

int
lexic_definir_index_variable (struct variables *vs, int lloc)
{
	int i;
	char *t = maquina_estats_cadena_caracters ("TODO", lloc);

	for (i = 0; i < vs->mida; i++)
		if (!strcmp(t, vs->punter[i].nom))
			return i;

	printf ("ERROR: Entrat: \"%s\" i esperat:\n", t);
	mostra_variables (vs);
	maquina_error_procedencia ("Saben de on és la informació", lloc);
	return 0;
}

int
lexic_llegir_digit_positiu_entre_parentesis (char *missatge, int lloc)
{
	int o;

	maquina_estats_comprovacio_caracter ('(', "Parèntesis per descriure", lloc);
	o = maquina_estats_llegir_enter_positiu (missatge, lloc);
	maquina_estats_comprovacio_caracter (')', "Parèntesis per descriure", lloc);

	return o;
}

struct descriptor
lexic_definir_descriptor (int lloc)
{
	char *t;
	struct descriptor d;

	t = maquina_estats_cadena_caracters ("Definint tipus", lloc);
	d.tipus = lexic_definir_tipu (t, "Investigant el tipus", lloc);
	d.vegades_punter = lexic_llegir_digit_positiu_entre_parentesis ("Vegades punter", lloc);
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
		printf ("ERROR: Entrat: %c.\n", c);
		maquina_error_procedencia ("Esperàvem si inicialitzava la variable, llavors tenia que entrar: [:;]", lloc);
	}
if (verbos_objecte) {printf ("L: "); mostra_variable (v);}
}

void
lexic_variables_i_declarar (char b, struct variables *vs, char *missatge, int lloc)
{
	struct variable *v;

if (verbos_objecte) printf ("L: Variables i declarar → %s.\n", missatge);
	maquina_estats_llegir_inici_final ('-', b, missatge, lloc);

	vs->mida = maquina_estats_llegir_enter_positiu ("Definint el nombre de variables", lloc);
	vs->punter = basic_malloc ( vs->mida * sizeof (struct variable) );
if (verbos_objecte) printf ("L: Un total de: %ld variables.\n", vs->mida);

	for (v = vs->punter; v < vs->punter +vs->mida; v++)
		lexic_definir_variable (v, lloc);
}

/*
struct localitzat lloc;		// Execució, lèxic, sintaxis i semàntic.
union valor auxiliar;		// Execució.
struct descriptor descriptor;	// Depurar i semàntic.
*/
void
lexic_definir_paraula (struct paraula *p, int lloc)
{
	p->lloc.on = lexic_definir_localitzacio (lloc);

	switch (p->lloc.on)
	{
	case Localitzacio_codi:
		p->lloc.relatiu = 0;
		p->descriptor = lexic_definir_descriptor (lloc);
		p->auxiliar = lexic_definir_valor (p->descriptor, "Definint valor de la paraula", lloc);
		break;

	case Localitzacio_arguments:
		p->lloc.relatiu = lexic_definir_index_variable (&funcions.punter[lloc].funcio.arguments, lloc);
		p->descriptor = funcions.punter[lloc].funcio.arguments.punter[p->lloc.relatiu].descriptor;
		p->auxiliar.enter = 0;
		break;

	case Localitzacio_locals:
		p->lloc.relatiu = lexic_definir_index_variable (&funcions.punter[lloc].locals, lloc);
		p->descriptor = funcions.punter[lloc].locals.punter[p->lloc.relatiu].descriptor;
		p->auxiliar.enter = 0;
		break;

	case Localitzacio_globals:
		p->lloc.relatiu = lexic_definir_index_variable (&variables_globals, lloc);
		p->descriptor = variables_globals.punter[p->lloc.relatiu].descriptor;
		p->auxiliar.enter = 0;
		break;

	case Localitzacio_funcions:
		p->lloc.relatiu = lexic_definir_index_funcio (lloc);
		p->descriptor = funcions.punter[p->lloc.relatiu].funcio.retorn;
		p->auxiliar.enter = 0; // És definirà a la sintàxis.
		break;

	case Localitzacio_sistema:
		p->lloc.relatiu = lexic_definir_index_sistema (lloc);
		p->descriptor = sistemes.punter[p->lloc.relatiu].funcio.retorn;
		p->auxiliar.enter = 0; // És definirà a la sintàxis.
		break;

	case Localitzacio_preexecucio:
		p->lloc.relatiu = lexic_definir_index_preexecucio (lloc);
		p->descriptor.tipus = p->descriptor.vegades_punter = p->auxiliar.enter = 0;
		p->auxiliar.enter = 0; // Serà eliminat a la sintàxis.
		break;

	default:
		printf ("ERROR: Entrat: %d < %d.\n", p->lloc.on, Localitzacio_END);
		maquina_error_procedencia ("Esperàvem si estava inicialitzada la funció, llavors tenia que entrar: '[dn]'", lloc);
	}

	maquina_estats_comprovacio_caracter (';', "Finalitzador de paraula", lloc);
if (verbos_objecte) {printf ("L: Paraula: "); mostra_paraula (p, lloc);}
}

void
lexic_definir_frase (struct frase *f, int lloc)
{
	struct paraula *p;
if (verbos_objecte) printf ("L: Definim una frase.\n");

	maquina_estats_llegir_inici_final ('-', 'f', "Definint paraules del codi (-f:)", lloc);
	f->mida = maquina_estats_llegir_enter_positiu ("Definint el nombre de paraules", lloc);
	f->punter = basic_malloc (f->mida * sizeof (struct paraula));

	for (p = f->punter; p < f->punter +f->mida; p++)
		lexic_definir_paraula (p, lloc);
}

int
lexic_definir_codi (struct codi *c, int lloc)
{
	int m = 0;
	struct frase *f;
if (verbos_objecte) printf ("L: Definim el codi.\n");

	maquina_estats_llegir_inici_final ('-', 'c', "Definint frases del codi", lloc);
	c->mida = maquina_estats_llegir_enter_positiu ("Definint el nombre de frases", lloc);
	c->punter = basic_malloc (c->mida * sizeof (struct frase));

	for (f = c->punter; f < c->punter +c->mida; f++)
	{
		lexic_definir_frase (f, lloc);
		m = MAX (m, f->mida);
	}

	return m;
}

int
lexic_funcio (int definits, int *restants, int *nous, int lloc)
{
	int i;
	char c;
	struct descriptor_funcio *f;

if (verbos_objecte) printf ("L: Declarant la funció.\n");
	maquina_estats_llegir_inici_final ('<', 'F', "Declarar la funció", lloc);

	switch ((c = maquina_estats_llegir_caracter ("Mirant si està inicialitzada la funció", lloc)))
	{
	case 'd':
if (verbos_objecte) printf ("L: Funció declarada, ara la definirem.\n");
		(*restants)--;
		i = lexic_definir_index_funcio (lloc);
		f = funcions.punter +i;
		break;

	case 'n':
if (verbos_objecte) printf ("L: Funció nova, ara la definirem.\n");
		i = definits +*nous;
		(*nous)++;
		if ( i >= funcions.mida )
		{
			printf ("ERROR: Demanat %d < %ld. On són punters relatius de les funcions.\n", i, funcions.mida);
			maquina_error_procedencia ("Índex major al nombre total de funcions possibles", lloc);
		}
		f = funcions.punter +i;
		f->funcio.nom = strdup (maquina_estats_cadena_caracters ("Definint nom", lloc));
		break;

	default:
		printf ("ERROR: Entrat: %c.\n", c);
		maquina_error_procedencia ("Esperàvem si estava inicialitzada la funció, llavors tenia que entrar: '[dn]'", lloc);
	}

	f->funcio.retorn = lexic_definir_descriptor (lloc);
	f->funcio.SYA = lexic_definir_SYA (maquina_estats_cadena_caracters ("Definint si és operant o funció", lloc), lloc);
	f->funcio.precedencia = f->funcio.SYA == SYA_funcio ? 0 : lexic_llegir_digit_positiu_entre_parentesis ("Definint precedència", lloc);

	lexic_variables_i_declarar ('a', &f->funcio.arguments, "Arguments", -1);
	lexic_variables_i_declarar ('l', &f->locals, "Locals", -1);

	f->mida_memoria_execucio = lexic_definir_codi (&f->codi, lloc);
if (verbos_objecte) { printf ("L: "); mostra_funcio (f);}
	return f->mida_memoria_execucio;
}

int
lexic_funcions (void)
{
	int mida, i, max = 0, aux;
	int nous, restants;
	struct descriptor_funcio *f;

if (verbos_objecte) printf ("L: Funcions.\n");
	maquina_estats_llegir_inici_final ('-', 'f', "Definint nombre total de funcions", -1);

	funcions.mida = maquina_estats_llegir_enter_positiu ("Definint el nombre de funcions", -1);
	funcions.punter = basic_malloc (funcions.mida * sizeof (struct descriptor_funcio));
if (verbos_objecte) printf ("L: Un total de: %ld funcions.\n", funcions.mida);

	// Inicialitzem els valors.
	for (f = funcions.punter; f < funcions.punter +funcions.mida; f++)
	{
		f->funcio.nom	= NULL;
		f->funcio.arguments.mida	= 0;
		f->funcio.arguments.punter	= NULL;
		f->funcio.retorn.vegades_punter	= 0;
		f->funcio.retorn.tipus		= Tipus_END;
		f->funcio.SYA	= SYA_END;
		f->funcio.precedencia		= 0;
		f->funcio.optimitzable		= CF_fals;
		f->codi.mida	= 0;
		f->codi.punter	= NULL;
		f->mida_memoria_execucio = 0;
		f->locals.mida	= 0;
		f->locals.punter= NULL;
	}

	maquina_estats_llegir_inici_final ('-', 'd', "Declarant el nombre de funcions pre-inicialitzades", -1);
	restants = mida = maquina_estats_llegir_enter_positiu ("Definir el nombre de noms abans de compilar", -1);
if (verbos_objecte) printf ("L: Un total de: %d definir noms abans de compilar.\n", mida);

	if (funcions.mida < mida)
	{
		printf ("ERROR: Ha dit que hi haurà: %ld i vols declarar: %d.\n", funcions.mida, mida);
		maquina_error_procedencia ("No pot declarar més funcions de les que ha dit que hi haurà", -1);
	}
	for (f = funcions.punter; f < funcions.punter +mida; f++)
		f->funcio.nom = strdup (maquina_estats_cadena_caracters ("Definint nom", -1));

	nous = 0;
	for (i = 0; i < funcions.mida; i++)
	{
		aux = lexic_funcio (mida, &restants, &nous, i);
		max = MAX (max, aux);
	}

	return aux;
}

int
lexic_llegir_objecte (char (*funcio) (void), enum cert_fals fem_verbos, enum cert_fals maquina_estats)
{
	int i;

	// Definim.
	verbos_objecte = fem_verbos;
	maquina_estats_inicialitza (funcio, maquina_estats);

	// Lèxic.
if (verbos_objecte) printf ("L: Llegir objecte.\n");
	lexic_variables_i_declarar ('v', &variables_globals, "Variables globals", -1);
	i = lexic_funcions ();

	maquina_estats_finalitza ();

	return i;
}

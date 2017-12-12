#include <stdio.h>

#include "depurador.h"

#include "../1-Executor/descriptor.h"

/* enum a cadena de caràcters */
char *
string_localitzacio (enum localitzacions e)
{
	switch (e)
	{
	case Localitzacio_codi:		return "Codi";
	case Localitzacio_arguments:	return "Arguments";
	case Localitzacio_locals:	return "Locals";
	case Localitzacio_globals:	return "Globals";
	case Localitzacio_funcions:	return "Funcions";
	case Localitzacio_sistema:	return "Sistema";
	case Localitzacio_preexecucio:	return "Preexecució";
	case Localitzacio_END:		return "Fi";
	default:
		basic_error ("String localització, esperat un valor menor que: %d, entrat: %d", Localitzacio_END, e);
		return "ERROR"; // Només posat perquè deixes de donar warning.
	}
}

char *
string_tipu (enum tipus e)
{
	switch (e)
	{
	case Tipus_cap:		return "NT";
	case Tipus_void:	return "Void";
	case Tipus_char:	return "Char";
	case Tipus_int:		return "Int";
	case Tipus_float:	return "Float";
	case Tipus_pointer:	return "Punter";
	case Tipus_END:		return "Fi";
	default:
		basic_error ("String tipus, esperat un valor menor que: %d, entrat: %d", Tipus_END, e);
		return "ERROR"; // Només posat perquè deixes de donar warning.
	}
}

char *
string_SYA (enum SYA e)
{
	switch (e)
	{
	case SYA_funcio:	return "Funció";
	case SYA_esquerra:	return "Associativa per l'esquerra";
	case SYA_dreta:		return "Associativa per la dreta";
	default:
		basic_error ("String SYA, esperat un valor menor que: %d, entrat: %d", SYA_END, e);
		return "ERROR"; // Només posat perquè deixes de donar warning.
	}
}

char *
string_preexecucio (enum preexecucio e)
{
	switch (e)
	{
	case Preexecucio_obert:		return "(";
	case Preexecucio_coma:		return ",";
	case Preexecucio_tancat:	return ")";
	default:
		basic_error ("String preexecució, esperat un valor menor que: %d, entrat: %d", Preexecucio_END, e);
		return "ERROR"; // Només posat perquè deixes de donar warning.
	}
}

void
mostra_SYA (void)
{
	int i;

	printf ("Shunting-yard algorithm:\n");
	for (i = 0; i < SYA_END; i++)
		printf ("%2d \"%s\"\n", i, string_SYA (i));
}

void
mostra_preexecucio (void)
{
	int i;
	printf ("Elements de preexecució:\n");
	for (i = 0; i < Preexecucio_END; i++)
		printf ("%2d \"%s\"\n", i, string_preexecucio (i));
}

/* Mostra dades interessants */
void
mostra_localitzacions (void)
{
	int i;

	printf ("Localitzacions:\n");
	for (i = 0; i <= Localitzacio_END; i++)
		printf ("%2d \"%s\"\n", i, string_localitzacio (i));
}

void
mostra_tipu (struct descriptor d)
{
	printf ("%s(%ld)", string_tipu (d.tipus), d.vegades_punter);
}

void
mostra_tipus (void)
{
	int i;

	printf ("Tipus:\n");
	for (i = 0; i <= Tipus_END; i++)
		printf ("%2d \"%s\"\n", i, string_tipu (i));
}

void
mostra_argument (struct variable *v)
{
	printf ("\"%s\" ", v->nom);
	mostra_tipu (v->descriptor);
}

void
mostra_base_funcio (struct base_funcio *b)
{
	int i;

	if (b->SYA == SYA_funcio)
	{
		mostra_tipu (b->retorn);
		printf ("\t%10s\t(", b->nom);

		if (b->arguments.mida)
			mostra_argument (&b->arguments.punter[0]);

		for (i = 1; i < b->arguments.mida; i++)
		{
			printf (", ");
			mostra_argument (&b->arguments.punter[i]);
		}
		printf (")");
	}else
	{
		if (b->arguments.mida != 2)
			basic_error ("D'un operant esperem 2 arguments. Aquest en té %d", b->arguments.mida);

		mostra_tipu (b->arguments.punter[0].descriptor);
		printf (" %s ", b->nom);
		mostra_tipu (b->arguments.punter[1].descriptor);
		printf ("\t| %s amb precedència: %d", string_SYA (b->SYA), b->precedencia);
	}
	printf ("\n");
}

void
mostra_sistema (void)
{
	int i;

	printf ("Funcions de sistema:\n");
	for (i = 0; i < Sistema_END; i++)
	{
		printf ("%2d ", i);
		if (sistemes.punter[i].funcio.nom)
			mostra_base_funcio (&sistemes.punter[i].funcio);
		else
			printf ("NULL\n");
	}
}

void
mostra_valor (struct descriptor d, union valor v)
{
	if (d.vegades_punter)
	{
		if ((d.tipus == Tipus_char) && (d.vegades_punter == 1))
			printf ("\"%s\"", (char *)v.punter);
		else
		{
			printf ("ERROR: No sabem mostrar el valor de: %s(%ld).\n", string_tipu(d.tipus), d.vegades_punter);
			exit (EXIT_FAILURE);
		}
		return;
	}
	switch (d.tipus)
	{
	case Tipus_char:	printf ("'%c'", v.caracter);	break;
	case Tipus_int:		printf ("%de", v.enter);	break;
	default:
		printf ("ERROR: No sabem mostrar el valor de: %s(%ld).\n", string_tipu(d.tipus), d.vegades_punter);
		exit (EXIT_FAILURE);
	}
}

void
mostra_variable (struct variable *v)
{
	printf ("\"%s\" \"%s\"(%ld)", v->nom, string_tipu (v->descriptor.tipus), v->descriptor.vegades_punter);
	if (v->inicialitzat)
		mostra_valor (v->descriptor, v->valor);
	else
		printf ("No inicialitzat");
	printf (".\n");
}

void
mostra_variables (struct variables *vs)
{
	struct variable *v;

	for (v = vs->punter; v < vs->punter +vs->mida; v++)
		mostra_variable (v);
}

void
mostra_funcions_nom (void)
{
	struct descriptor_funcio *f;

	for (f = funcions.punter; f < funcions.punter + funcions.mida; f++)
		if (f->funcio.nom)
			printf (" \"%s\"\n", f->funcio.nom);
		else break;
}

void
mostra_paraula (struct paraula *p, int lloc)
{
	printf ("\"%s\" ", string_localitzacio (p->lloc.on));

	switch (p->lloc.on)
	{
	case Localitzacio_codi:
		mostra_valor (p->descriptor, p->auxiliar);
		printf (".\n");
		break;

	case Localitzacio_arguments:
		mostra_variable (&funcions.punter[lloc].funcio.arguments.punter[p->lloc.relatiu]);
		break;

	case Localitzacio_locals:
		mostra_variable (&funcions.punter[lloc].locals.punter[p->lloc.relatiu]);
		break;

	case Localitzacio_globals:
		mostra_variable (&variables_globals.punter[p->lloc.relatiu]);
		break;

	case Localitzacio_funcions:
		mostra_base_funcio (&funcions.punter[p->lloc.relatiu].funcio);
		break;

	case Localitzacio_sistema:
		mostra_base_funcio (&sistemes.punter[p->lloc.relatiu].funcio);
		break;

	case Localitzacio_preexecucio:
		printf ("\"%s\".\n", string_preexecucio (p->lloc.relatiu));
		break;

	default:
		basic_error ("ERROR: No sabem on està localitzada la informació de la paraula");
	}
}

void
mostra_funcio (struct descriptor_funcio *f)
{
	mostra_base_funcio (&f->funcio);
}

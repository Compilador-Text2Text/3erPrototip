#include <stdio.h>

#include "depurador.h"

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
mostra_base_funcio (struct base_funcio *b)
{
	int i;

	if (b->SYA == SYA_funcio)
	{
		mostra_tipu (b->retorn);
		printf ("\t%s (", b->nom);
		if (b->arguments.mida)
			mostra_tipu (b->arguments.punter[0]);
		for (i = 1; i < b->arguments.mida; i++)
		{
			printf (", ");
			mostra_tipu (b->arguments.punter[i]);
		}
		printf (")");
	}else
	{
		if (b->arguments.mida != 2)
			basic_error ("D'un operant esperem 2 arguments. Aquest en té %d", b->arguments.mida);

		mostra_tipu (b->arguments.punter[0]);
		printf (" %s ", b->nom);
		mostra_tipu (b->arguments.punter[1]);
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

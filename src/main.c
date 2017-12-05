#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "0-Inicialitzador/inicialitza.h"
#include "9-Útils/bàsic.h"

void
main_mostra_ajuda (void)
{
	printf ("Ha premut '-h', aquí té la informació demanda:\n");
	printf (" '-q'\tTreure el missatge per defecte del main.\n");
	printf (" '-h'\tMostra aquest missatge i surt.\n");
	printf (" '-hf'\tMostra la informació de les funcions de sistema.\n");
	printf (" '-v'\tMostra tots els detalls de tots els passos (lèxic, sintàctic i execució).\n");
	printf (" '-vl'\tMostra tots els detalls del lèxic.\n");
	printf (" '-vs'\tMostra tots els detalls de la sintaxis.\n");
	printf (" '-ve'\tMostra tots els detalls de l'execució.\n");
	printf (" '-f'\tDemana el nom d'un fitxer (serà el que compilarà i executarà).\n");
	printf (" '-a'\tDemana el nombre d'arguments i tot seguit els mateixos.\n");
	exit (EXIT_SUCCESS);
}

void // ✓
main_mostra_ajuda_funcions (void)
{
	inicialitza_mostra_sistema ();
	exit (EXIT_SUCCESS);
}

void // ✓
main_error (char *m, char *n)
{
	if (n) fprintf (stderr, "Instrucció entrada: '%s'.\n", n);
	fprintf (stderr, "Per a més informació premi '-h'.\n");
	basic_error (m);
}

// Cridat al prémer '-f'
void // ✓
main_nombrar_nom (int i, char **argv, int argc, char **nom)
{
	if ( i < argc )
		*nom = argv[i];
	else
		main_error ("Tot seguit '-f' ha d'haver el nom del fitxer a llegir", NULL);
}

// Cridat al prémer '-a'
int // ✓
main_definir_arguments (int i, char **argv, int argc, int *nombre_arguments, char ***arguments)
{
	if ( i >= argc ) main_error ("Tot seguit '-a' ha d'haver el nombre d'arguments a llegir", NULL);

	*nombre_arguments = atoi (argv[i]);
	*arguments = argv + i +1;
	i += *nombre_arguments;

	if ( i >= argc ) main_error ("En '-a', necessitem el nombre d'arguments demanats", NULL);

	return i;
}

int
main (int argc, char *argv[])
{
	int out, i;

	enum cert_fals verbos_lexic	= CF_fals;
	enum cert_fals verbos_sintactic	= CF_fals;
	enum cert_fals verbos_execucio	= CF_fals;
	enum cert_fals verbos_main	= CF_cert;

	char *nom		= NULL;
	int nombre_arguments	= 0;
	char **arguments	= NULL;

	for ( i = 1; i < argc; i++ )
	{
		if	( !strcmp ("-q", argv[i])  )
			verbos_main	= CF_fals;
		else if ( !strcmp ("-h", argv[i])  )
			main_mostra_ajuda ();
		else if ( !strcmp ("-hf", argv[i])  )
			main_mostra_ajuda_funcions ();
		else if ( !strcmp ("-v", argv[i])  )
			verbos_lexic = verbos_sintactic = verbos_execucio = CF_cert;
		else if ( !strcmp ("-vl", argv[i]) )
			verbos_lexic	= CF_cert;
		else if ( !strcmp ("-vs", argv[i]) )
			verbos_sintactic= CF_cert;
		else if ( !strcmp ("-ve", argv[i]) )
			verbos_execucio	= CF_cert;
		else if ( !strcmp ("-f", argv[i])  )
			main_nombrar_nom (++i, argv, argc, &nom);
		else if ( !strcmp ("-a", argv[i])  )
			i = main_definir_arguments (++i, argv, argc, &nombre_arguments, &arguments);
		else
			main_error ("Ordre desconeguda", argv[i]);
	}


	if (nom == NULL) main_error ("Ha de definir que vol executar '-f'", NULL);

	inicialitza_inicialitza_funcions_sistema ();
	out = inicializa_lectura_objecte (nom, nombre_arguments, arguments, verbos_lexic, verbos_sintactic, verbos_execucio);
	inicialitza_finalitza_funcions_sistema ();

	if (verbos_main)
	{
		printf ("Interpretat:\n");
		printf ("-Verbós lèxic:\t\t%s\n", basic_depurar_cert_fals (verbos_lexic) );
		printf ("-Verbós sintàctic:\t%s\n", basic_depurar_cert_fals (verbos_sintactic) );
		printf ("-Verbós execució:\t%s\n", basic_depurar_cert_fals (verbos_execucio) );
		printf ("-Nom fitxer:\t\t\"%s\"\n", nom);
		printf ("-Sortida: %d\n", out);
		printf ("-Nombre d'arguments: %d\n", nombre_arguments);
		for (i = 0; i < nombre_arguments; i++)
			printf ("%3d \"%s\"\n", i, arguments[i]);
	}

	return out;
}

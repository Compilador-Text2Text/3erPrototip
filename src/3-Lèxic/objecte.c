#include "objecte.h"
#include "maquina_estats.h"

#include "../1-Executor/descriptor.h"
#include "../9-Útils/pila.h"

struct pila e_p; // Variable global externa pila, per llegir noms.
enum cert_fals verbos; // Per saber si continuem sent verbosos.

void
lexic_variables_i_declarar (struct variables *vs, char *m_error, int lloc)
{
	maquina_estats_llegir_inici_final ('-', 'v', m_error, lloc);
}

enum cert_fals
lexic_llegir_objecte (char (*funcio) (void), enum cert_fals fem_verbos)
{
	verbos = fem_verbos;
	maquina_estats_descriu_funcio (funcio);
	e_p = pila_inicialitzar (100, sizeof (char));
		lexic_variables_i_declarar (&variables_globals, "Declarant les variables globals", -1);
	pila_alliberar (&e_p);
	return CF_fals;
}

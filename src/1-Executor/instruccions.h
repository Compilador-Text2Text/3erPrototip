#ifndef EXECUTOR_INSTRUCCIONS_H_
#define EXECUTOR_INSTRUCCIONS_H_

#include "descriptor.h"

// Només serveix per dir si volem que sigui verbos o no l'execució.
void instruccio_inicialitzada (enum cert_fals ve);

// Com que no té un inicialitzador, hereta el problema al inicialitzador.
// Però perquè aquest pugui funcionar necessita poder crear funcions.
void instruccions_crear_nova_funcio_dinamica
(size_t nombre_arguments, struct element_execucio *retorn, size_t funcio_relativa, struct pila *guarda_resultat);

// Instrucció elemental per a poder executar una instrucció.
// Té dependència amb l'argument, aquest l'hi indicarà exactament que ha de fer.
// Aquest format dona la flexibilitat a paral·lelisme o a simular manualment un
// paral·lelisme.
int instruccio_execucio_paraula (struct pila *pf);

#endif // EXECUTOR_INSTRUCCIONS_H_

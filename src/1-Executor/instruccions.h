#ifndef EXECUTOR_INSTRUCCIONS_H_
#define EXECUTOR_INSTRUCCIONS_H_

#include "descriptor.h"

void instruccio_inicialitzada (enum cert_fals ve);

void instruccions_crear_nova_funcio_dinamica
(size_t nombre_arguments, struct element_execucio *retorn, size_t funcio_relativa, struct pila *guarda_resultat);

int instruccio_execucio_paraula (struct pila *pf);

#endif // EXECUTOR_INSTRUCCIONS_H_

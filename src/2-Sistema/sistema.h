#ifndef SISTEMA_SISTEMA_H_
#define SISTEMA_SISTEMA_H_

#include "../1-Executor/descriptor.h"
#include "../9-Útils/pila.h"

int sistema_retorn	(size_t, struct element_execucio *, struct pila *, struct base_funcio *);
int sistema_exit	(size_t, struct element_execucio *, struct pila *, struct base_funcio *);

int sistema_atoi	(size_t, struct element_execucio *, struct pila *, struct base_funcio *);
#endif // SISTEMA_SISTEMA_H_

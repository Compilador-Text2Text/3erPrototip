#ifndef SISTEMA_OPERADORS_H_
#define SISTEMA_OPERADORS_H_

#include "../1-Executor/descriptor.h"
#include "../9-Útils/pila.h"

int sistema_igual	(size_t, struct element_execucio *, struct pila *, struct base_funcio *);

int sistema_suma	(size_t, struct element_execucio *, struct pila *, struct base_funcio *);
int sistema_resta	(size_t, struct element_execucio *, struct pila *, struct base_funcio *);

int sistema_producte	(size_t, struct element_execucio *, struct pila *, struct base_funcio *);
int sistema_divisio	(size_t, struct element_execucio *, struct pila *, struct base_funcio *);

int sistema_potencia	(size_t, struct element_execucio *, struct pila *, struct base_funcio *);

#endif // SISTEMA_OPERADORS_H_

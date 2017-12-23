#ifndef SISTEMA_SALTS_H_
#define SISTEMA_SALTS_H_

#include "../1-Executor/descriptor.h"
#include "../9-Útils/pila.h"

int sistema_goto   (size_t, struct element_execucio *, struct pila *, struct base_funcio *);
int sistema_gotoZ  (size_t, struct element_execucio *, struct pila *, struct base_funcio *);
int sistema_gotoNZ (size_t, struct element_execucio *, struct pila *, struct base_funcio *);

#endif // SISTEMA_SALTS_H_

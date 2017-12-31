#ifndef SISTEMA_INICIALITZADOR_H_
#define SISTEMA_INICIALITZADOR_H_

void sistema_inicialitza (void);
void sistema_finalitza (void);

void sistema_definir_funcio (enum sistema r, char *nom, int (*exec) (size_t, struct element_execucio *, struct pila *, struct base_funcio *), struct variables a, struct descriptor d, enum SYA s, int p, enum cert_fals o);
struct variables sistema_definir_arguments (int num, ...);

#endif // SISTEMA_INICIALITZADOR_H_

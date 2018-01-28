#ifndef SISTEMA_INICIALITZADOR_H_
#define SISTEMA_INICIALITZADOR_H_

// Fa les crides per generar totes les funcions del sistema.
void sistema_inicialitza (void);
// Allibera totes les funcions del sistema.
void sistema_finalitza (void);

// Permet omplir la memòria inicialitzada.
void sistema_definir_funcio (enum sistema r, char *nom, int (*exec) (size_t, struct element_execucio *, struct pila *, struct base_funcio *), struct variables a, struct descriptor d, enum SYA s, int p, enum cert_fals o);
// Permet definir correctament els arguments de les funcions.
struct variables sistema_definir_arguments (int num, ...);

#endif // SISTEMA_INICIALITZADOR_H_

#ifndef DEPURADOR_DEPURADOR_H_
#define DEPURADOR_DEPURADOR_H_

#include "../1-Executor/descriptor.h"

char * string_localitzacio (enum localitzacions);
char * string_tipu (enum tipus);
char * string_SYA (enum SYA);
char * string_preexecucio (enum preexecucio e);

void mostra_tipu (struct descriptor);
void mostra_base_funcio (struct base_funcio *);
void mostra_valor (struct descriptor d, union valor v);
void mostra_paraula (struct paraula *p, int lloc);

void mostra_variable  (struct variable  *v );
void mostra_variables (struct variables *vs);
void mostra_funcions_nom (void);
void mostra_funcio (struct descriptor_funcio *f);

void mostra_localitzacions (void);
void mostra_tipus (void);
void mostra_SYA (void);
void mostra_sistema (void);
void mostra_preexecucio (void);

#endif // DEPURADOR_DEPURADOR_H_

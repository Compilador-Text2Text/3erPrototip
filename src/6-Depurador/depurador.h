#ifndef DEPURADOR_DEPURADOR_H_
#define DEPURADOR_DEPURADOR_H_

#include "../1-Executor/descriptor.h"

char * string_localitzacio (enum localitzacions);
char * string_tipu (enum tipus);
char * string_SYA (enum SYA);

void mostra_tipu (struct descriptor);
void mostra_base_funcio (struct base_funcio *);

void mostra_localitzacions (void);
void mostra_tipus (void);
void mostra_sistema (void);

#endif // DEPURADOR_DEPURADOR_H_

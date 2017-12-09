#ifndef LEXIC_MAQUINA_ESTATS_H_
#define LEXIC_MAQUINA_ESTATS_H_

#include "../9-Útils/bàsic.h"

void maquina_estats_inicialitza (char (*) (void), enum cert_fals verbos);
void maquina_estats_finalitza (void);

void maquina_estats_llegir_inici_final (char p, char s, char *m_error, int lloc);
int maquina_estats_llegir_enter_positiu (char *missatge, int lloc);

#endif // LEXIC_MAQUINA_ESTATS_H_

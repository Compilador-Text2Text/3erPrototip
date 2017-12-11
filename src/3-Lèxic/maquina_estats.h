#ifndef LEXIC_MAQUINA_ESTATS_H_
#define LEXIC_MAQUINA_ESTATS_H_

#include "../9-Útils/bàsic.h"

// Errors.
void maquina_error_procedencia (char *general, int lloc);

// Començar i acabar.
void maquina_estats_inicialitza (char (*) (void), enum cert_fals verbos);
void maquina_estats_finalitza (void);

// Maquina d'estats pròpiament dit.
void maquina_estats_comprovacio_caracter (char e, char *general, int lloc);
void maquina_estats_llegir_inici_final (char p, char s, char *m_error, int lloc);
char maquina_estats_caracter_sense_comentaris (char *general, int lloc);
char maquina_estats_llegir_caracter (char *missatge, int lloc);
char* maquina_estats_cadena_caracters (char *missatge, int lloc);
int maquina_estats_llegir_enter (char *missatge, int lloc);
int maquina_estats_llegir_enter_positiu (char *missatge, int lloc);

#endif // LEXIC_MAQUINA_ESTATS_H_

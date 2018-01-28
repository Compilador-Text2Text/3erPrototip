#ifndef LEXIC_OBJECTE_H_
#define LEXIC_OBJECTE_H_

#include "../9-Útils/bàsic.h"

// Retorna la llargada màxima de frase. (Tot seguit fer el SYA).
// També és fa responsable d'omplir els objectes de l'estructura per un futur ser executat.
int lexic_llegir_objecte (char (*) (void), enum cert_fals verbos, enum cert_fals verbos_maquina_estats);

#endif // LEXIC_OBJECTE_H_

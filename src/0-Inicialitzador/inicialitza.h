#ifndef INICIALITZADOR_INICIALITZA_H_
#define INICIALITZADOR_INICIALITZA_H_

#include "../9-Útils/bàsic.h"

/* Llegeix i executa totes les instruccions que hi hagi al codi */
int inicialitza_lectura_objecte (char *nom, int argc, char **argv, enum cert_fals vl, enum cert_fals vm, enum cert_fals vs, enum cert_fals va, enum cert_fals ve);

/* Permet tota la informació que té el compilador: Localitzacions, Tipus i Funcions de sistema */
void inicialitza_mostra_sistema (void);

#endif // INICIALITZADOR_INICIALITZA_H_

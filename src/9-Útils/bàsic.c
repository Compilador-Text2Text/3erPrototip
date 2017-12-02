#include <stdio.h>

#include "bàsic.h"

char *
depurar_cert_fals (enum cert_fals e)
{
	if (e == CF_cert)
		return "Cert";
	return "Fals";
}

#include <stdarg.h>
#include <stdio.h>

char (*seguent_caracter) (void);

/************************************************/
/*	Funcions privades			*/
/************************************************/

// [^'f'\\n]*'f'
void
maquina_estats_llegir_fins (char f, char *general, int lloc, char *concret, va_list arg)
{
	char c;

	while ((c = seguent_caracter()) != EOF)
		if	(c == f	  ) return;
		else if	(c == '\n') break;
}

char
maquina_estats_llegir_linia_privada (char *general, int lloc, char *concret, va_list arg)
{
	char c;

	while ((c = seguent_caracter()) != EOF)
		switch (c)
		{
		case '#': maquina_estats_llegir_fins ('\n', general, lloc, concret, arg);
		}
	return c;
}

void
maquina_estats_comprovacio_caracter_amb_2 (char c, char e, char *m_error, int lloc, char *concret, va_list arg)
{
}

/************************************************/
/*	Funcions públiques			*/
/************************************************/
void
maquina_estats_descriu_funcio (char (*funcio) (void))
{
	seguent_caracter = funcio;
}

char
maquina_estats_llegir_linia (char *general, int lloc, char *concret, ...)
{
	va_list arg;

	va_start (arg, concret);
	return 'c';
}

// (comentaris)'esperat'
void
maquina_estats_comprovacio_caracter (char e, char *m_error, int lloc, char *concret, ...)
{
	char c;
	va_list arg;

	va_start (arg, concret);
		c = maquina_estats_llegir_linia_privada (m_error, lloc, concret, arg);
		maquina_estats_comprovacio_caracter_amb_2 (c, e, m_error, lloc, concret, arg);
	va_end (arg);
}

// (comentaris)'p'(comentaris)'s'[^:\\n]*:
void
maquina_estats_llegir_inici_final (char p, char s, char *m_error, int lloc)
{
	char *error = "\"(comentaris)%c(comentaris)%c[^:\\n]*:\" és el missatge esperat";

	maquina_estats_comprovacio_caracter (p, m_error, lloc, error, p, s);
}

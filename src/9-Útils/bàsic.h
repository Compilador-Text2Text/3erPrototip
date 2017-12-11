#ifndef UTILS_BASIC_H_
#define UTILS_BASIC_H_

#define MIN(X, Y) X < Y ? X : Y
#define MAX(X, Y) X > Y ? X : Y

#include <stdlib.h>

enum
cert_fals
{
	CF_fals = 0,
	CF_cert = 1,
};

void basic_error (char *, ...);
void basic_error_perror (void);

char* basic_depurar_cert_fals (enum cert_fals);

void* basic_malloc (size_t); // És un malloc, amb control d'errors.
void* basic_realloc (void *, size_t); // És un realloc, amb control d'errors.
void* basic_free (void *);

#endif // UTILS_BASIC_H_

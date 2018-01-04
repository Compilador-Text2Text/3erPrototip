#include <stdio.h>
#include <stdlib.h>

void
euclides_recursiu (int a, int b)
{
//printf ("a: %d, b: %d\n", a, b);
	if (a == 0) { printf ("%d\n", b); exit (EXIT_SUCCESS); }

	euclides_recursiu (b%a, a);
}

void
euclides (int a, int b)
{
	int aux;

	if (a > b)
	{
		aux = a;
		a = b;
		b = aux;
	}
	euclides_recursiu (a, b);
}

int main (int argc, char *argv[])
{
	int a, b;

	if (argc < 3)
	{
		printf ("Error, volem com a mínim 2 entrades\n");
		exit (EXIT_FAILURE);
	}

	a = atoi (argv[1]);
	b = atoi (argv[2]);

	euclides (a, b);
}

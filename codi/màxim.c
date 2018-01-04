// Per fer al meu llenguatge de programació un màxim.
#include <stdio.h>
#include <stdlib.h>

int
maxim (int a, int b)
{
	if (a > b)
		return a;
	return b;
}

int
main (int argc, char *argv[])
{
	int out;

	if (argc < 3)
	{
		printf ("Error, volem com a mínim 2 entrades\n");
		return 1;
	}

	out = maxim (atoi(argv[--argc]), atoi(argv[--argc]));
	while (--argc)
		out = maxim (out, atoi(argv[argc]));

	printf ("%d\n", out);
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int trobar_quan_se_fa_petit (int l, char *p)
{
	int i;
	char v, n; // vell i nou
	v = 0; // valor mínim

	for (i = l-1; i >= 0; i--)
	{
		n = p[i];
		if ( n < v )
			return i +1;
		v = n;
	}
	exit (1);
}

void canvi (int i, int l, char *p)
{
	char a = p[i];
	p[i] = p[l];
	p[l] = a;
}

void gira (int l, char *p)
{
	int i; // minim, increment

	i = -1;
	while ( ++i < --l )
		canvi (i, l, p);
}
int trobar_quan_se_fa_gran (int l, char *p, char v)
{
	int i;

	for (i = 0; i < l; i++)
		if (v < p[i])
			return i +1;
	exit (1);
}
int next (int l, char *p)
{
	int m, c;

	m = trobar_quan_se_fa_petit (l, p);
	gira (l-m, p+m);
	c = trobar_quan_se_fa_gran (l-m, p+m, p[m-1]);
	canvi (m-1, c+m-1, p);

	return m;
return 0;
}

int main (int argc, char *argv[])
{
	if (argc == 1) return 1;
	next (strlen (argv[1]), argv[1]);
	printf ("%s\n", argv[1]);
	return 0;
}

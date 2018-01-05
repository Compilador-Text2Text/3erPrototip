#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

/**
 * Aquest programa accepta _un_ paràmetre per consola
 * (en format de nombre enter, n) i escriu per sortida
 * estàndar la representació com a producte de nombres
 * primers del factorial n!, en notació de LaTeX.
 * 	Compilar amb: make factorial.
 */

/**
 * Implementació del Garbell d'Eratòstenes
 */
int8_t *make_primes(int max)
{
	int i, j;
	int8_t *primes = (int8_t *)malloc(sizeof(int8_t) * (max + 1));
	for (i = 2; i <= max; i++) primes[i] = 1;

	primes[0] = primes[1] = 0;
	for (i = 2; i < sqrt(max) + 1; i++) {
		if (primes[i]) {
			// Preguntar, si podem posar j = i*i;
			for (j = i*i; j <= max; j += i) {
				primes[j] = 0;
			}
		}
	}
	return primes;
}

/**
 * Valoració p-àdica del nombre n!
 * També conegut com fórmula de Legandre/ fórmula de Polignac
 */
int power(int n, int p)
{
	int exponent = n/p;
	int last = exponent;

	while (last / p > 0) {
		last /= p;
		exponent += last;
	}
	return exponent;
}

int main(int argc, char *argv[])
{
	int8_t *primes;
	int n;
	int max;
	int p;
	int powerof;

	if (argc != 2) {
		printf("Usage: %s number\n", argv[0]);
		return 1;
	}

	n = atoi(argv[1]);

	if (n == 0 || n == 1) {
		printf("$%d! = 1$\n", n);
		return 0;
	}

	primes = make_primes(n);

	printf("$%d! =", n);

	/**
	 * Calculem iterativament la
	 * valoració p-àdica de n!
	 * i posteriorment ho imprimim
	 * en format LaTeX.
	 * Ho fem per a tot nombre primer
	 * 2 <= p <= n
	 */
	powerof = power(n, 2);
	if (powerof) {
		printf(" 2^{%d}", powerof);
	}
	for (p = 3; p <= n; p++) {
		if (primes[p]) {
			powerof = power(n, p);
			if (powerof) {
				printf(" \\cdot %d^{%d}", p, powerof);
			}
		}
	}

	printf("$\n");

	free(primes);

	return 0;
}

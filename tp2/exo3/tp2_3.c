#include <stdio.h>
#include <stdlib.h>

/* Modifiez ces définitions à votre guise afin de tester toutes les
conditions; elles correspondent aux valeurs initiales de a, b, c, d et e : */
#define INIT_A	2
#define INIT_B	7
#define INIT_C	3
#define INIT_D	4
#define INIT_E	5

int a, b, c, d, e;

extern void func_s(void);

static void func_c(void) {
	a = b;
	if (c + 1600 > e + 2013) {
		a = c;
		if ((b <= c) || (d == e)) {
			a = e;
		}
	} else {
		a = a + b;
	}
}

int main(void) {
	a = INIT_A;
	b = INIT_B;
	c = INIT_C;
	d = INIT_D;
	e = INIT_E;

	printf("a = %d    b = %d    c = %d    d = %d    e = %d\n", a, b, c, d, e);
	printf("Le résultat devrait être le même les 3 fois :\n\n");
	func_c();
	printf("Version en langage C : %i\n", a);
	a = INIT_A;
	b = INIT_B;
	c = INIT_C;
	d = INIT_D;
	e = INIT_E;
	func_s();
	printf("Version en assembleur : %i\n", a);
	a = INIT_A;
	b = INIT_B;
	c = INIT_C;
	d = INIT_D;
	e = INIT_E;
	func_c();
	printf("Version en langage C : %i\n", a);

	return 0;
}

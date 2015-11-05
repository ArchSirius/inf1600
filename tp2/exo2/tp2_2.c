#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float a, b, c, d, e, f, g;

extern void func_s(void);

static void func_c(void) {
	a = (((b * c) / (f + c)) * ((g - d) / e)) + (e * (g - d));
}

int main(void) {
	srand48(time(0));
	b = drand48();
	c = drand48();
	d = drand48();
	e = drand48();
	f = drand48();
	g = drand48();

	printf("Le résultat devrait être le même les 3 fois :\n\n");
	func_c();
	printf("Version en langage C : %f\n", a);
	a = 123456789;
	func_s();
	printf("Version en assembleur : %f\n", a);
	func_c();
	printf("Version en langage C : %f\n", a);
	
	return 0;
}

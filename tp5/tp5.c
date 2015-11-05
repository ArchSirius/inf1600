#include <stdio.h>

unsigned int little_endian_to_big_endian(unsigned int le)
{
	unsigned int be;

	/*
	 * Remplacez le code suivant par de l'assembleur en ligne
	 * en utilisant le moins d'instructions possible
	 */
	//be = le >> 24 | (le & 0xff0000) >> 8 | (le & 0xff00) << 8 | (le & 0xff) << 24;

	asm volatile (
		"movl %1, %%esi \n\t"
		"movl %%esi, %0 \n\t"
		"shrl $24, %1 \n\t"
		"andl $0xff0000, %0 \n\t"
		"shrl $8, %0 \n\t"
		"orl %1, %0 \n\t"
		"movl %%esi, %1 \n\t"
		"andl $0xff00, %1 \n\t"
		"shll $8, %1 \n\t"
		"orl %1, %0 \n\t"
		"movl %%esi, %1 \n\t"
		"andl $0xff, %1 \n\t"
		"shll $24, %1 \n\t"
		"orl %1, %0" // instructions...
		: "=r" (be) // sorties (s'il y a lieu)
		: "g" (le) // entrées
		: "esi" // registres modifiés (s'il y a lieu)
	);

// Également, il existe une fonction byteswap déjà implémentée
/*
	asm volatile (
        "movl %1, %0 \n\t"
        "bswap %0" // instructions...
        : "=r"(be) // sorties (s'il y a lieu)
        : "g"(le) // entrées
        : // registres modifiés (s'il y a lieu)
    );
*/

	return be;
}

int main()
{
	unsigned int data = 0xddccbbaa;

	printf("Représentation little-endian:   %08x\n"
	       "Représentation big-endian:      %08x\n",
	       data,
	       little_endian_to_big_endian(data));

	return 0;
}

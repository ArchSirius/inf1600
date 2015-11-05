#include "tp4.hpp"

# Cercle* nouveauCercle(Coord centre, unsigned int rayon, unsigned int couleur)
.global _Z13nouveauCercle5Coordjj

_Z13nouveauCercle5Coordjj:
	push %ebp
	mov %esp, %ebp

	pushl $32					# sizeof(Cercle) = 32
	call _Znwj					# operator new, address in %eax

	push 20(%ebp)				# push couleur
	push 16(%ebp)				# push rayon
	push 12(%ebp)
	push 8(%ebp)				# push centre

	push %eax					# push address
	call _ZN6CercleC1E5Coordjj	# constructor
	pop %eax
	addl $20, %esp				# unstacking

	leave
	ret


# void faireDessin(Forme** formes, unsigned int n)
.global _Z11faireDessinPP5Formej

_Z11faireDessinPP5Formej:
	push %ebp
	mov %esp, %ebp

	push %esi

	pushl $12					#sizeof(Canevas)
	call _Znwj

	pushl $COULEUR_CANEVAS
	pushl $HAUTEUR_CANEVAS
	pushl $LARGEUR_CANEVAS

	push %eax					#adresse de Canevas
	call _ZN7CanevasC1Ejjj
	pop %eax
	addl $16, %esp				# enlever 4 de %esp

	xor %ecx, %ecx
	
	jmp test
for:
	mov 8(%ebp), %esi
	mov (%esi,%ecx,4), %edx


	push %ecx
	push %edx					# param forme[i]

	push %eax					# param this
	call _ZN7Canevas13dessinerFormeEP5Forme
	pop %eax

	pop %edx
	pop %ecx

	inc %ecx

test:
	cmp %ecx, 12(%ebp)
	ja for

	push %eax
	call _Z11ecrireFramePK7Canevas # ecrireFrame(canevas)
	pop %eax

	push %eax
	call _ZN7CanevasD1Ev # destructeur
	push %eax
	call _ZdlPv
	addl $8, %esp



	pop %esi
	leave
	ret



# void desallouerForme(Forme* forme)
.global _Z15desallouerFormeP5Forme

_Z15desallouerFormeP5Forme:
	push %ebp
	mov %esp, %ebp

	mov 8(%ebp), %eax	#forme
	push %eax
	call _ZN5FormeD1Ev
	push %eax
	call _ZdlPv
	movl $0, 8(%ebp)	# forme = 0
	addl $8, %esp

	leave
	ret


#void Canevas::dessinerForme(Forme *forme)
.global _ZN7Canevas13dessinerFormeEP5Forme

_ZN7Canevas13dessinerFormeEP5Forme:
	push %ebp
	mov %esp, %ebp

	movl 12(%ebp), %eax	#forme
	pushl 8(%ebp)		#this (canevas)

	push %eax # empiler les param this (forme)

	movl (%eax), %eax

	call *8(%eax) # deuxieme fonction de la table virtuelle

	addl $8, %esp

	leave
	ret


#void Canevas::assignerPixel(int x, int y, unsigned int couleur)
.global _ZN7Canevas13assignerPixelEiij
_ZN7Canevas13assignerPixelEiij:
	push %ebp
	mov %esp, %ebp
	push %esi

	cmpl $0, 12(%ebp)
	jl fin
	cmpl $0, 16(%ebp)
	jl fin
	cmpl $LARGEUR_CANEVAS, 12(%ebp)
	jae fin
	cmpl $HAUTEUR_CANEVAS, 16(%ebp)
	jae fin

	movl 20(%ebp), %esi		# couleur

	movl $LARGEUR_CANEVAS, %eax
	mull 16(%ebp)		# y
						# on sait qu'on ne déborde pas dans %edx
	addl 12(%ebp), %eax	# %edx = x + y * LARGEUR_CANEVAS

	movl 8(%ebp), %edx
	movl (%edx), %edx	#_canevas
	movl %esi, (%edx, %eax, 4) # _canevas[x + y * LARGEUR_CANEVAS] = couleur

	fin:

	pop %esi
	leave
	ret


#void Canevas::assignerPixel(Coord coord, unsigned int couleur)
.global _ZN7Canevas13assignerPixelE5Coordj
_ZN7Canevas13assignerPixelE5Coordj:
	push %ebp
	mov %esp, %ebp

	pushl 20(%ebp)	# couleur
	pushl 16(%ebp)
	pushl 12(%ebp)	# coord
	pushl 8(%ebp)	# this

	call _ZN7Canevas13assignerPixelEiij

	addl $16, %esp

	leave
	ret
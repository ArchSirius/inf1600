
.global dot

dot:
  push %ebp
  mov %esp,%ebp

/* Implementer ici votre fonction dot a virgule fixe */
	push %ecx
	push %esi
	push %ebx
	push %edi
	xor %ecx, %ecx		#i=0
	xor %edi, %edi		
	xor %ebx, %ebx

	jmp test

for:
	movl 8(%ebp), %edx  	# u dans edx
	movl 12(%ebp), %esi 	# v dans esi

	movl (%edx, %ecx, 4), %eax 
	movl (%esi, %ecx, 4), %edx

	imull %edx		# u[i]*v[i]
	
	addl %eax, %edi		# concaténation mis dans deux registres et ajouté au fur et mesure de la boucle
	adcl %edx, %ebx 
	
	inc %ecx		# i++

test:
	cmp %ecx, 16(%ebp) 	# flags <- n-i
	ja for
	
	
	movl %edi,%eax		# somme remise dans eax et edx pour faire le shift
	movl %ebx,%edx
	
	
	shll $12, %edx		# on sélectionne les 12 bits à gauche de edx
	shrl $20, %eax		# 20 bits à droite de eax
	or %edx, %eax		# concaténation dans eax
	
	
	pop %edi
	pop %ebx
	pop %esi
	pop %ecx


  leave
  ret

.global func_s

func_s:
	mov b, %ebx 	#  a=b
	mov %ebx, a
	mov c, %ecx 	# (c+1600)
	add $1600, %ecx
	mov e, %edx
	add $2013, %edx #(e+2013)
	cmp %ecx, %edx
	jae else 	#si (c+1600 <= e+2013) sauter au else
	mov c, %ecx	# a = c
	mov %ecx, a	
	cmp %ebx, %ecx	
	jae if2
	mov d, %edx
	mov e, %ecx
	cmp %edx, %ecx
	je if2
	jmp fin 
	
if2:
	mov e, %ecx
	mov %ecx,a 
	jmp fin

else:
	mov a, %eax
	add b, %eax
	mov %eax, a

fin:
	ret

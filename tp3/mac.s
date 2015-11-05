
.global mac

mac:
  push %ebp
  mov %esp,%ebp

  push %esi
  xor %ecx, %ecx		 # i = 0
  jmp test
for:
  mov 20(%ebp), %eax		      # %eax = c
  mov (%eax, %ecx, 4), %eax   # %eax = c[i]
  imull 16(%ebp)               # %edx#%eax = f * c[i]

  shll $12, %edx              # on sélectionne les 12 bits à gauche de edx
  shrl $20, %eax              # 20 bits à droite de eax
  orl %edx, %eax              # concaténation dans eax

  mov 12(%ebp), %edx          # %edx = b
  mov (%edx, %ecx, 4), %edx   # %edx = b[i]
 
  add %edx, %eax              # %eax = b[i] + f * c[i]
  
  mov 8(%ebp), %edx		        # %edx = a
  mov %eax, (%edx, %ecx, 4)	  # a[i] = b[i] + f * c[i]
  
  inc %ecx			 # i++
test:

  movl 24(%ebp), %esi		 # n
  cmp %ecx, %esi		 # if i<n	
  ja for

  pop %esi
  leave
  ret

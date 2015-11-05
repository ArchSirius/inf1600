
.global mul

mul:

  push %ebp                     # sauvegarder old %ebp
  mov %esp, %ebp                # %ebp = %esp
  
  sub $8, %esp                  # espace pour les variables locales

  push %esi                     # sauvegarder old %esi
  push %ebx                     # sauvegarder old %ebx

### %esp :
#        n = 28(%ebp)
#        q = 24(%ebp)
#        p = 20(%ebp)
#       *x = 16(%ebp)
#       *a = 12(%ebp)
#       *y = 8(%ebp)
# old %eip = 4(%ebp)
# old %ebp = 0(%ebp)
# sommeLSB = -4(%ebp)
# sommeMSB = -8(%ebp)   <- ** carry **
# old %esi = -12(%ebp)
# old %ebx = -16(%ebp)
#
### registres:
# %eax : *m, *b, *w, *s
# %edx : *x
# %ecx : i
# %esi : 4 * n
# %ebx : divers index ou comparateurs
# %edx#%eax : résultat de la multiplication sur 64 bits

  xor %ecx, %ecx                # i = 0

  mov 28(%ebp), %esi            # %esi = n
  # Multiplication x4 sans mul/imul
  add %esi, %esi                # %esi = n * 2
  add %esi, %esi                # %esi = n * 4

  jmp test_for0

for0:
  movl $0, -4(%ebp)             # sommeLSB = 0
  movl $0, -8(%ebp)             # sommeMSB = 0

  mov 12(%ebp), %eax            # %eax = a = m
  mov (%eax, %ecx, 4), %eax     # %eax = m[i]

  mov 16(%ebp), %edx            # %edx = x
  mov (%edx, %ecx, 4), %edx     # %edx = x[i]

  imul %edx                     # %edx#%eax = m[i] * x[i]
  add %eax, -4(%ebp)            # sommeLSB += %eax
  adc %edx, -8(%ebp)            # sommeMSB += %edx

if1:
  movl $1, %ebx                 # %ebx = 1
  cmp %ecx, %ebx                # if(i >= 1)
  ja if2                        # else

  mov 12(%ebp), %eax            # %eax = a
  add %esi, %eax                # %eax = a + n * 4 = b
  mov (%eax, %ecx, 4), %eax     # %eax = b[i]

  mov 16(%ebp), %edx            # %edx = x
  mov -4(%edx, %ecx, 4), %edx   # %edx = x[i - 1]

  imul %edx                     # %edx#%eax = b[i] * x[i - 1]
  add %eax, -4(%ebp)            # sommeLSB += %eax
  adc %edx, -8(%ebp)            # sommeMSB += %edx

if2:
  mov 28(%ebp), %ebx            # %ebx = n
  subl $1, %ebx                 # %ebx = n - 1
  cmp %ecx, %ebx                # if(i < n - 1)
  jbe if3                       # else

  mov 12(%ebp), %eax            # %eax = a
  add %esi, %eax                # %eax = a + n * 4 = b
  mov 4(%eax, %ecx, 4), %eax    # %eax = b[i + 1]

  mov 16(%ebp), %edx            # %edx = x
  mov 4(%edx, %ecx, 4), %edx    # %edx = x[i + 1]

  imul %edx                     # %edx#%eax = b[i + 1] * x[i + 1]
  add %eax, -4(%ebp)            # sommeLSB += %eax
  adc %edx, -8(%ebp)            # sommeMSB += %edx

if3:
  mov 20(%ebp), %ebx            # %ebx = p
  cmp %ecx, %ebx                # if(i >= p)
  ja if4                        # else

  mov 12(%ebp), %eax            # %eax = a
  add %esi, %eax                # %eax = a + n * 4
  add %esi, %eax                # %eax = a + 2 * n * 4 = w
  mov (%eax, %ecx, 4), %eax     # %eax = w[i]

  mov %ecx, %ebx                # %ebx = i
  sub 20(%ebp), %ebx            # %ebx = i - p
  mov 16(%ebp), %edx            # %edx = x
  mov (%edx, %ebx, 4), %edx     # %edx = x[i - p]

  imul %edx                     # %edx#%eax = w[i] * x[i - p]
  add %eax, -4(%ebp)            # sommeLSB += %eax
  adc %edx, -8(%ebp)            # sommeMSB += %edx

if4:
  mov 28(%ebp), %ebx            # %ebx = n
  sub 20(%ebp), %ebx            # %ebx = n - p
  cmp %ecx, %ebx                # if(i < n - p)
  jbe if5                       # else

  mov 12(%ebp), %eax            # %eax = a
  mov 28(%ebp), %ebx            # %ebx = n
  add 28(%ebp), %ebx            # %ebx = 2 * n
  add %ecx, %ebx                # %ebx = i + 2 * n
  add 20(%ebp), %ebx            # %ebx = i + p + 2 * n
  # Multiplication x4 sans mul/imul
  add %ebx, %ebx                # %ebx = (i + p + 2 * n) * 2
  add %ebx, %ebx                # %ebx = (i + p + 2 * n) * 4
  add %ebx, %eax                # %eax = a + 4 * (i + p + 2 * n)
  # Mémoire -> Registre, car pointeur
  # Le x4 est déjà calculé
  mov (%eax), %eax              # %eax = w[i + p]

  mov %ecx, %ebx                # %ebx = i
  add 20(%ebp), %ebx            # %ebx = i + p
  mov 16(%ebp), %edx            # %edx = x
  mov (%edx, %ebx, 4), %edx     # %edx = x[i + p]

  imul %edx                     # %edx#%eax = w[i + p] * x[i + p]
  add %eax, -4(%ebp)            # sommeLSB += %eax
  adc %edx, -8(%ebp)            # sommeMSB += %edx

if5:
  mov 24(%ebp), %ebx            # %ebx = q
  cmp %ecx, %ebx                # if (i >= q)
  ja if6                        # else

  mov 12(%ebp), %eax            # %eax = a
  add %esi, %eax                # %eax = a + n * 4
  add %esi, %eax                # %eax = a + 2 * n * 4
  add %esi, %eax                # %eax = a + 3 * n * 4 = s
  mov (%eax, %ecx, 4), %eax     # %eax = s[i]

  mov %ecx, %ebx                # %ebx = i
  sub 24(%ebp), %ebx            # %ebx = i - q
  mov 16(%ebp), %edx            # %edx = x
  mov (%edx, %ebx, 4), %edx     # %edx = x[i - q]

  imul %edx                     # %edx#%eax = s[i] * x[i - q]
  add %eax, -4(%ebp)            # sommeLSB += %eax
  adc %edx, -8(%ebp)            # sommeMSB += %edx

if6:
  mov 28(%ebp), %ebx            # %ebx = n
  sub 24(%ebp), %ebx            # %ebx = n - q
  cmp %ecx, %ebx                # if(i < n - q)
  jbe fin                       # else

  mov 12(%ebp), %eax            # %eax = a
  mov 28(%ebp), %ebx            # %ebx = n
  add 28(%ebp), %ebx            # %ebx = 2 * n
  add 28(%ebp), %ebx            # %ebx = 3 * n
  add %ecx, %ebx                # %ebx = i + 3 * n
  add 24(%ebp), %ebx            # %ebx = i + q + 3 * n
  # Multiplication x4 sans mul/imul
  add %ebx, %ebx                # %ebx = (i + q + 3 * 2) * 2
  add %ebx, %ebx                # %ebx = (i + q + 3 * n) * 4
  add %ebx, %eax                # %eax = a + 4 * (i + q + 3 * n)
  # Mémoire -> Registre, car pointeur
  # Le x4 est déjà calculé
  mov (%eax), %eax              # %eax = s[i + q]

  mov %ecx, %ebx                # %ebx = i
  add 24(%ebp), %ebx            # %ebx = i + q
  mov 16(%ebp), %edx            # %edx = x
  mov (%edx, %ebx, 4), %edx     # %edx = x[i + q]

  imul %edx                     # %edx#%eax = s[i + q] * x[i + q]
  add %eax, -4(%ebp)            # sommeLSB += %eax
  adc %edx, -8(%ebp)            # sommeMSB += %edx

fin:
  
  mov -4(%ebp), %eax            # %eax = sommeLSB
  mov -8(%ebp), %edx            # %edx = sommeMSB

  shl $12, %edx                 # on sélectionne les 12 bits à gauche de %edx
  shr $20, %eax                 # 20 bits à droite de %eax
  or %edx, %eax                 # concaténation dans %eax

  mov 8(%ebp), %edx             # %edx = y
  # Pas besoin de recopier en paramètre, car pointeur
  mov %eax, (%edx, %ecx, 4)     # y[i] = %eax

  inc %ecx                      # i++

test_for0:
 	cmp %ecx, 28(%ebp)            # i < n
 	ja for0                       # true

  pop %ebx                      # restaurer old %ebx
  pop %esi                      # restaurer old %esi
  leave                         # restaurer old %ebp
  ret                           # return

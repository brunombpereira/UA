#mapa de registos
#n_even = $t0
#n_odd = $t1
#p1 = $t2
#p2 = $t3
#a+N = $t4
#*p1 = $t5
#*p1%2 = $t6
#b + n_odd = $t7
#*p2 = $t8

	.data
arraya:	.space 140 #75*4
arrayb:	.space 140 #75*4
	.eqv N,35
	.eqv N_4,140 #N*4
	.eqv read_int,5
	.eqv print_int10,1
	.text
	.globl main

main:	li $t0,0 #n_even
	li $t1,0 #n_odd
	
	la $t2,arraya #p1 = $t2 = &a[0] = a
	
	addiu $t4,$t2,N_4 #a + N

for:	bge $t2,$t4,endf
	
	li $v0,5
	syscall #read_int()
	
	sw $v0,0($t2) #*p1=read_int() [*p no lado esquerdo e atribuir o valor ao registo que e apontado por *p}
	
	addiu $t2,$t2,4 #p1++
	j for

endf:	la $t2,arraya #p1 = a
	la $t3,arrayb #p2 = b

for1:	bge $t2,$t4,endf1
	
	lw $t5,0($t2) #*p1
	rem $t6,$t5,2 #*p1 % 2

if:	beq $t6,0,else
	
	sw $t5,0($t3)
	addiu $t3,$t3,4 #*p2++
	
	addiu $t1,$t1,1 #n_odd++
	

else:	addiu $t0,$t0,1 #n_even++

endif:	addiu $t2,$t2,4 #p1++
	j for1

endf1:	la $t3,arrayb #p2=&arrayb[0]=b
	sll $t1,$t1,2 #n_odd*4
	addu $t7,$t1,$t3 #b + n_odd
	
for2:	bge $t3,$t7,endf2
	
	lw $t8,0($t3) #*P
	
	move $a0,$t8
	li $v0,1
	syscall #print_int10(*p2)
	
	addiu $t3,$t3,4 #p2++
	j for2
	
endf2:	jr $ra
	
	
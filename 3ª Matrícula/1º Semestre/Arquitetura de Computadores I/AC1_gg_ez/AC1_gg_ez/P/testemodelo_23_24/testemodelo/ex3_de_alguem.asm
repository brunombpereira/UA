#mapa de registos
#$t0-n_even
#$t1-n_odd
#$t2-p1
#$t3-p2
#$t4-a+N
#$t5-b+n_odd

	.data
arraya:	.space 140
arrayb:	.space 140
	.eqv N,35
	.eqv N_4,140
	.eqv read_int,5
	.eqv print_int10,1
	.text
	.globl main
main:
	li $t0,0 #n_even=0
	li $t1,0 #n_odd=0
	
	la $t2,arraya #p1=a
	addiu $t4,$t2,N_4 # #a+N
for:
	bge $t2,$t4,endf

	li $v0,5
	syscall
	
	sw $v0, 0($t2) #*p1=read_int()
	addiu $t2,$t2,4 #p1++
	j for
endf:
	la $t2,arraya #p1=a
	la $t3,arrayb #p2=b
for2:
	bge $t2,$t4,endf2
	
	lw $t5,0($t2) #*p
	rem $t6,$t5,2  
if:
	beq $t6,0,else
	
	sw $t5,0($t3)
	addiu $t3,$t3,4 #*p2++
	
	addiu $t1,$t1,1 #n_odd++
	j endif
else:
	addiu $t0,$t0,1 #n_even++
endif:
	addiu $t2,$t2,4 #p1++
	j for2
endf2:
	la $t3,arrayb #p2=b
	sll $t1,$t1,2 #n_odd*4
	addu $t5,$t3,$t1 #b+n_odd
for3:
	
	bge $t3,$t5,endf3
	
	lw $t6,0($t3) #*p2
	
	move $a0,$t6
	li $v0,1
	syscall #print_int10(*p2)
	
	addiu $t3,$t3,4
	j for3
endf3:
	jr $ra
	

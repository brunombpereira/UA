# Mapa de registos
#n_even:$t0
#n_odd:$t1
#p1:$t2
#p2:$t3
#a+N || b+n_odd:$t4
#*p1:$t5
#*p1%2:$t6
	.data
arraya:	.space 140
arrayb:	.space 140	
	.eqv N,35
	.eqv N_4,140
	.eqv read_int,5
	.eqv print_int10,1
	.text
	.globl main
main:	li $t0,0		#n_even = 0
	li $t1,0		#n_odd = 0
	
	la $t2,arraya		#p1=a
	addiu $t4,$t2,N_4	#a+(N*4)
	
for1:	bge $t2,$t4,endf1	#p1<a+(N*4)

	li $v0,read_int		#read_int()
	syscall
	
	sw $v0,0($t2)		#*p1=read_int()
	addiu $t2,$t2,4		#p++
	j for1

endf1:	la $t2,arraya		#p1=a
	la $t3,arrayb		#p2=b
	
for2:	bge $t2,$t4,endf2	#p1<a+(N*4)

	lw $t5,0($t2)		#$t5=*p1
	rem $t6,$t5,2		#$t6=*p1%2

if:	beqz $t6,else	

	sw $t5,0($t3)		#*p2=*p1
	addiu $t3,$t3,4		#p2++	
	addiu $t1,$t1,1		#n_odd++
	j endif

else:	addiu $t0,$t0,1		#n_even++

endif:	addiu $t2,$t2,4		#p++

	j for2

endf2:	la $t3,arrayb		#p2=b
	sll $t1,$t1,2		#n_odd*4
	addu $t5,$t1,$t3	#b+n_odd
	
	
for3:	bge $t3,$t5,endf3	#p2<(b+(n_odd*4))

	lw $a0,0($t3)		#*p2
	li $v0,print_int10
	syscall
	
	addiu $t3,$t3,4		#p2++
	j for3

endf3:	jr $ra	

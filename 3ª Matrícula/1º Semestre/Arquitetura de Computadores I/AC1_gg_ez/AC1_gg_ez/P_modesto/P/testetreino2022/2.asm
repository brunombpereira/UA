# Mapa de registos
#i:$t0
#v:$t1
#&val[0]:$t2
#i*4:$t3
#&val[i]:$t4
#&val[i+SIZE/2]:$t5
	.data
val:	.word 8,4,15,-1987,327,-9,27,16
	.eqv SIZE,8
	.eqv SIZE_4,32
	.eqv SIZE_2,4
	.eqv SIZE_2_4,16
	.eqv print_string,4
	.eqv print_int10,1
	.eqv print_char,11
str:	.asciiz "Result is: "
	.text
	.globl main
main:	li $t0,0		#i=0
	
	la $t2,val		#$t2=&val[0]
	
do1:	sll $t3,$t0,2		#$t3=i*4

	addu $t4,$t2,$t3	#$t4=&val[i]
	lw $t1,0($t4)		#v=val[i]
	addiu $t5,$t4,SIZE_2_4	#&val[i+SIZE/2]
	lw $t6,0($t5)
	sw $t6,0($t4)		#val[i]=val[i+SIZE/2]
	sw $t1,0($t5)		#val[i+SIZE/2]=v
	addiu $t0,$t0,1		#i++
	
while:	bge $t0,SIZE_2,endw

	j do1

endw:	la $a0,str
	li $v0,print_string
	syscall
	
	li $t0,0		#i=0
	la $t2,val
	
do2:	sll $t3,$t0,2		#i*4

	addu $t4,$t2,$t3	#&val[i]
	
	lw $a0,0($t4)	
	li $v0,print_int10
	syscall
	
	addiu $t0,$t0,1
	
	li $a0,',' 
	li $v0,print_char
	syscall
	
while2:	blt $t0,SIZE,do2
	
	jr $ra
	
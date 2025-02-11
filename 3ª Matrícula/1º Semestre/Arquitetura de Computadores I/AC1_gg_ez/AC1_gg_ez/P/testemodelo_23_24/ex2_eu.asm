#mapa de registos
#i = $t0
#v = $t1
#&val[0] = $t2
#i*4 = $t3
#&val[i] = $t4
#val[i] = $t5
#i+SIZE/2 = $t6
#&val[i+SIZE/2] = $t7
#val[i+SIZE/2] = $t8

	.data
val:	.word 8,4,15,-1987,327,-9,27,16
str:	.asciiz "Result is:"
	.eqv SIZE,8
	.eqv SIZE_2,4
	.eqv SIZE_4,32
	.eqv SIZE_4_2,16
	.eqv print_string,4
	.eqv print_int10,1
	.eqv print_char,11
	.text
	.globl main

main:	li $t0,0 #i=0
	

do:	la $t2,val #&val[0]
	sll $t3,$t0,2 #i*4
	addu $t4,$t3,$t2 #&val[i]
	lw $t5,0($t4) #val[i]
	
	move $t1,$t5 #v=val[i]
		
	addi $t6,$t3,SIZE_4_2 #i+SIZE/2
	addu $t7,$t2,$t6 #&val[i+SIZE/2]
	lw $t8,0($t7) #val[i+SIZE/2]
	
	sw $t8,0($t4) #val[i]=val[i+SIZE/2]
	sw $t1,0($t7) #val[i+SIZE/2]=v
	
	addi $t0,$t0,1 #i++

while:	blt $t0,SIZE_2,do

	la $a0,str
	li $v0,4
	syscall #print_string(result is:)
	
	li $t0,0 #i=0

do1:	la $t2,val #&val[0]
	sll $t3,$t0,2 #i*4
	addu $t4,$t3,$t2 #&val[i]
	lw $t5,0($t4) #val[i]
	
	move $a0,$t5 
	li $v0,1
	syscall
	
	addiu $t0,$t0,1 #i++
	
	li $a0,','
	li $v0,11
	syscall
	
while1:	blt $t0,SIZE,do1

	jr $ra

	.data
str1:	.asciiz "Arquitetura de "
str2:	.space 50
str3:	.asciiz "\n"
str4:	.asciiz "Computadoores I "
	.eqv print_string,4
	.text
	.globl main

#strcpy() começa
strcpy:	li $t0,0 #i=0

do:	addu $t1,$a0,$t0 #&dst[i]
	addu $t2,$a1,$t0 #&src[i]
	
	lb $t3,0($t2) #src[i]
	sb $t3,0($t1) #dst[i]=src[i]

	addiu $t0,$t0,1 #i++

while:	bne $t3,'\0',do 
	
	move $v0,$a0
	jr $ra #strcpy() acaba

#strcat() funciton begin
strcat:	addiu $sp,$sp,-8
	sw $ra,0($sp)
	sw $s0,4($sp)
	
	move $t0,$a0
	move $s0,$a0

w1:	lb $t1,0($t0)
	beq $t1,'\0',endw1
	
	addiu $t0,$t0,1
	j w1

endw1:	move $a0,$t0
	jal strcpy
	
	move $v0,$s0
	
	lw $s0,4($sp)
	lw $ra,0($sp)
	addiu $sp,$sp,8
	
	jr $ra

#strcat() function end

#main function begin
main:	addiu $sp,$sp,-8
	sw $ra,0($sp)
	sw $s0,4($sp)
	
	la $s0,str2
	move $a0,$s0
	la $a1,str1
	jal strcpy
	
	move $a0,$s0
	li $v0,4
	syscall
	
	la $a0,str3
	li $v0,print_string
	syscall
	
	move $a0,$s0
	la $a1,str4
	jal strcat
	
	move $a0,$v0
	li $v0,print_string
	syscall
	
	li $v0,0 #return 0

	lw $s0,4($sp)
	lw $ra,0($sp)
	addiu $sp,$sp,8
	
	jr $ra
#main function end
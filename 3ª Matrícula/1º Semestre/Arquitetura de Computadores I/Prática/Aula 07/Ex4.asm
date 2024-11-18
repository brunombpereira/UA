	.data
	
str0:	.asciiz "Arquitetura de "
str1:	.asciiz "Computadores I"
str3:	.asciiz "\n"

str2:	.space 50

	.eqv print_string,4
	
	.text
	.globl main
	

strcpy:
	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	li $t0,0
do:
	addu $s0,$a0,$t0
	
	addu $s1,$a1,$t0
	lb $t1,0($s1)
	
	sb $t1,0($s0)
	
	addi $t0,$t0,1
	bne $t1,'\0',do

	move $v0,$s0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
	
	
strcat:
	addiu $sp,$sp,-8
	sw $ra,0($sp)
	sw $s0,4($sp)
	
	move $s0,$a0
while:
	lb $t0,0($s0)
	beq $t0,'\0',endw
	
	addiu $s0,$s0,1
	j while
endw:
	move $a0,$s0
	jal strcpy
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	addiu $sp,$sp,8
	
	jr $ra
	
	
main:
	addiu $sp,$sp,-12
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	
	la $s0,str2
	la $s1,str0
	
	move $a0,$s0
	move $a1,$s1
	jal strcpy
	
	la $a0,str2
	li $v0,print_string
	syscall
	
	la $a0,str3
	li $v0,print_string
	syscall
	
	la $a0,str2
	la $a1,str1
	jal strcat
	
	la $a0,str2
	li $v0,print_string
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	addiu $sp,$sp,12
	
	jr $ra
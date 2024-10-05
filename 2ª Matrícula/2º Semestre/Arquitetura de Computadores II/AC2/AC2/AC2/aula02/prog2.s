	.data
	.equ resetcoretimer,12
	.equ printint,6
	.equ putchar,3
	.equ readcoretimer,11
	.text
	.globl main

main:	addiu $sp,$sp,-16
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)

	li $s0,0
	li $s1,0
	li $s2,0
while:	
	li $a0,4000
	jal delay
	
	li $a0,'\r'
	li $v0,putchar
	syscall		

	addi $s0,$s0,1
	
	move $a0,$s0
	li $a1,0x0005000A
	li $v0,printint
	syscall
	addi $s1,$s1,1
	
	move $a0,$s1
	li $a1,0x0005000A
	li $v0,printint
	syscall

	addi $s2,$s2,1
	
	move $a0,$s2
	li $a1,0x0005000A
	li $v0,printint
	syscall
	
	j while
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	addiu $sp,$sp,16
	jr $ra	



delay:	mul $a0,$a0,20000
	li $v0, resetcoretimer
	syscall
whr:	li $v0,readcoretimer
	syscall
	blt $v0,$a0,whr
	
	li $v0,0
	jr $ra

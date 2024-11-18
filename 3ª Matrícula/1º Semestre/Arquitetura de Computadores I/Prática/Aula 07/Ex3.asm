	.data
	
str0:	.asciiz "I serodatupmoC ed arutetiuqrA"
str1:	.asciiz "String too long: "
str3:	.asciiz "\n"

str2:	.space 31
	
	.eqv STR_MAX_SIZE,30
	.eqv print_string,4
	.eqv print_int10,1
	
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
	
	
strlen:
	li $t0,0
while:
	lb $t1,0($a0)
	addiu $a0,$a0,1
	
	beq $t1,'\0',endw
	
	addi $t0,$t0,1
	j while
endw:
	move $v0,$t0
	jr $ra
	
	
exchange:
	lb $t0,0($a0)
	lb $t1,0($a1)
	
	sb $t1,0($a0)
	sb $t0,0($a1)
	
	jr $ra
	
	
strrev:
	addiu $sp,$sp,-16
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	
	move $s0,$a0
	move $s1,$a0
	move $s2,$a0
while0:
	lb $t0,0($s2)
	beq $t0,'\0',endw0
	
	addiu $s2,$s2,1
	j while0
endw0:
	addiu $s2,$s2,-1
while1:
	bge $s1,$s2,endw1
	
	move $a0,$s1
	move $a1,$s2
	jal exchange
	
	addiu $s1,$s1,1
	addiu $s2,$s2,-1
	j while1
endw1:
	move $v0,$s0
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	addiu $sp,$sp,16
		
	jr $ra


main:
	addiu $sp,$sp,12
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	
	la $s0,str0
	la $s1,str2
if:
	move $a0,$s0
	jal strlen
	
	bgt $v0,STR_MAX_SIZE,else
	
	move $a0,$s1
	move $a1,$s0
	jal strcpy
	
	la $a0,str2
	li $v0,print_string
	syscall
	
	la $a0,str3
	li $v0,print_string
	syscall
	
	la $a0,str2
	jal strrev
	
	move $a0,$v0
	li $v0,print_string
	syscall
	
	li $v0,0
	j endif
else:
	la $a0,str1
	li $v0,print_string
	syscall
	
	la $a0,str1
	jal strlen
	
	move $a0,$v0
	li $v0,print_int10
	syscall
	
	li $v0,-1
endif:
	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	addiu $sp,$sp,12
	
	jr $ra

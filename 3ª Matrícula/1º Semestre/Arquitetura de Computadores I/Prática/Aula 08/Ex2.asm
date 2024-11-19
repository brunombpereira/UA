# Mapa de Registos
# n:	 $a0 -> $s0
# b:	 $a1 -> $s1
# s:	 $a2 -> $s2
# p:	 $s3
# digit: $t0


	.data
	
str:	.space 33

	.eqv MAX_STR_SIZE,33
	.eqv read_int,5
	.eqv print_string,4
	.eqv print_char,11
	
	.text
	.globl main
	
	
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
	
	
toascii:
	li $t0,'0'
	addu $a0,$a0,$t0
if:
	ble $a0,'9',endif
	
	addiu $a0,$a0,7
endif:
	move $v0,$a0	
	jr $ra


itoa:
	addiu $sp,$sp,-20
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	sw $s3,16($sp)
	
	move $s0,$a0
	move $s1,$a1
	move $s2,$a2
	move $s3,$a2
do:
	remu $t0,$s0,$s1
	divu $s0,$s0,$s1
	
	move $a0,$t0
	jal toascii
	
	sb $v0,0($s3)
	addiu $s3,$s3,1
	
	bgt $s0,0,do
	
	li $t1,'\0'
	sb $t1,0($s3)
	
	move $a0,$s2
	jal strrev
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	lw $s3,16($sp)
	addiu $sp,$sp,20
	
	jr $ra
	
	
main:
	addiu $sp,$sp,-12
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	
	la $s1,str
do2:
	li $v0,read_int
	syscall
	
	move $s0,$v0
	
	move $a0,$s0
	li $a1,2
	move $a2,$s1
	jal itoa
	
	move $a0,$v0
	li $v0,print_string
	syscall
	
	li $a0,'\n'
	li $v0,print_char
	syscall
	
	move $a0,$s0
	li $a1,8
	move $a2,$s1
	jal itoa
	
	move $a0,$v0
	li $v0,print_string
	syscall
	
	li $a0,'\n'
	li $v0,print_char
	syscall
	
	move $a0,$s0
	li $a1,16
	move $a2,$s1
	jal itoa
	
	move $a0,$v0
	li $v0,print_string
	syscall
	
	li $a0,'\n'
	li $v0,print_char
	syscall
	
	bne $s0,0,do2

	li $v0,0

	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	addiu $sp,$sp,12
	
	jr $ra
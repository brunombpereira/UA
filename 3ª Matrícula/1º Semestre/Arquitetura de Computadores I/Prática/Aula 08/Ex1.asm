# Mapa de Registos
# res: 	 $v0
# s:	 $a0
# *s:	 $t0
# digit: $t1

	.data

str:	.asciiz "2020 e 2024 sao anos bissextos"

	.eqv print_int10,1
	
	.text
	.globl main
	
	
atoi:
	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	li $v0,0
while:
	lb $t0,0($a0)
	blt $t0,'0',endw
	bgt $t0,'9',endw
	
	li $t2,'0'
	subu $t1,$t0,$t2
	addiu $a0,$a0,1
	mulu $v0,$v0,10
	addu $v0,$v0,$t1
	
	j while
endw:
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
	
	
main:
	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	la $a0,str
	jal atoi
	
	move $a0,$v0
	li $v0,print_int10
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
# Mapa de Registos
# p: $t0
# *p: $t1
# lista + SIZE: $t2


	.data
	
str:	.asciiz "\nConteúdo do array:\n"
str2:	.asciiz "; "

	.eqv SIZE,10
	.eqv print_string,4
	.eqv print_int10,1
	
lista:	.word 8, -4, 3, 5, 124, -15, 87, 9, 27, 15

	.text
	.globl main
main:
	la $a0,str
	li $v0,print_string
	syscall

	li $t4,SIZE
	la $t0,lista
	sll $t2,$t4,2
	addu $t2,$t2,$t0
for:
	bge $t0,$t2,endf
	
	lw $a0,0($t0)
	li $v0,print_int10
	syscall
	
	la $a0,str2
	li $v0,print_string
	syscall
	
	addiu $t0,$t0,4
	
	j for
endf:
	jr $ra
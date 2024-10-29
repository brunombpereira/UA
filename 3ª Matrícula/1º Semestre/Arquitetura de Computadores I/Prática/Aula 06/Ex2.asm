# Mapa de Registos
# p: $t0
# pUltimo: $t1


	.data
	
str0:	.asciiz "Array"
str1:	.asciiz "de"
str2:	.asciiz "ponteiros"

	.eqv SIZE,3
	.eqv print_string,4
	.eqv print_char,11
	
array:	.word str0, str1, str2

	.text
	.globl main
main:
	la $t0,array
	
	li $t2,SIZE
	sll $t2,$t2,2
	addu $t1,$t0,$t2
for:
	bge $t0,$t1,endf
	
	lw $a0,0($t0)
	li $v0,print_string
	syscall
	
	li $a0,'\n'
	li $v0,print_char
	syscall
	
	addiu $t0,$t0,4
	j for
endf:
	jr $ra
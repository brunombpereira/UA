# Mapa de Registos
# i: $t0


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
	li $t0,0
for:
	bge $t0,SIZE,endf
	
	la $t1,array
	sll $t2,$t0,2
	addu $t2,$t2,$t1
	
	lw $a0,0($t2)
	li $v0,print_string
	syscall
	
	li $a0,'\n'
	li $v0,print_char
	syscall
	
	addi $t0,$t0,1
	j for
endf:
	jr $ra
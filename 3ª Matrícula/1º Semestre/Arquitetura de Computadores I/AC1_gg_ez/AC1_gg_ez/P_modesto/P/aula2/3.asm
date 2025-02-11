#	.data
#str1:	.asciiz "So para chatear"
#str2:	.asciiz "AC1 - P"
#	.eqv print_string,4
#	.text
#	.globl main
#main:	la $a0, str2
#	ori $v0,$0,print_string
#	syscall
#	jr $ra

	.data
str1:	.asciiz "Introduza 2 numeros "
str2:	.asciiz "A soma dos dois numeros e "
	.eqv print_string,4
	.eqv read_int,5
	.eqv print_int10,1
	.text
	.globl main
main:	la $a0, str1
	
	ori $v0,$0,print_string
	syscall
	
	li $v0, read_int
	syscall
	ori $t0,$v0,0
	
	li $v0,read_int
	syscall
	ori $t1,$v0,0
	
	la $a0, str2
	ori $v0,$0,print_string
	syscall
	
	add $a0, $t0,$t1
	
	li $v0, print_int10
	syscall
	
	jr $ra

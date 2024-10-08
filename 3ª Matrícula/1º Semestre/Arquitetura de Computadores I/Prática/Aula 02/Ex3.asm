	.data

str1:	.asciiz "--Introduza 2 números--\n"
str2:	.asciiz "1º Número: "
str3:	.asciiz "2º Número: "
str4:	.asciiz "A soma dos dois números é: "

	.eqv print_string,4
	.eqv read_int,5
	.eqv print_int10,1
	
	.text
	.globl main
main:
	la $a0,str1
	ori $v0,$0,print_string
	syscall
	
	la $a0,str2
	ori $v0,$0,print_string
	syscall
	
	ori $v0,$0,read_int
	syscall
	
	or $t0,$0,$v0
	
	la $a0,str3
	ori $v0,$0,print_string
	syscall
	
	ori $v0,$0,read_int
	syscall
	
	or $t1,$0,$v0
	
	add $t2,$t0,$t1
	
	la $a0,str4
	ori $v0,$0,print_string
	syscall
	
	or $a0,$0,$t2
	ori $v0,$0,print_int10	
	syscall
	
	jr $ra
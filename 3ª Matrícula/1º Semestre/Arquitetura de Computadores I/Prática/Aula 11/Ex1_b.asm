	.data
	
str0:	.asciiz "\nN. Mec: "
str1:	.asciiz "\nNome: "
str2:	.asciiz "\nNota: "
str3:	.asciiz "\nPrimeiro nome: "
str4:	.asciiz "\nÚltimo nome: "
	
	.eqv print_string,4
	.eqv print_intu10,36
	.eqv print_char,11
	.eqv print_float,2
	.eqv read_int,5
	.eqv read_string,8
	.eqv read_float,6
	
	.align 2
stg:	.space 44
	
	.text
	.globl main
main:
	la $t0,stg
	
	la $a0,str0
	li $v0,print_string
	syscall
	
	li $v0,read_int
	syscall
	sw $v0,0($t0)
	
	la $a0,str3
	li $v0,print_string
	syscall
	
	addiu $a0,$t0,4
	li $a1,17
	li $v0,read_string
	syscall
	
	la $a0,str4
	li $v0,print_string
	syscall
	
	addiu $a0,$t0,22
	li $a1,14
	li $v0,read_string
	syscall
	
	la $a0,str2
	li $v0,print_string
	syscall
	
	li $v0,read_float
	syscall
	s.s $f0,40($t0)
	
	la $a0,str0
	li $v0,print_string
	syscall
	
	lw $a0,0($t0)
	li $v0,print_intu10
	syscall
	
	la $a0,str1
	li $v0,print_string
	syscall
	
	addiu $a0,$t0,22
	li $v0,print_string
	syscall
	
	li $a0,','
	li $v0,print_char
	syscall
	
	addiu $a0,$t0,4
	li $v0,print_string
	syscall
	
	la $a0,str2
	li $v0,print_string
	syscall
	
	l.s $f12,40($t0)
	li $v0,print_float
	syscall
	
	li $v0,0
	
	jr $ra
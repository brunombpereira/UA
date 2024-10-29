# Mapa de Registos
# i: $t0
# j: $t1


	.data

str0:	.asciiz "Array"
str1:	.asciiz "de"
str2:	.asciiz "ponteiros"
str3:	.asciiz "\nString #"
str4:	.asciiz ": "

	.eqv SIZE,3
	.eqv print_string,4
	.eqv print_int10,1
	.eqv print_char,11
	
array:	.word str0, str1, str2

	.text
	.globl main
main:
	li $t0,0
for:
	bge $t0,SIZE,endf
	
	la $a0,str3
	li $v0,print_string
	syscall
	
	move $a0,$t0
	li $v0,print_int10
	syscall
	
	la $a0,str4
	li $v0,print_string
	syscall
	
	li $t1,0
while:
	la $t2,array
	sll $t3,$t0,2
	addu $t2,$t2,$t3
	lw $t4,0($t2)
	addu $t4,$t4,$t1
	lb $a0,0($t4)
	
	beq $a0,'\0',endw
	
	li $v0,print_char
	syscall
	
	li $a0,'-'
	li $v0,print_char
	syscall
	
	addi $t1,$t1,1
	j while
endw:
	addi $t0,$t0,1
	j for
endf:
	jr $ra
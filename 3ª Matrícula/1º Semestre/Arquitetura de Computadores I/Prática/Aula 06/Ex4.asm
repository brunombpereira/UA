# Mapa de Registos
# i: 	  $t0
# argc:   $a0, $t1
# argv[]: $a1, $t2


	.data
	
str0:	.asciiz "Nr. de parametros: "
str1:	.asciiz "\nP"
str2:	.asciiz ": "

	.eqv print_string,4
	.eqv print_int10,1
	
	.text
	.globl main
main:
	li $t0,0
	move $t1,$a0
	
	la $a0,str0
	li $v0,print_string
	syscall
	
	move $a0,$t1
	li $v0,print_int10
	syscall
for:
	bge $t0,$t1,endf
	
	la $a0,str1
	li $v0,print_string
	syscall
	
	move $a0,$t0
	li $v0,print_int10
	syscall
	
	la $a0,str2
	li $v0,print_string
	syscall
	
	move $t2,$a1
	sll $t3,$t0,2
	addu $t2,$t2,$t3
	
	lw $a0,0($t2)
	li $v0,print_string
	syscall
	
	addi $t0,$t0,1
	j for
endf:
	li $v0,0
	jr $ra
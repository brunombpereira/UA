#		MAPA DE REGISTOS:
#	$t0-----------------------------argc			 
#	$t1-----------------------------&argv[0]
#	$t2-----------------------------i
#	$t3-----------------------------i*4
#	$t4-----------------------------&argv[i]

	ACABAR

	.data
	.eqv print_string,4
	.eqv print_int10,1
str1:	.asciiz "Nr. de parametros: "
str2:	.asciiz "\nP"
str3:	.asciiz ": "
	.text
	.globl main

main:	li $t2,0 #i=0
	move $t0,$a0
	move $t1,$a1

	la $a0,str1
	li $v0,print_string
	syscall
	
	move $a0,$t0
	li $v0,print_int10
	syscall

for:
	
	
	j for

endf:
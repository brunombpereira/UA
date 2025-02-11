		.data
stg:		.align 2# se nao for a primeira cena no segmento de dados
idn_a:		.word 72343
first_name:	.asciiz "Napoleao"
		.space 9
last_name:	.asciiz "Bonaparte"
		.space 5
		.align 2
grade_a:	.float 5.1
		.eqv print_intu10,36

main:	li $v0,print_int10

	la $a0,stg
	lw $a0,0($t0)
	syscall
	#.
	#.
	#.
	li $v0,4
	la $a0,last_name#em vez de last name stg+22 por ser
	# uma estrutura sozinha num endereço fixo
	syscall
	#agr o float
	li $v0,2
	la $t0,grade_a#em vez de grade_a tb da stg+40
	l.s $f12,0($t0)
	syscall
##########alinea b##########
	li $v0,5
	syscall
	
	la $t0,stg
	sw $v0,0($t0)
	
	la $a0,stg+4
	li $a1,17
	li $v0,8
	syscall		
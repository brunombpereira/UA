 # Mapa de Registos
 # i: 	       $t0
 # lista:      $t1
 # lista + i : $t2
 
 
 	.data
 	
str:	.asciiz "\nIntroduza um número: " 	
 	
 	.eqv SIZE,5
 	.eqv print_string,4
 	.eqv read_int,5
 	
 	.align 2
lista:	.space 20

	.text
	.globl main
main:	
	li $t0,0
for:
	bge $t0,SIZE,endf
	
	la $a0,str
	li $v0,print_string
	syscall
	
	li $v0,read_int
	syscall
	
	la $t1,lista
	sll $t2,$t0,2
	addu $t2,$t2,$t1
	
	sw $v0,0($t2)
	
	addi $t0,$t0,1
	
	j for
endf:
	jr $ra
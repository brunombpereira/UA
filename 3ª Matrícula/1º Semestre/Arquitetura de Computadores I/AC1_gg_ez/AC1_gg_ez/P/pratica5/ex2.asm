# Mapa de registos
# p: $t0
# *p: $t1 (Registo tempor�rio para guardar o valor armazenado em mem�ria)
# lista+Size: $t2
	.data
str1:	.asciiz "; "
str2:	.asciiz "\nConteudo do array:\n"
lista:	.word 8,-4, 3, 5, 124, -15, 87, 9, 27, 15 
			# a diretiva ".word" alinha num endere�o
 			# m�ltiplo de 4
	.eqv print_int10,1
	.eqv print_string,4
	.eqv SIZE,10
	.text
	.globl main

main:	la $a0,str2
	li $v0,4
	syscall # print_string(...)
	
	la $t0,lista # p = lista
	li $t2,SIZE #
	sll $t2,$t2,2 # SIZE * 4 pq cada elemento e um inteiro
	addu $t2,$t0,$t2 # $t2 = lista + SIZE;

for:	bgeu $t0,$t2,endf # while(p < lista+SIZE) {
	lw $t1,0($t0) # $t1 = *p;
	
	move $a0,$t1
	li $v0, print_int10
	syscall # print_int10( *p );
	
	la $a0,str1 
	li $v0,4
	syscall	# print_string(...);
	
	addiu $t0,$t0,4 # p++;
	
	j for
endf:	jr $ra # termina o programa 

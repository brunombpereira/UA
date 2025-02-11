# i: $t0
# $t1: lista ou &lista[0]->endereço do elemento inicil do array
# $t2: lista + i ou &lista[i]
	.data
	.eqv SIZE,5
str:	.asciiz "\nIntroduza um numero: "
	.align 2 #smp q um inteiro n é o primeiro num espaço de memoria pq tem um char ou assim antes, temos que usar o align 2
lista:	.space 20 # SIZE * 4 (inteiros)
	.eqv read_int,5
	.eqv print_string,4
	.text
	.globl main

main:	li $t0,0 # i = 0;
	
	la $t1,lista # $t1 = lista (ou &lista[0])

for:	bge $t0,SIZE,endf # while(i < SIZE) {
	
	la $a0,str
	li $v0,4
	syscall # print_string(...);
	
	li $v0,read_int
	syscall # $v0 = read_int();
	
	
	sll $t2,$t0,2 #
	addu $t2,$t1,$t2# $t2 = &lista[i]
	sw $v0,0($t2) # lista[i] = read_int();
	addi $t0,$t0,1# i++
	j for # }

endf:	li $v0,0 #nao e obrigatorio
	jr $ra # termina programa

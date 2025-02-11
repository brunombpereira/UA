	.data
lista:	.word 8,-4,3,5,124,-15,87,9,27,15
str1:	.asciiz "\nConteudo do array:\n"
str2:	.asciiz "; "
	.eqv SIZE,10
	.eqv SIZE_4,40
	.eqv print_string,4
	.eqv print_int10,1
	.text
	.globl main
main:	la $a0,str1
	li $v0,print_string
	syscall
	
	la $t0,lista		#p
	addiu $t1,$t0,SIZE_4	#lista+SIZE
	
for:	bge $t0,$t1,endf

	lw $a0,0($t0)
	li $v0,print_int10
	syscall	
	
	la $a0,str2
	li $v0,print_string
	syscall
			
	addiu $t0,$t0,4
	j for

endf:	jr $ra
	
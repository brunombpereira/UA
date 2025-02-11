	.data
lista:	.space 20
str:	.asciiz "\nIntroduza um numero: "
	.eqv SIZE,5
	.eqv SIZE_4,20
	.eqv print_string,4
	.eqv read_int,5
	.text
	.globl main
main:	la $t0,lista		#&lista[0]

	li $t1,0		#i=0

for:	bge $t1,SIZE,endf
	
	la $a0,str
	li $v0,print_string
	syscall
	
	li $v0,read_int
	syscall
	
	sll $t2,$t1,2		#i*4
	addu $t3,$t0,$t2	#&lista[i]
	sw $v0,0($t3)		#lista[i]=read_int()
	
	addiu $t1,$t1,1		#i++
	j for
	
endf:	jr $ra
	
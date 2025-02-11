#	MAPA DE REGISTOS:
#	p 	 - 	$t0
#	p*       - 	$t1
#	contador -      $t2
       
	.data
	.eqv SIZE,20
	.eqv print_string,4
	.eqv read_string,8
str:	.space 21
str1:	.asciiz "Introduza uma string: "
	.text
	.globl main
main:	la $a0,str1
	
	li $v0,print_string
	syscall
	
	la $a0,str
	li $a1,SIZE
	li $v0,read_string
	syscall
	
	li $t2,0
	la $t0,str
while:	lb $t1,0($t0)

	beq $t1,'\0',endw	
	addi $t1,$t1,0x41
	sub $t1,$t1,0x61
	sb $t1,0($t0)
	addiu $t0,$t0,1
	addiu $t2,$t2,1
	j while
endw:	
	sub $t0,$t0,$t2
	move $a0,$t0
	li $v0,print_string
	syscall
	
	jr $ra
	
#	MAPA DE REGISTOS:
#	num 	- 	$t0
#	i 	- 	$t1
#	&str[0] - 	$t2
#	&str[i]	-	$t3
#	str[i]	-	$t4	
	.data
	.eqv read_string,8
	.eqv print_int10,1
str:	.space 21	#SIZE+1
	.eqv SIZE,20
	.text
	.globl main
main:	la $a0,str
	
	li $a1,SIZE
	li $v0,read_string
	syscall
	
	li $t0,0
	li $t1,0
	
while:	la $t2,str
	addu $t3,$t2,$t1

	lb $t4,0($t3)
	beq $t4,'\0',endw
if:	blt $t4,'0',endif

	bgt $t4,'9',endif
	addi $t0,$t0,1
endif:	addi $t1,$t1,1

	j while
endw:	move $a0,$t0
	li $v0,print_int10
	syscall
	jr $ra
	
	
	
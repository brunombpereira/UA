#	MAPA DE REGISTOS:
#	p 	- 	$t0
#	pultimo - 	$t1
#	*p	-	$t2
#	soma	-	$t3
	.data
	.eqv SIZE,4
array:	.word 7692,23,5,234
	.eqv print_int10,1
	.text
	.globl main
main:	li $t3,0

	la $t0,array
	addiu $t1,$t0,12
while:	bgt $t0,$t1,endw

	lw $t2,0($t0)
	add $t3,$t3,$t2
	addiu $t0,$t0,4
	j while
endw:	move $a0,$t3

	li $v0,print_int10
	syscall
	
	jr $ra
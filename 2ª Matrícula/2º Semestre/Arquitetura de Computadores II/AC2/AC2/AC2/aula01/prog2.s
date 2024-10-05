	.data
	.equ getchar,2
	.equ putchar,3
	.text
	.globl main
main:	
do:	li $v0,getchar
	syscall
	move $t0,$v0
	
	move $a0,$t0
	li $v0,putchar
	syscall
	
while:	bne $t0,'\n',do
	li $v0,0
	jr $ra

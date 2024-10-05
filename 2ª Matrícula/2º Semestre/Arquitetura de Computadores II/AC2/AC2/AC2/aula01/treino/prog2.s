	.data
	.text
	.globl main

main:	
do: 	li $v0,2		# getChar()
	syscall
	move $t0,$v0
	move $a0,$t0
	li $v0,3		#putCHar(c)
	syscall
while:	bne $t0,'\n',do

	li $v0,0
	jr $ra

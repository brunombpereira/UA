	.data
	.text
	.globl main
main:
do:	li $v0,1
	syscall
	move $t0,$v0
if:	beq $t0,$0,else
	move $a0,$t0
	li $v0,3
	syscall
	j while
else:	li $a0,'.'
	li $v0,3
	syscall
while:	bne $t0,'\n',do

	li $v0,0
	jr $ra

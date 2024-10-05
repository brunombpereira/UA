	.data
	.equ inkey, 1
	.equ putchar,3
	.text
	.globl main
main:	
do: 	li $v0, inkey
	syscall
	move $t0,$v0

if:	beq $t0,0,else
	move $a0, $t0
	li $v0,putchar
	syscall
else:	li $a0,'.'
	li $v0, putchar
	syscall
while:	bne $t0,'\n',do
	li $v0,0
	jr $ra

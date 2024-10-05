	.data
	.text
	.globl main
main:	li $t0,0		# state = 0
	li $t1,0		# cnt = 0
do:	li $a0,'\r'
	li $v0,3
	syscall
	move $a0,$t1
	sll $t9,3,16
	li $a1,10
	or $a1,$a1,$t9
	li $v0,6
	syscall
	li $a0,'\t'
	li $v0,3
	syscall
	move $a0,$t1
	sll $t9,6,16
	li $a1,2
	or $a1,$a1,$t9
	li $v0,6
	syscall
	
	li $v0,12
	syscall
while:	li $v0,11
	syscall
	move $t9,$v0
	bge $t9,

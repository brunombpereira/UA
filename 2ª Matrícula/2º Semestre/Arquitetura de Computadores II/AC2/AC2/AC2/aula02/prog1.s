	.data
	.equ putChar,3
	.equ printInt,6
	.equ read_core_timer,11
	.equ reset_core_timer,12
	.text
	.globl main
main:	li $t0,0		# counter = 0
	
while1:
	li $v0,reset_core_timer
	syscall


whr:	li $v0,read_core_timer
	syscall
	blt $v0,200000,whr

	li $t3,4
	sll $t3,$t3,16		# 4<<16
	li $t4,10
	or $a1,$t4,$t3
	addi $t0,$t0,1
	move $a0,$t0
	li $v0,printInt
	syscall

	li $a0,'\r'
	li $v0,putChar
	syscall

	j while1
endw1:	li $v0,0
	jr $ra

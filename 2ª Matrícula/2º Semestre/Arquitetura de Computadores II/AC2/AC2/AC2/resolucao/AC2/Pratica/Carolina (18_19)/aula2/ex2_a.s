	.equ READ_CORE_TIMER,11
	.equ RESET_CORE_TIMER,12
	.equ PUT_CHAR,3
	.equ PRINT_INT, 6
	.data
	.text
	.globl main

main:	li $t0, 0
while1:	li $a0, 1000
	jal delay
	li $a0,' '
	li $v0,PUT_CHAR
	syscall			# putChar(' ');
	addi $t0,$t0,1
	move $a0,$t0
	li $a1,10
	li $v0,PRINT_INT
	syscall			# printInt(++counter, 10);
	j while1
	jr $ra

delay:	ble $a0, $0, end
	li $v0,RESET_CORE_TIMER		# resetCoreTimer();
	syscall
while:	
	li $v0,READ_CORE_TIMER		# readCoreTimer();
	syscall
	blt $v0, 20000, while

	sub $a0, $a0,1 			#ms--
	j delay
end:	jr $ra

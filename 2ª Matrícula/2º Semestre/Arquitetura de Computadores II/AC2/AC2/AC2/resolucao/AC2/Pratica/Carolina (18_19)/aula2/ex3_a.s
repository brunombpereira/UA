.equ READ_CORE_TIMER,11
	.equ RESET_CORE_TIMER,12
	.equ PUT_CHAR,3
	.equ PRINT_INT, 6
	.data
	.text
	.globl main
main:	li $t0, 0
while: 	li $v0,READ_CORE_TIMER	# while (1) {
	syscall
	blt $v0,10000000,while	# while(readCoreTimer() < 20000);
	li $v0,RESET_CORE_TIMER	# resetCoreTimer();
	syscall
	li $a0,' '
	li $v0,PUT_CHAR
	syscall			# putChar(' ');
	addi $t0,$t0,1

	lui $t1, 0xBF88
	lw $t2,0x6050($t1)
	Andi $t2, $t2, 0x000F

	move $a0,$t2
	li $a1,0x00040002
	li $v0,PRINT_INT
	syscall			# printInt(++counter, 10);
	j while
	jr $ra
	
		


.equ READ_CORE_TIMER,11
	.equ RESET_CORE_TIMER,12
	.equ PUT_CHAR,3
	.equ PRINT_INT, 6
	.data
	.text
	.globl main
main:
	subu $sp,$sp, 8
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	lui $t1, 0xBF88
	lw $t2,0x6050($t1)
	Andi $a0, $t2, 0x000F
	move $s0, $a0
	li $a1,0x00040002
	li $v0,PRINT_INT
	syscall			
	addi $s0, $s0, 1

	li $t4, 1000
	div $s0, $t4,$s0

	move $a0, $s0
	jal delay

	j main

	lw $ra, 0($sp)
	lw $s0, 4($sp)
	subu $sp,$sp, -8
		
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

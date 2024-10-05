
	.equ SFR_BASE_HI, 0xBF88
	.equ READ_CORE_TIMER,11
	.equ RESET_CORE_TIMER,12
    .equ TRISB, 0x6040
	.equ PORTB, 0x6050
	.equ LATB, 0x6060
	.equ TRISE, 0x6100           
	.equ PORTE, 0x6110            
	.equ LATE,  0x6120            

	.data
	.text
	.globl main
main:
	subu $sp,$sp,8
	sw $ra,0($sp)
	sw $s0,4($sp)
	#$s0=v
	li $s0, 0
	lui $t1, SFR_BASE_HI

	#configurar o porto REO como saida

	lw $t2, TRISE($t1)	#read
	andi $t2, $t2, 0xFFFE 		#modificar
	sw $t2, TRISE($t1)	#write

while1:
	lw $t3, LATE($t1)		#read
	andi $t3, $t3,0xFFFE	#modify
	or  $s0, $t3, $s0					
	sw $s0, LATE($t1)		#write
	
	li $a0, 500
	jal delay
	xori $s0, $s0, 1

	j while1

	lw $ra,0($sp)
	lw $s0,4($sp)
	subu $sp,$sp,-8

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
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
	
	lui $t1, SFR_BASE_HI

	#configurar os portos RE[3..0] como saida

	lw $t2, TRISE($t1)	#read
	ori $t2,$t2,0x000F	#modificar
	sw $t2, TRISE($t1)	#write

	#configurar os portos RS[3..0] como entrada
	lw $t2, TRISE($t1)	#read
	andi $t2,$t2, 0xFFF0 		#modificar
	sw $t2, TRISE($t1)	#write

while1: #$s0=v
		li $s0, 16
contador: beq $s0,0,while1
		lw $t0,LATE($t1)
		andi $t0, $t0, 0xFFF0
		or $t0, $s0, $t0
		sw $t0,LATE($t1)

		
		li $a0,250
		jal delay

		sub $s0, $s0, 1	#contar decrescente

		j contador

		
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
	
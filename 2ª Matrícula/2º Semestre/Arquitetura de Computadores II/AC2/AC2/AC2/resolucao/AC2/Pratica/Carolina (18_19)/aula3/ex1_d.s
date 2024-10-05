	.equ SFR_BASE_HI, 0xBF88
	.equ READ_CORE_TIMER,11
	.equ RESET_CORE_TIMER,12
    .equ TRISB, 0x6040
	.equ PORTB, 0x6050
	.equ LATB, 0x6060
	.equ TRISE, 0x6100           
	.equ PORTE, 0x6110            
	.equ LATE,  0x6120            
	.equ PRINT_INT,6
	.equ PUT_CHAR,3
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

	#configurar os portos RB[3..0] como entrada
	lw $t2, TRISE($t1)	#read
	andi $t2,$t2, 0xFFF0 		#modificar
	sw $t2, TRISE($t1)	#write

while1: #$s0=v
		li $s0, 0x0000
contador: 
		lw $t0,LATE($t1)
		andi $t0, $t0, 0xFFF0
		or $t0, $s0, $t0
		

		sw $t0,LATE($t1)
		move $t2, $t0
		move $a0,$t0 
		li $a1,2
		li $v0, PRINT_INT
		syscall
		jal espaco

		andi $t0, $t0, 8	#fica 8 se o RB3=1,
		move $a0,$t0 
		li $a1,2
		li $v0, PRINT_INT
		syscall
		jal espaco



		beq $t0, 0x0000, RB3_0		#RB3 esta=0 e RB0 vai ficar 1
		beq $t0, 8, RB3_1		#RB3 esta=1 e RB0 vai ficar 0
RB3_1:	sll $s0,$t2, 1
		
		j salto


RB3_0:	sll $t2,$t2, 1
		ori $s0, $t2, 1		#concatenar e meter o ultimo bit a 1
		move $a0,$s0 
		li $a1,2
		li $v0, PRINT_INT
		syscall
		jal espaco
		
salto:	li $a0,750
		jal delay

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
	
espaco:
	li $a0,'\n'
	li $v0,PUT_CHAR
	syscall	
	jr $ra
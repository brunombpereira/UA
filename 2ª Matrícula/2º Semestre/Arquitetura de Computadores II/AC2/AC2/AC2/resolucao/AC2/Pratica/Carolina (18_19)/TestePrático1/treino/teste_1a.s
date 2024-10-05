	
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
	.global main
main:	lui $t1, SFR_BASE_HI
	#configure Switch3_0 inputs
	lw $t2, TRISB($t1)
	ori $t2,$t2,0x000F
	sw $t2, TRISB($t1)
	
	#configure LED	outputs
	lw $t2, TRISE($t1)
	andi $t2,$t2,0xFFF0
	sw $t2, TRISE($t1)

ciclo:

	lw $t2, PORTB($t1)		#ler o sw
	andi $t2,$t2,0x000F		#so queremos os 4 ultimos
	
	lw $t3, LATE($t1)		#mandar para os leds
	andi $t3, $t3, 0xFFF0
	or $t3, $t3, $t2
	sw $t3, LATE($t1)
	j ciclo
	
	jr $ra

	
	

.equ SFR_BASE_HI, 0xBF88
	.equ TRISE, 0x6100            # TRISE address is 0xBF886100
	.equ PORTE, 0x6110            # PORTE address is 0xBF886110
	.equ LATE,  0x6120            # LATE  address is 0xBF886120
        .equ TRISB, 0x6040
	.equ PORTB, 0x6050
	.equ LATB, 0x6060
	.equ PRINT_INT,6
	.equ PRINT_STR,8
	.data

	.text
	.globl main

main:	lui $t1,SFR_BASE_HI   #REO como saída
	lw $t2,TRISE($t1)
	andi $t2,$t2,0xFFF0
	sw $t2,TRISE($t1)
	
	lw $t2,TRISB($t1)    #RB0 como entrada
	ori $t2,$t2,0x000F
	sw $t2,TRISB($t1)
	
while:	lw $t0,PORTB($t1)
	andi $t0, $t0, 0x000F
	xori $t0, $t0, 0x0009
	lw $t2,LATE($t1)
	andi $t2, $t2,0xFFF0
	or $t2, $t2,$t0
	sw $t2,LATE($t1)

	j while

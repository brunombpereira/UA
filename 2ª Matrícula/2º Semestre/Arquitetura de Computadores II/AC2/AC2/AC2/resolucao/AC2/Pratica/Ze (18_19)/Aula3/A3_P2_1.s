	.data

		.equ SFR_BASE_HI, 0xBF88 # 16 MSbits of SFR area

		.equ TRISE, 	  0x6100 # TRISE address is 0xBF886100
		.equ PORTE, 	  0x6110 # PORTE address is 0xBF886110
		.equ LATE, 		  0x6120 # LATE address is 0xBF886120

		.equ TRISB,		  0x6040 # TRISB lower address
		.equ PORTB,		  0x6050 # PORTB lower address
		.equ LATB,		  0x6060 # LATB lower address

	.text
	.globl main

main:	lui  $t1, SFR_BASE_HI	# upper address thingy
		
		lw 	 $t2, TRISE($t1)
		lw   $t3, TRISB($t1)

		andi $t2, $t2, 0xFFFE
		ori  $t3, $t3, 0x1

		sw   $t2, TRISE($t1)	# Store I/O options RE
		sw   $t3, TRISB($t1)	# Store I/O options RB



ICycle:	lw   $t2, PORTB($t1)	# Guarda RB
		lw   $t3, LATE($t1)		# Guarda RE
    	

		andi $t3, $t3, 0xFFFE	
		andi $t2, $t2, 0x0001
		xori $t2, $t2, 0x0001	# inverts bit if xor 1 
		or	 $t3, $t3, $t2


		sw	 $t3, LATE($t1)		# Outputa E

		j ICycle

		jr $ra



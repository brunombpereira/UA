.data
	
	.equ SFR_BASE_HI, 0xBF88 # 16 MSbits of SFR area

	.equ TRISE,	  0x6100 # TRISE address is 0xBF886100
	.equ PORTE,	  0x6110 # PORTE address is 0xBF886110
	.equ LATE,	  0x6120 # LATE address is 0xBF886120

	.equ TRISB,		  0x6040 # TRISB lower address
	.equ PORTB,		  0x6050 # PORTB lower address
	.equ LATB,		  0x6060 # LATB lower address


.text
.globl main


main:	lui  $t0, SFR_BASE_HI
		
		lw   $t1, TRISE($t0)
		andi $t1, $t1, 0xFFF0
		sw	 $t1, TRISE($t0)

		lw   $t1, TRISB($t0)
		ori  $t1, $t1, 0x8
		sw   $t1, TRISB($t0)


		# ver estado de RB3
		lw   $t5, PORTB($t0)
		andi $t5, $t5, 0x8


		beq	 $t5, 0, Rdcres

Rcres:	li   $t2, 0x0000		# Reset counter
		j w2

Rdcres:	li   $t2, 0x000F		# Reset counter
		
w2:		lw	 $t3, LATE($t0)		# Read

		andi $t3, $t3, 0xFFF0	# Modify
		andi $t2, $t2, 0x000F
		or	 $t4, $t2, $t3

		sw	 $t4, LATE($t0)		# Write



		# ver estado de RB3
		lw   $t5, PORTB($t0)
		andi $t5, $t5, 0x8



		# Parte a decrescer
		beq  $t5, 0x8, cresc		

		addi $t2, $t2, -1		# counter -= 1

		li   $a0, 500			# delay 2Hz
		jal delay

		blt  $t2, 0, Rdcres		# if == max -> reset

		j w2					# continue counting if != max



		# Parte a crescer
cresc:	addi $t2, $t2, 1		# counter += 1

		li   $a0, 500			# delay 2Hz
		jal delay

		bgt  $t2, 0x000F, Rcres # if == max -> reset
		j w2					# continue counting if != max





		j w2					# continue counting if != max

		jr $ra


# delay()
delay:	li $v0, 12	# resetCoreTimer();
		syscall

wdelay:	li $v0, 11	# readCoreTimer();
		syscall

		blt $v0, 20000, wdelay	# while(readCoreTimer() < 20000);

		addi $a0, $a0, -1		# ms --		condição do for loop

		bgt $a0, 0, delay		# ms > 0	condição do for loop


		jr $ra


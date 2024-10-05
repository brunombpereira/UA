.data
	
	.equ SFR_BASE_HI, 0xBF88 # 16 MSbits of SFR area

	.equ TRISE,	      0x6100 # TRISE address is 0xBF886100
	.equ PORTE,	  	  0x6110 # PORTE address is 0xBF886110
	.equ LATE,	 	  0x6120 # LATE address is 0xBF886120

.text
.globl main


main:	lui  $t0, SFR_BASE_HI
		
		lw   $t1, TRISE($t0)
		andi $t1, $t1, 0xFFF0
		sw	 $t1, TRISE($t0)


		# Reset johnson counter
		lw 	 $t1, LATE($t0)
		andi $t1, $t1, 0xFFF0
		sw	 $t1, LATE($t0)


		
loop:	lw	 $t1, LATE($t0)		# estado atual -> isolar bit RB3
		andi $t1, $t1, 0x0008
		srl  $t1, $t1, 3

		xori $t1, $t1, 1		# inverter bit

		lw	 $t2, LATE($t0)		# ir buscar estado atual
		sll  $t2, $t2, 1

		or   $t2, $t2, $t1		# juntar estado atual + bit invertido

		li   $a0, 667			# aproximadamente 1.5 Hz
		jal  delay

		sw   $t2, LATE($t0)		# guardar

		j loop


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


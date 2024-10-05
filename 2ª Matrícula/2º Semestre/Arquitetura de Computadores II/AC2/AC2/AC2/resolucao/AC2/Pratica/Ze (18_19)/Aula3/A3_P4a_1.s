.data
	
	.equ SFR_BASE_HI, 0xBF88 # 16 MSbits of SFR area

	.equ TRISE,	  0x6100 # TRISE address is 0xBF886100
	.equ PORTE,	  0x6110 # PORTE address is 0xBF886110
	.equ LATE,	  0x6120 # LATE address is 0xBF886120


.text
.globl main


main:	li 	 $t0, 0				# int v = 0;
		
		lui	 $t1, SFR_BASE_HI	

		lw 	 $t2, TRISE($t1)	# TRISE0 = 0;
		andi $t2, $t2, 0xFFFE
		sw	 $t2, TRISE($t1)



while:	lw 	 $t2, LATE($t1)		# LATE0 = v;
		andi $t2, $t2, 0xFFFE
		andi $t3, $t0, 0x0001
		or	 $t2, $t2, $t3
		sw	 $t3, LATE($t1)

		
		li 	 $a0, 500			# delay(500);
		jal delay


		xori $t0, $t0, 0x0001


		j while

		jr $ra



delay:	li $v0, 12	# resetCoreTimer();
		syscall

wdelay:	li $v0, 11	# readCoreTimer();
		syscall

		blt $v0, 20000, wdelay	# while(readCoreTimer() < 20000);

		addi $a0, $a0, -1		# ms --		condição do for loop

		bgt $a0, 0, delay		# ms > 0	condição do for loop


		jr $ra



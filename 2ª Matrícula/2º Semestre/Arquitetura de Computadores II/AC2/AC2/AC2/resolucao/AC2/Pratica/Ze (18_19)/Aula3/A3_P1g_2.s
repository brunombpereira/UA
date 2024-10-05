.data
	
	.equ SFR_BASE_HI, 0xBF88 # 16 MSbits of SFR area

	.equ TRISE,	      0x6100 # TRISE address is 0xBF886100
	.equ PORTE,	  	  0x6110 # PORTE address is 0xBF886110
	.equ LATE,	 	  0x6120 # LATE address is 0xBF886120


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
		ori  $t1, $t1, 0x2
		sw   $t1, TRISB($t0)





		lw   $t3, PORTB($t0)
		andi $t3, $t3, 0x2

		beq	 $t3, 0, rr

rl:		li   $t1, 1
		j loop

rr:		li 	 $t1, 8



loop:	lw   $t2, LATE($t0)
		andi $t2, $t2, 0xFFF0

		or   $t2, $t2, $t1
		sw   $t2, LATE($t0)



		li  $a0, 333
		jal delay



		lw   $t3, PORTB($t0)
		andi $t3, $t3, 2


		beq	 $t3, 0, rloop


lloop:	beq  $t1, 8, rl

		sll  $t1, $t1, 1
		j loop


rloop:	beq  $t1, 1, rr

		srl  $t1, $t1, 1
		j loop





# delay()
delay:	li $v0, 12	# resetCoreTimer();
		syscall

wdelay:	li $v0, 11	# readCoreTimer();
		syscall

		blt $v0, 20000, wdelay	# while(readCoreTimer() < 20000);

		addi $a0, $a0, -1		# ms --		condição do for loop

		bgt $a0, 0, delay		# ms > 0	condição do for loop


		jr $ra




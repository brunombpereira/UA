 .data
 .text
 .globl main

main:	ori $t0,$0,0x0614
	nor $t1,$t0,$t0	#nega�ao
	
	jr $ra	#fim do prog

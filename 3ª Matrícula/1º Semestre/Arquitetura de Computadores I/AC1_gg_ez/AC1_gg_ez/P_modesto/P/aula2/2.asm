	.data	
	.text
	.globl main

main:	li $t0,valor		#substituir valor
	
	sll $t2,$t0,nbits	#substituir nbits
	srl $t3,$t0,nbits	#substituir nbits
	sra $t4,$t0,nbits	#substituir nbits
	
	srl $t1,$t0,1		#bin gray
	xor $t1,$t1,$t0		#bin gray
	
	
	jr $ra

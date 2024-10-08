	.data
	
	.text
	.globl main
main:
	li $t0,0x862A5C1B
	
	sll $t2,$t0,4
	srl $t3,$t0,4
	sra $t4,$t0,4
	
	xor $t1,$t0,$t3
	xor $t1,$t1,$t3
	srl $t5,$t1,2
	xor $t1,$t1,$t5
	srl $t6,$t1,1
	xor $t7,$t1,$t6
	
	jr $ra
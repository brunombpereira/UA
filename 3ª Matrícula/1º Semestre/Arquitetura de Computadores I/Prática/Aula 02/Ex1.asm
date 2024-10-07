	.data
	
	.text
	.globl main
main:
	ori $t0,$0,0x5C1B
	ori $t1,$0,0xA3E4
	and $t2,$t0,$t1
	or $t3,$t0,$t1
	nor $t4,$t0,$t1
	xor $t5,$t0,$t1
	nor $t6,$t0,$t0
	nor $t7,$t1,$t1
	
	jr $ra
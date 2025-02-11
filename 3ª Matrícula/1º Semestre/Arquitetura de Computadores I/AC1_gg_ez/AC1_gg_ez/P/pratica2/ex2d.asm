 .data
 .text
 .globl main
 
main:	ori $t0,$0,5 #$t0=bin
	srl $t2,$t0,1 #$t2 = temporaria = (bin>>1)
	xor $t1,$t0,$t2	#$t1 = gray = bin ^ (bin >> 1);
	
	jr $ra	#fim dom prog
	
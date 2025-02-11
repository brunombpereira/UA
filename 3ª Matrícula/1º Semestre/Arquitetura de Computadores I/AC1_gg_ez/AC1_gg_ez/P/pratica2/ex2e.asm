 .data
 .text
 .globl main
 
# $t0 - gray
# $t1 - num
# $t2 - bin 
# $t3 - temporaria 

main:	ori $t1,$0,15 #num=gray
	
	srl $t3,$t1,4 #$t3 = (num >> 4)
	xor $t1,$t3,$t1 #$t1 = num = num ^ (num >> 4)
	
	srl $t3,$t1,2 #$t3 = (num >> 2)
	xor $t1,$t3,$t1 #$t1 = num = num ^ (num >> 2)
	
	srl $t3,$t1,1 #$t3 = (num >> 1)
	xor $t1,$t3,$t1 #$t1 = num = num ^ (num >> 1)
	
	ori $t2,$t1,0 #bin = num
	
	jr $ra #fim do programa

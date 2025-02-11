	.data
	.text
	.globl main
main:	ori $t0,$0,x		#substituir x pelo valor
	
	ori $t1,$0,y		#susbtituir y pelo valor
	and $t2,$t0,$t1
	or  $t3,$t0,$t1
	nor $t4,$t0,$t1
	xor $t5,$t0,$t1
	
				#xori $t1,$t0,0xFFFFFFFF tinha usado esta mas nao esta totalmente correto 
				#pq n posso usar assim so 0xFFFF oq faz com que n seja correto 
	nor $t1,$t0,$0		#alinea c negaçao
	jr $ra

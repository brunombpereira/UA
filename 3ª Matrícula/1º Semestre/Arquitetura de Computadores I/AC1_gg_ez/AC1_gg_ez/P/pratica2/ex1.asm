 
 #podeoms usar .eqv para cada valor de val_1 e val_2 e dps ir mudando
 .data
 .text
 .globl main
 
main:	ori $t0,$0,0x1234
	ori $t1,$0,0x000F
	and $t2,$t0,$t1	#$t2 = $t0 & $t1 (and bit a bit)
	or  $t3,$t0,$t1	#$t3 = $t0 | $t1 (or bit a bit)
	nor $t4,$t0,$t1 #$t4 = ~($t0 | $t1)
	xor $t5,$t0,$t1	#$t5 = $t0 ^ $t1
	jr $ra	#fim do prog

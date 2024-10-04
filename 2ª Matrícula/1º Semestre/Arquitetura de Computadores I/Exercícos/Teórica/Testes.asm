.data
	.align 4
L1:	.asciiz "AC1-2010"
	.align 4
L2:	.word 0x2901, 0x10
L3:	.space 3
L4:	.asciiz ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>><"
.text
.globl main
main: 	ori $t0,$0,5  # $t0 = x (substituir val_x pelo
 			# valor de x pretendido)
 	ori $t2,$0,8 # $t2 = 8
 	add $t1,$t0,$t0 # $t1 = $t0 + $t0 = x + x = 2 * x
 	add $t1,$t1,$t2 # $t1 = $t1 + $t2 = y = 2 * x + 8
 	jr $ra # fim do programa 

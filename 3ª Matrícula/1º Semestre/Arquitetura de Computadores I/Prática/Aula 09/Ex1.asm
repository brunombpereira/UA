	.data
	
k1:	.float 2.59375
k2:	.float 0.0

	.eqv read_int,5
	.eqv print_float,2
	
	.text
	.globl main
main:
do:
	li $v0,read_int
	syscall
	
	mtc1 $v0,$f0
	cvt.s.w $f0,$f0
	
	la $t0,k1
	l.s $f2,0($t0)
	
	mul.s $f12,$f0,$f2
	li $v0,print_float
	syscall
	
	la $t1,k2
	l.s $f4,0($t1)
	c.eq.s $f12,$f4
	bc1f do
	
	li $v0,0
	jr $ra
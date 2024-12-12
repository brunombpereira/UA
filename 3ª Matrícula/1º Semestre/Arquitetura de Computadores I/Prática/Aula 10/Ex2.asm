	.data
	
aux:	.double 1.0
zero:	.double 0.0
multi:	.double 0.5

	.text
	.globl main
	
sqrt:
	la $t0,aux
	l.d $f2,0($t0)
	l.d $f0,0($t0)
	li $t0,0
	la $t1,zero
	l.d $f4,0($t1)
	la $t2,multi
	l.d $f6,0($t2)
if:
	c.le.d $f12,$f4
	bc1t else
do:
	mov.d $f2,$f0
	
	div.d $f0,$f12,$f0
	add.d $f0,$f0,$f0
	mul.d $f0,$f0,$f6
	
	c.eq.d $f2,$f0
	bc1f
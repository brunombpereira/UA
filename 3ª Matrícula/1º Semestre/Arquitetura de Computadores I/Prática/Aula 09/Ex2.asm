	.data
	
k1:	.double 5.0
k2:	.double 9.0
k3:	.double 32.0
k4:	.double 0.0
k5:	.double 100.0

	.eqv read_double,7
	.eqv print_double,3
	
	.text
	.globl main

f2c:
	la $t3,k3
	l.d $f2,0($t3)
	sub.d $f0,$f12,$f2
	
	la $t3,k2
	l.d $f2,0($t3)
	mul.d $f0,$f0,$f2
	
	la $t3,k1
	l.d $f2,0($t3)
	div.d $f0,$f0,$f2
	
	jr $ra
	
main:
	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	la $t0,k4
	la $t1,k4
	la $t2,k5
	l.d $f4,0($t0)
	l.d $f6,0($t1)
	l.d $f8,0($t2)
while:
	c.le.d $f6,$f8
	bc1f endw
	
	li $v0,read_double
	syscall
	
	mov.d $f12,$f0
	jal f2c
	mov.d $f6,$f0
	
	mov.d $f12,$f6
	li $v0,print_double
	syscall
	
	j while
endw:
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
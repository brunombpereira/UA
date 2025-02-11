	.data
f1:	.float 2.59375
f2:	.float 0.0
	.eqv read_int,5
	.eqv print_float,2
	.text
	.globl main
#tem um erro qlq tenho que ver

main:	la $t0,f1
	la $t1,f2
	l.s $f4,0($t0) #guardar o float 2.59...
	l.s $f6,0($t1) #guardar o float 0.0

do:	li $v0,5
	syscall #read_int()
	
	move $t0,$v0 
	mtc1 $t0,$f6 #passar para o coprocessador (FPU) para fazer o calc com floats
	cvt.s.w $f6,$f6 #converter inteiro em float
	
	mul.s $f12,$f6,$f4 #guardar o res no $f12 p/ entrar na syscall
	li $v0,print_float
	syscall #print_float(res)
	
	c.eq.s $f12,$f6 #while
	bc1f do
	
	li $v0,0 #return 0
	
	jr $ra
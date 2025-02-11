	.data
d1:	.double 1.0
d2:	.double 0.0
d3:	.double 0.5
	.eqv print_double,3
	.eqv read_double,7
	.text
	.globl main

###nao esta 100% bem PQP

sqrt:	la $t0,d1
	l.d $f0,0($t0) #xn=1.0 no endereço de retorno
	li $t1,0 #i=0
	


if:	c.le.d $f12,$f2
	bc1t else
	
	la $t2,d2
	l.d $f2,0($t2) #$f2=0.0
	
do:	mov.d $f4,$f0 #aux=xn
	
	la $t3,d3
	l.d $f6,0($t3) 	#$f6=0.5
	
	div.d $f8,$f12,$f0 #val/xn
	add.d $f10,$f4,$f8 #xn+val/xn
	mul.d $f0,$f6,$f10 #0.5*(xn+val/xn)
	
	c.eq.d $f4,$f0 
	bc1t endw #(aux != xn)
	addi $t1,$t1,1 #++i
	blt $t0,25,do

endw:	j endif 

else:	la $t4,d2
	l.d $f0,0($t4) #xn=0.0

endif: jr $ra

main:	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	li $v0,read_double
	syscall
	
	mov.d $f12,$f0
	jal sqrt
	
	mov.d $f12,$f0
	li $v0,print_double
	syscall
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	jr $ra

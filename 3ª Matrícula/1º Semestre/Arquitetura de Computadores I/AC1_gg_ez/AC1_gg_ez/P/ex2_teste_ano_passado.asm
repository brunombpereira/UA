#mapa de registos
#val-$f12
#array-$a0
#fx-$t0
#k-$t1
#k*8-$t4
#&array[k]-$t5
#array[k]-$f2
#sum-$f0--->$v0 ----> retorno
#aux-$f6
	.data
zero:	.double 0.0
valor:	.double 0.035
	.text
	.globl calc

calc:	li $t0,1 #fx=1
	li $t1,0 #k=0

	la $t2,zero
	l.s $f0,0($t2) #sum=0.0

do:	addiu $t3,$t1,1 #k+1
	mul $t0,$t0,$t3 #fx = fx * (k+1)
	
	sll $t4,$t2,3 #k*8
	addu $t5,$t4,$a0 #&array[k]
	l.d $f2,0($t5) #array[k]
	
	mtc1 $t0,$f4
	cvt.d.w $f4,$f4 #converter inteiro em double
	
	div.d $f6,$f2,$f4 #aux  = array[k] / (double) fx
	
	add.d $f0,$f0,$f6 #sum = sum + aux
	
	addi $t1,$t1,1 #k++
	addu $t5,$a0,$t1 #array[k++]
	s.d $f0,0($t5) #array[k++]=sum
	
	la $t6,valor
	l.d $f8,0($t6) #0.035

while:	c.le.d $f6,$f8
	bc1f do
	
	cvt.w.d $f0,$f0
	mfc1 $v0,$f0 #converter para inteiro
	
	jr $ra
	
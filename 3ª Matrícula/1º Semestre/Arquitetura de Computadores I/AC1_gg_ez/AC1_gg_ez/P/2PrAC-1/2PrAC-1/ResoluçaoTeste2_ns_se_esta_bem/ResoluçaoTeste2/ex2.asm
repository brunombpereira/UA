#mapa de registos
#val-$f12
#array-$a0
#fx-$t0
#k-$t1
#sum-$f2
#aux-$f6
	.data
zero:	.double 0.0
valor:	.double 0.035
	.text
	.globl calc
calc:
	li $t0,1 #fx=1
	li $t1,0 #k=0
	
	la $t2,zero
	l.d $f0,0($t2) #double sum=0.0
do:
	addi $t3,$t1,1 #k+1
	mul $t0,$t0,$t3 #fx=fx*(k+1)
	
	mtc1 $t0,$f2
	cvt.d.w $f2,$f2 #(double)fx
	
	sll $t4,$t1,3 #k*8
	addu $t5,$a0,$t4 #&array[k]
	l.d $f4,0($t5) #array[k]
	
	div.d $f6,$f4,$f2 #aux=array[k]/(double)fx
	
	add.d $f0,$f0,$f6 #sum=sum+aux
	
	s.d $f0,0($t5) #array[k++]=sum
	addi $t1,$t1,1 #k++
	
	la $t6,valor
	l.d $f8,0($t6) #0.035
while:
	c.le.d $f6,$f8
	bc1f do  #aux>0.035
	
	cvt.w.d $f0,$f0
	mfc1 $t7,$f0 # (int) sum
	
	move $v0,$t7 #return (int) sum
	
	jr $ra
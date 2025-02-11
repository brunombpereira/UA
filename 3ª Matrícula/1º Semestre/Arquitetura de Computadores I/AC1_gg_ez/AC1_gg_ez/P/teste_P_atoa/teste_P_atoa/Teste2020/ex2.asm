#mapa de registos
#array-$a0
#thd-$f12
#val-$f14
#n-$a1
#sum-$f0
#aux-$f4
#i- $t1
	.data
zero:	.double 0.0
	.text
	.globl proc
proc:
	la $t0,zero    
	l.d $f0,0($t0) #double sum=0.0
	
	li $t1,0 #i=0
for:
	bge $t1,$a1,endf
	
	sll $t2,$t1,3 #i*8
	addu $t3,$a0,$t2 #&array[i]
	
	l.d $f2,0($t3) #array[i]
	
	add.d $f4,$f2,$f14 #aux=array[i]+val
if:
	c.le.d $f4,$f12
	bc1t else
	
	mov.d $f2,$f12 #array[i]=thd
	add.d $f0,$f0,$f12 #sum+=thd
	j endif
else:
	mov.d $f2,$f4 #array[i]=aux
	add.d $f0,$f0,$f4 #sum+=aux
endif:
	addi $t1,$t1,1 #i++
	j for
endf:
	mtc1 $a1,$f6
	cvt.d.w $f6,$f6 #(double)n
	
	div.d $f0,$f0,$f6 #return sum/(double)n
	jr $ra
	
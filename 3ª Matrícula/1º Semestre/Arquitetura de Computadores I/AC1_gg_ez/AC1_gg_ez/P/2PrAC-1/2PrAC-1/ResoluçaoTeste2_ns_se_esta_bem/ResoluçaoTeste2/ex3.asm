#tabela		Align	Size	Offset
#char id	1	1	0
#double av	8	8	1->8
#int ns		4	4	16
#char smp[18]	1	18	20
#int sum	4	4	38->40
#t_sample	8	44->48

#mapa de registos
#ts-$a0
#nval-$a1
#sum-$f0
#n- n usei
#k-$t3
#acc-$t1
#pu-$t2
	.data
zero:	.double 0.0
ts:	.space 48
	.eqv id,0
	.eqv av,8
	.eqv ns,16
	.eqv smp,20
	.eqv sum,40
	.text
	.globl main
main:
	la $t0,zero
	l.d $f0,0($t0) #double sum=0.0
	
	li $t1,0 #acc=0
	
	addi $t2,$a0,$a1 #ts *pu=ts+nval
for:
	bge $a0,$t2,endf
	
	li $t3,0 #k=0
	lw $t4,ns($a0)#ts->ns
for1:
	bge $t3,$t4,endf1
	
	addu $t5,$a0,$t3 #struct k
	lb $t6,smp($t5) #ts->smp[k]
	
	add $t1,$t1,$t6 #+=ts->smp[k]
	
	addi $t3,$t3,1 #k++
	j for1
endf1:	
	sw $t1,sum($a0) #Ts->sum=acc
	
	mtc1 $t1,$f2
	cvt.d.w $f2,$f2 #(double)acc
	
	mtc1 $t4,$f4
	cvt.d.w $f4,$f4#(double)ts->ns
	
	div.d $f6,$f2,$f4 #(double)acc/(double)ts->ns
	
	s.d $f6,av($a0) #ts->av=(double)acc/(double)ts->ns
	
	l.d $f8,av($a0) #ts->av
	
	add.d $f0,$f0,$f8 #sum+=ts->av
	addi $a0,$a0,48
	j for
endf:
	cvt.s.d $f0,$f0 #return (float)sum
	
	jr $ra
		

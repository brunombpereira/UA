#tabela		Align	Size	OffSet
#char smp[10]	1	10	0
#double av	8	8	11->16
#int ns		4	4	24
#char id	1	1	28
#int sum	4	4	32
#t_cell		8	36->40

#mapa de registos
#t_cell-$t0
#smp-
#av-
#ns-
#id-
#sum-
#res-$f0
#aux-
#i-$t2
	.data
zero:	.double 0.0
valor:	.double 3.597
tcell:	.space 40
	.eqv smp,0
	.eqv av,16
	.eqv ns,24
	.eqv id,28
	.eqv sum,32
	.text
	.globl prcells
prcells:
	
	la $t1,zero
	l.d $f0,0($t1) #res=0.0
	
	li $t2,0 #i=0
for:
	bge $t2,$a1,endf
	
	lw $t5,ns($a0)#tc[i]->ns
	
	mtc1 $t5,$f2
	cvt.d.w $f2,$f2 #(double)tc[i]->ns
	
	la $t6,valor
	l.d $f4,0($t6)#3.597
	
	div.d $f6,$f2,$f4 #aux=(double)tc[i]->ns/3.597
	add.d $f0,$f0,$f6 #sum+=aux
	
	s.d $f4,av($a0) #tc[i]->av=aux
	
	cvt.w.d $f0,$f0
	mfc1 $t8,$f0
	
	sw $t8,sum($a0)	#tc[i]->sum=(int)res
	
	addi $t2,$t2,1 #i++
	j for
endf:
	move $v0,$t8
	jr $ra
	
	
	
	


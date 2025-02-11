#tabela		Align	Size	Offset
#char id	1	1	0		
#double av	8	8	8	
#int ns		4	4	16	
#char smp[18]	1	18	20
#int sum	4	4	40
#t_sample	8	44->48

	
#mapa de registos
#ts: $a0
#nval: $a1
#sum: $f0
#n: nao usei .l.
#k: $t4
#acc: $t1
#pu: $t2

	.data
zero:	.double 0.0
sample: .space 48
	.text
	.globl process

process:
	li $t1,0 #acc=0
	la $t6,zero
	l.d $f0,0($t6) #sum=0.0
	
	
# Typed struct
# {                   align       SIZE      Offset
#  int acc             4	   4	     0
#  unsigned char nm    1	   1 	     4
#   double grade       8	   8	     5 -> 8
#   char quest[14]     1	   14 	     16
#  int cq              4           4         30->32
#  }t_kvd              8	   40 #tem que ser multiplo de 8

#Mapa Registos
#nv: $a0
#pt $a1
#i: $t0
#j: $t1
#sum: $f2
#return: $f0

	.data
d1:	.double 0.0
	.text
	.globl func4

func4:	la $t2,d1
	l.d $f2,0($t2) #double sum = 0.0
	
	li $t0,0 #i=0

for:	bge $t0,$a0,endf 
	li $t1,0 #j=0

do:	addi $t4,$a1,16
	add $t4,$t4,$t1 #(pt->quest[j])
	lb $t5,0($t4) #ir buscar o valor de quest (acho que o offset devia ser 16)
	
	mtc1 $t5,$f8
	cvt.d.w $f8,$f8 #converte em double
	 
	add.d $f2,$f2,$f8 #sum += (double) pt->quest[j]
	addiu $t1,$t1,1 #j++
	
	lb $t6,4($a1) #ir buscar nm com ofsset 4 e meter em pt

while:	blt $t1,$t6,do
	l.d $f10,8($a1) #pt->grade
	div.d $f10,$f2,$f10 #sum / pt->grade
	cvt.w.d $f10,$f10 #converter para int
	mfc1 $t7,$f10
	sw $t7,0($a1) #n percebo esta linha
	addi $t0,$t0,1 #i++
	addi $a1,$a1,40 #tamanho da estrutura (pt++)
	
	j for
	

endf:	lw $t3,32($a1) #ir buscar cq com offset 32, ver tabela
	mtc1 $t3,$f4
	cvt.d.w $f4,$f4 #converter int em double
	l.d $f6,8($a1) #buscar grade c offset 8 ver tabela
	mul.d $f0,$f4,$f6 #return da lixeira toda 
	jr $ra


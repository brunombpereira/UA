# Typed struct
# {                   align       SIZE      Offset
#  int acc             4           4         0
#  unsigned char nm    1           1          4
#   double grade       8           8          5->8
#   char quest[14]     1           14         16
#  int cq              4           4          30->32
#  }t_kvd              8           40 #pq e multiplo de 8 

#Mapa Registos
#nv: $a0
#pt $a1
#i: $t0
#j: $t1
#sum: $f2
#return: $f0

	.data 
f1:	.double 0.0
	.text
	.globl func4
	
func4:	la $t2,f1
	l.d $f2,0($t2)        #sum = 0.0
	
	li $t0,0 
for:    bge $t0,$a0,endf
	li $t1,0
do:	addi $t4,$a1,16
	add $t4,$t4,$t1     #(pt->quest[j]))
	lb $t5,0($t4)       #ir buscar o valor de quest com o offset que está no $t4 e guardar $t5
	mtc1 $t5,$f8 
	cvt.d.w $f8,$f8    #coverter para double
	add.d $f2, $f2, $f8  #sum += ptquest[j]
	addi $t1,$t1,1        #k++
	lb $t6, 4($a1)       #ir buscar o nm com offset 4 e guardar no pt
	blt $t1,$t6,do       #j < pt-> nm
	l.d $f10,8($a1)      # pt-> grade 
	div.d $f10,$f2,$f10  
	cvt.w.d $f10,$f10    #coverter para int
	mfc1 $t7,$f10
	sw $t7,0($a1)		#guardar no acc offset 0
	addi $t0,$t0,1        #i++
	addi $a1,$a1,40        #tamanho da struct (pt++)
	j for

endf:	lw $t3, 32($a1)     #ir buscar o cq com offset 32 e guardar no pt
	mtc1 $t3,$f4        #
	cvt.d.w $f4,$f4     # covert para double (double) pt->cq 
	l.d $f6, 8($a1)     # ir buscar o grade e guardar no pt
	mul.d $f0,$f4,$f6   # por no $f0 para return 
	jr $ra
	
	
#Mapa de Registos
#a: $a0 -> porque � *a , estamos a passar o 1 endere�o do array, se fosse s� a era $f12
#t: $f12
#n: $a1
#oldg: $f2
#g: $f4
#s: $f6
#k: $t0
# return $f0

	.data
k1:	.float -1.0
k2:	.float 1.0
k3:	.float 0.0
	.text
	.globl func3
	
func3:	la $t1,k1
	l.s $f2,0($t0) #oldg = -1.0
	
	la $t1,k2
	l.s $f4,0($t1) #g = 1.0
	
	la $t1,k3
	l.s $f6,0($t2) #s = 0.0
	
	li $t0,0 #k=0
	
for:	bge $t0,$a1,endf
	sub.s $f8,$f4,$f2 #g - oldg
	#addi $t0,$t0,1

while:	c.le.s $f8,$f12
	bc1t endw
	mov.s $f2,$f4 #oldg = g
	
	sll $t1,$t0,2 #k*4
	add $t1,$t1,$a0 #&a[k]
	l.s $f16,0($t1)#$f16=a[k]
	
	add.s $f4,$f4,$f16 #g+a[k]
	div.s $f4,$f4,$f12 #g=(g+a[k])/t
	
	j while
	
endw:	add.s $f6,$f6,$f4 #s=s+g
	sll $t1,$t0,2 #k*4
	add $t1,$t1,$a0 #&a[k]
	
	s.s $f4,0($t1) #a[k]=g
	
	addiu $t0,$t0,1 #k++
	j for

endf:	mtc1 $a1,$f10 #meter no coprocessador para passar pra float
	cvt.s.w $f10,$f10 #(float) n
	div.s $f0,$f6,$f10 #return s / (float) n
	
	jr $ra

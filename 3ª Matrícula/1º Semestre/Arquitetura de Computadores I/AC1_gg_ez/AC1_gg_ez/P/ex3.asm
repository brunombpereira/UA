	.data
array:	.space 80
k0:	.double 0.0
	.eqv SIZE,10
	.eqv SIZE_8,80
	.eqv read_double,7
	.eqv print_double,3
	.text
	.globl main
main:
	addiu $sp,$sp,-4
	sw $ra, 0($sp)
	
	la $a0,array #$a0=array
	li $t0,0 #i=0
	
for1:
	bge $t0,SIZE,endf1
	
	sll $t1,$t0,3 #i*8
	addu $t2,$t1,$a0 #&aray[i]
	
	li $v0,read_double
	syscall
	
	s.d $f0,0($t2) #a[i]=read_double()
	
	addi $t0,$t0,1 #i++
	
	j for1
endf1:
	li $a1,SIZE
	jal average
	
	mov.d $f12,$f0
	li $v0,print_double
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	jr $ra
	
average:
	addi $t0,$a1,-1 #i=n-1
	
	la $t2,k0
	l.d $f2,0($t2) #double sum=0.0
for:
	blt $t0,0,endf
	
	sll $t1,$t0,3 #i*8
	addu $t3,$a0,$t1 #&array[i]
	
	l.d $f4,0($t3) #
	add.d $f2,$f2,$f4 #sum=+=array[i]
	
	addi $t0,$t0,-1
	
	j for
endf:
	mtc1 $a1,$f6
	cvt.d.w $f6,$f6
	div.d $f0,$f2,$f6
	
	jr $ra

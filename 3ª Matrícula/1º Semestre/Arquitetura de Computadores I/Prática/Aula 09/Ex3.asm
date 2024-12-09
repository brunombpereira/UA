	.data
	
k1:	.double 0.0

a:	.space 80

	.eqv SIZE,10
	.eqv read_double,7
	.eqv print_double,3
	
	.text
	.globl main
	
average:
	addi $t2,$a1,-1
	la $t0,k1
	l.d $f0,0($t0)
for:
	blt $t2,0,endf
	
	sll $t1,$t2,3
	addu $t1,$t1,$a0
	l.d $f2,0($t1)
	
	add.d $f0,$f0,$f2
	
	addi $t2,$t2,-1
	j for
endf:
	mtc1 $a1,$f2
	cvt.d.w $f2,$f2
	div.d $f0,$f0,$f2
	jr $ra

main:
	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	li $t0,0
for1:
	bge $t0,10,endf1
	
	li $v0,read_double
	syscall
	
	la $t1,a
	sll $t2,$t0,3
	addu $t1,$t1,$t2
	s.d $f0,0($t1)
	
	addi $t0,$t0,1
	j for1
endf1:
	la $a0,a
	li $a1,SIZE
	jal average
	
	mov.d $f12,$f0
	li $v0,print_double
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
	.data

a:	.space 80

	.eqv SIZE,10
	.eqv read_double,7
	.eqv print_double,3
	
	.text
	.globl main
	
max:
	addu $t0,$a0,$a1
	addiu $t0,$t0,-1
	
	l.d $f0,0($a0)
	addiu $a0,$a0,8
for:
	bgt $a0,$t0,endf
if:
	l.d $f2,0($a0)
	c.le.d $f2,$f0
	bc1t endif
	
	mov.d $f0,$f2
endif:
	addiu $a0,$a0,8
	j for
endf:
	jr $ra
	
main:
	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	li $t1,0
for1:
	bge $t1,10,endf1
	
	li $v0,read_double
	syscall
	
	la $t2,a
	sll $t3,$t1,3
	addu $t2,$t2,$t3
	s.d $f0,0($t2)
	
	addi $t1,$t1,1
	j for1
endf1:
	la $a0,a
	li $a1,SIZE
	jal max
	
	mov.d $f12,$f0
	li $v0,print_double
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
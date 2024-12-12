	.data
	
str0:	.asciiz "Média: "
str1:	.asciiz "Variância: "
str2:	.asciiz "Desvio padrão: "

zero:	.float 0.0
result:	.float 1.0
multi:	.double 0.5

arr:	.space 80

	.eqv read_double,7
	.eqv print_string,4
	.eqv print_double,3
	.eqv SIZE,10
	
	.text
	.globl main
	
average:	
	addi $t2,$a1,-1
	la $t0,zero
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
	
xtoy:
	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	li $t0,0
	la $t1,result
	l.s $f2,0($t1)
	jal abs
for1:
	bge $t0,$v0,endf
if:
	ble $a0,0,else
	
	mul.s $f2,$f2,$f12
	j endif
else:
	div.s $f2,$f2,$f12
endif:
	addi $t0,$t0,1
	j for
endf1:
	mov.s $f0,$f2
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
	
abs:
if2:
	bge $a0,0,endif2
	
	xor $a0,$a0,$a0
endif2:
	move $v0,$a0
	jr $ra
	
sqrt:
	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	la $t0,result
	l.d $f2,0($t0)
	l.d $f0,0($t0)
	li $t0,0
	la $t1,zero
	l.d $f4,0($t1)
	la $t2,multi
	l.d $f6,0($t2)
if1:
	c.le.d $f12,$f4
	bc1t else
do:
	mov.d $f2,$f0
	
	div.d $f8,$f12,$f0
	add.d $f8,$f8,$f0
	mul.d $f0,$f8,$f6
	
	addi $t0,$t0,1
	blt $t0,25,cond2
	j endif
cond2:
	c.eq.d $f2,$f0
	bc1f do
	j endif
else1:
	l.d $f0,0($t1)
endif1:
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
	
var:
	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	jal average
	cvt.s.d $f2,$f0
	
	li $t0,0
	la $t1,zero
	l.s $f4,0($t1)
	move $t3,$a1
for2:
	bge $t0,$t3,endf2
	
	sll $t1,$t0,3
	addu $t2,$a0,$t1
	l.d $f6,0($t1)
	cvt.s.d $f6,$f6
	sub.s $f12,$f6,$f2
	li $a1,2
	jal xtoy
	
	add.s $f4,$f4,$f0
	
	addi $t0,$t0,1
	j for2
endf2:
	cvt.d.s $f4,$f4
	mtc1 $t2,$f8
	cvt.d.w $f8,$f8
	div.d $f0,$f4,$f8
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
	
stdev:
	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	jal var
	
	mov.d $f12,$f0
	jal sqrt
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
	
main:
	li $t0,0
	li $t1,SIZE
for3:
	bge $t0,$t1,endf3
	
	sll $t2,$t0,3
	la $t3,arr
	addu $t3,$t3,$t2
	
	li $v0,read_double
	syscall
	
	s.d $f0,0($t3)
	
	addi $t0,$t0,1
	j for3
endf3:
	la $a0,str0
	li $v0,print_string
	syscall
	
	la $a0,arr
	li $a1,SIZE
	jal average
	
	mov.d $f12,$f0
	li $v0,print_double
	syscall
	
	la $a0,str1
	li $v0,print_string
	syscall
	
	la $a0,arr
	li $a1,SIZE
	jal var
	
	mov.d $f12,$f0
	li $v0,print_double
	syscall
	
	la $a0,str2
	li $v0,print_string
	syscall
	
	la $a0,arr
	li $a1,SIZE
	jal stdev
	
	mov.d $f12,$f0
	li $v0,print_double
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
# Mapa de Registos
# aux: 	$f2
# xn:  	$f0
# i:	$t0
# val:	$f12
# zero:	$f4

	.data
	
str:	.asciiz	"Sqrt: "

aux:	.double 1.0
zero:	.double 0.0
multi:	.double 0.5
val:	.double 144.0

	.eqv print_string,4
	.eqv print_double,3
	
	.text
	.globl main
	
sqrt:
	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	la $t0,aux
	l.d $f2,0($t0)
	l.d $f0,0($t0)
	li $t0,0
	la $t1,zero
	l.d $f4,0($t1)
	la $t2,multi
	l.d $f6,0($t2)
if:
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
else:
	l.d $f0,0($t1)
endif:
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
	
main:
	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	la $t0,val
	l.d $f12,0($t0)
	jal sqrt
	
	la $a0,str
	li $v0,print_string
	syscall
	
	mov.d $f12,$f0
	li $v0,print_double
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
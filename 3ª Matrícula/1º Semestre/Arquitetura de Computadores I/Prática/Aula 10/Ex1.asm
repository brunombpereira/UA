	.data
	
str0:	.asciiz "Resultado: "
	
result:	.float 1.0
x:	.float 2.0

	.eqv print_string,4
	.eqv print_float,2

	.text
	.globl main
	
xtoy:
	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	li $t0,0
	la $t1,result
	l.s $f2,0($t1)
	jal abs
for:
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
endf:
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
	
main:
	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	la $t0,x
	l.s $f12,0($t0)
	li $a0,2
	jal xtoy
	
	la $a0,str0
	li $v0,print_string
	syscall
	
	mov.s $f12,$f0
	li $v0,print_float
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
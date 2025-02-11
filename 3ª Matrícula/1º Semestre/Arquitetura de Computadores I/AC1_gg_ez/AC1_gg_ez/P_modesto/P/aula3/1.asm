#	MAPA DE REGISTOS:
#	SOMA - $T0
#	VALUE - $T1
#	I - $T2	
	.data
	.eqv print_string,4
	.eqv read_int,5
	.eqv print_int10,1
str1:	.asciiz "Introduza um numero: "
str2:	.asciiz "Valor ignorado\n"
str3:	.asciiz "A soma dos positivos e: "
	.text
	.globl main
main:	li $t2,0
	
	li $t0,0
for:	bge $t2,5,endfor
	
	la $a0,str1
	li $v0, print_string
	syscall
	
	li $v0,read_int
	syscall
	
	or $t1,$v0,$0
if:	blez $t1,else
	
	add $t0,$t0,$t1
	j endif
else:	la $a0,str2
	
	li $v0,print_string
	syscall
	
endif:	addi $t2,$t2,1
	j for

endfor:	la $a0,str3

	li $v0,print_string
	syscall
	
	or $a0,$t0,$0
	li $v0,print_int10
	syscall
	
	jr $ra
	
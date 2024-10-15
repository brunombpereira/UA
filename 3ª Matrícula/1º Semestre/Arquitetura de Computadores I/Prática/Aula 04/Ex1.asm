# Mapa de Registos
# num:    $t0
# i:      $t1
# str:    $t2
# str+i:  $t3
# str[i]: $t4


	.data
	
	.eqv SIZE,20
	.eqv read_string,8
	.eqv print_int10,1
	
str:	.space 21

	.text
	.globl main
main:
	la $a0,str
	li $a1,SIZE
	li $v0,read_string
	syscall
	
	li $t0,0
	li $t1,0
while:
	la $t2,str
	addu $t3,$t2,$t1
	lb $t4,0($t3)
	
	beq $t4,'\0',endw
if:
	blt $t4,'0',endif
	bgt $t4,'9',endif
	
	addiu $t0,$t0,1
endif:
	addiu $t1,$t1,1
	
	j while
endw:
	or $a0,$0,$t0
	li $v0,print_int10
	syscall
	
	jr $ra
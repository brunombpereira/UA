# Mapa de Registos
# *p:	       $t1
# *(p+1):      $t2
# i:           $t3
# houve_troca: $t4
# p:	       $t5
# pUltimo:     $t6


	.data
	
str1:	.asciiz "\nIntroduza um número: "
str2:	.asciiz "\nConteúdo do array:\n"
str3:	.asciiz "; "

	.eqv SIZE,10
	.eqv TRUE,1
	.eqv FALSE,0
	.eqv print_string,4
	.eqv read_int,5
	.eqv print_int10,1
	
	.align 2
lista:	.space 40

	.text
	.globl main
main:
	li $t3,0
	la $t5,lista
for:
	bge $t3,SIZE,endf
	
	la $a0,str1
	li $v0,print_string
	syscall
	
	li $v0,read_int
	syscall
	
	sw $v0,0($t5)
	
	addiu $t5,$t5,4
	addi $t3,$t3,1
	
	j for
endf:
do:
	li $t4,FALSE
	la $t5,lista
	li $t0,SIZE
	addi $t0,$t0,-1
	sll $t0,$t0,2
	addu $t6,$t5,$t0
for2:
	bge $t5,$t6,endf2
	
	lw $t1,0($t5)
	lw $t2,4($t5)
if:
	ble $t1,$t2,endif
	
	sw $t1,4($t5)
	sw $t2,0($t5)
	
	li $t4,TRUE
endif:
	addiu $t5,$t5,4
	j for2
endf2:
	beq $t4,TRUE,do
endw:
	li $t3,0
	la $t5,lista
	
	la $a0,str2
	li $v0,print_string
	syscall
for3:
	bge $t3,SIZE,endf3
	
	lw $a0,0($t5)
	li $v0,print_int10
	syscall
	
	la $a0,str3
	li $v0,print_string
	syscall
	
	addiu $t5,$t5,4
	addi $t3,$t3,1
	j for3
endf3:
	jr $ra
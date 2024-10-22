# Mapa de Registos
# aux:         $t0
# lista[i+1]:  $t2
# lista[i]:    $t3
# houve_troca: $t4
# i:	       $t5
# lista:       $t6
# lista + i:   $t7


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
	li $t5,0
for:
	bge $t5,SIZE,do
	
	la $a0,str1
	li $v0,print_string
	syscall
	
	li $v0,read_int
	syscall
	
	sll $t7,$t5,2
	la $t6,lista
	addu $t7,$t7,$t6
	
	sw $v0,0($t7)
	
	addi $t5,$t5,1
	
	j for
	
do:	
	li $t4,FALSE
	li $t5,0
for2:
	bge $t5,9,endf2
	
	la $t6,lista
	sll $t7,$t5,2
	addu $t7,$t7,$t6
	lw $t3,0($t7)
	lw $t2,4($t7)
if:
	ble $t3,$t2,endif
	
	sw $t3,4($t7)
	sw $t2,0($t7)
	
	li $t4,TRUE
endif:
	addi $t5,$t5,1
	j for2
endf2:
	beq $t4,TRUE,do
endw:
	la $a0,str2
	li $v0,print_string
	syscall
	
	li $t5,0
for3:
	bge $t5,SIZE,endf3
	
	la $t6,lista
	sll $t7,$t5,2
	addu $t7,$t7,$t6
	
	lw $a0,0($t7)
	li $v0,print_int10
	syscall
	
	la $a0,str3
	li $v0,print_string
	syscall
	
	addi $t5,$t5,1
	
	j for3
endf3:
	jr $ra
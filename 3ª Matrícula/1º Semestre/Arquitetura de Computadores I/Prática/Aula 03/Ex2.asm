# Mapa de Registos
# value: $t0
# bit:   $t1
# i:     $t2



	.data
	
str1:	.asciiz "Introduza um número: "
str2:	.asciiz "\nO valor em binário é: "

	.eqv print_string,4
	.eqv read_int,5
	.eqv print_char,11
	
	.text
	.globl main
main:
	li $t2,0
	li $t3,0x80000000
	
	la $a0,str1
	ori $v0,$0,print_string
	syscall
	
	ori $v0,$0,read_int
	syscall
	
	or $t0,$0,$v0
	
	la $a0,str2
	ori $v0,$0,print_string
	syscall
	
for:
	rem $t4,$t2,4
if01:
	bne $t4,0,endif01
	li $a0,' '
	ori $v0,$0,print_char
	syscall
endif01:
	and $t1,$t0,$t3
	srl $t1,$t1,31
	addi $t4,$t1,0x30

	or $a0,$0,$t4
	li $v0,print_char
#	addi $a0,$t1,0x30
	syscall
#if:
#	beq $t1,0,else
#	li $a0,'1'
#	ori $v0,$0,print_char
#	syscall
#	
#	j endif
#else:
#	li $a0,'0'
#	ori $v0,$0,print_char
#	syscall
#endif:
	sll $t0,$t0,1
	
	beq $t2,31,endfor
	addi $t2,$t2,1
	
	j for
endfor:
	jr $ra
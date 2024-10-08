# Mapa de Registos
# soma:  $t0
# value: $t1
# i:     $t2


	.data
	
str1:	.asciiz "Introduza um número: "
str2:	.asciiz "Valor Negado\n"
str3:	.asciiz "A soma dos positivos é: "

	.eqv print_string,4
	.eqv read_int,5
	.eqv print_int10,1
	
	.text
	.globl main
main:
	li $t2,0
	li $t0,0
for:
	la $a0,str1
	ori $v0,$0,print_string
	syscall
	
	ori $v0,$0,read_int
	syscall
	
	or $t1,$0,$v0
if:
	ble $t1,0,else
	add $t0,$t0,$t1
	
	beq $t2,4,endfor
	addi $t2,$t2,1
	j for
else:
	la $a0,str2
	ori $v0,$0,print_string
	syscall
	
	beq $t2,4,endfor
	addi $t2,$t2,1
	j for
endfor:
	la $a0,str3
	ori $v0,$0,print_string
	syscall
	
	or $a0,$0,$t0
	ori $v0,$0,print_int10
	syscall
	
	jr $ra
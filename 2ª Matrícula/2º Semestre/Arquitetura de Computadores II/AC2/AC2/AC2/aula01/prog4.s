	.data
	.equ printstr,8
	.equ printint,6
	.equ printint10,7
	.equ readint10,5
msg:	.asciiz "\nIntroduza um inteiro (sinal e modulo): "
msg2:	.asciiz "\nValor em base 10 (signed): "
msg4:	.asciiz "\nValor em base 2: "
msg5:	.asciiz "\nValor em base 16: "
msg6: 	.asciiz "\nValor em base 10(unsigned): "
msg7: 	.asciiz "\nValor em base 10(unsigned), formatado: "
	.text
	.globl main
main:	li $t0,1
while:  bne $t0,1,endw
	la $a0,msg
	li $v0, printstr
	syscall
	li $v0,readint10
	syscall
	move $t1,$v0

	la $a0,msg2
	li $v0,printstr
	syscall
	move $a0,$t1
	li $v0,printint10
	syscall

	la $a0,msg4
	li $v0,printstr
	syscall
	move $a0,$t1
	li $a1,2
	li $v0,printint
	syscall

	la $a0,msg5
	li $v0,printstr
	syscall
	move $a0,$t1
	li $a1,16
	li $v0,printint
	syscall

	la $a0,msg6
	li $v0,printstr
	syscall
	move $a0,$t1
	li $a1,10
	li $v0,printint10
	syscall

	la $a0,msg7
	li $v0,printstr
	syscall
	move $a0,$t1
	li $t2,5
	sll $t2,$t2,16
	ori $t2,$t2,10
	move $a1,$t2
	li $v0,printint

	j while
endw:	li $t0,0
	jr $ra



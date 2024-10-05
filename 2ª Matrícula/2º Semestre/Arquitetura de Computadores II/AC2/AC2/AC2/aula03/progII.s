	.data
	.equ resetcoretimer,12
	.equ SFR_BASE_HI,0xBF88
	.equ readcoretimer,11
	.equ TRISE,0x6100
	.equ LATE,0x6120
	.equ TRISB,0x6040
	.equ PORTB,0x6050
	.text
	.globl main
main:	lui $t0,SFR_BASE_HI
	lw $t1,TRISB($t0)
	ori $t1,$t1,0x000E
	sw $t1,TRISB($t0)		#RB3-1 AS IN

	lw $t1,TRISE($t0)
	andi $t1,$t1,0xFFE1
	sw $t1,TRISE($t0)		#RE4-1 AS OUT

	li $t2,0			#inicializar contagem
loop:	li $a0,500
	jal delay
	lw $t3,LATE($t0)
	andi $t3,$t3,0xFFE1	#11100001
	sll $t4, $t2, 1
	or $t3,$t3,$t4
	sw $t3,LATE($t0)
	addi $t2,$t2,1
	andi $t2, $t2, 0x000F
	j loop


delay:	mul $a0,$a0,20000
	li $v0,resetcoretimer
	syscall
whr:	li $v0,readcoretimer
	syscall
	blt $v0,$a0,whr
	li $v0,0
	jr $ra

	.equ SFR_BASE_HI, 0xBF88
	.equ READ_CORE_TIMER,11
	.equ RESET_CORE_TIMER,12
    .equ TRISB, 0x6040
	.equ PORTB, 0x6050
	.equ LATB, 0x6060
	.equ TRISE, 0x6100           
	.equ PORTE, 0x6110            
	.equ LATE,  0x6120            

	.equ readInt10,5
	.equ printStr,8
	.data
	str1:	.asciiz "\nEscolha uma das opcoes(1,2 ou 3): \n"
	str2:	.asciiz "Ex1- Ler RB0 e escrever no RE0. \n"
	str3:	.asciiz "Ex2- Escrever em RE0 o valor negado de RB0. \n"
	str4:	.asciiz "Ex3- RE0 = RB0\ RE1= RB1 RE2= RB2 RE3= RB3\ . \n"
	str5: 	.asciiz "\n ----------------opçao invalida------------------\n"


	.text
	.globl main

main:	
	la $a0,str1
	li $v0,printStr
	syscall	

	la $a0,str2
	li $v0,printStr
	syscall

	la $a0,str3
	li $v0,printStr
	syscall

	la $a0,str4
	li $v0,printStr
	syscall

	li $v0,readInt10	#user escolhe
	syscall
	
	beq $v0, 1, opcao1		#menu
	beq $v0, 2, opcao2
	beq $v0, 3, opcao3

	la $a0,str5
	li $v0,printStr 	#opção invalida
	syscall 

	j main

	

#opçao 1
opcao1:
	
	lui $t1,SFR_BASE_HI
	lw $t2,TRISB($t1)	#RB0 como entrada
	ori $t2,$t2,1
	sw $t2,TRISB($t1)

	lw $t3,TRISE($t1)	#RE0 como saida
	andi $t3,$t3,0xFFFE
	sw $t3,TRISE($t1)

while1:	
	lw $t0,PORTB($t1)	#Read
						#nao é necessario modificar	
	sw $t0,LATE($t1)	#write

	j while1

#opção 2
opcao2:	
	lui $t1,SFR_BASE_HI

	lw $t2,TRISB($t1)	#RB0 como entrada
	ori $t2,$t2,0x0001
	sw $t2,TRISB($t1)

	lw $t3,TRISE($t1)	#RE0 como saida
	andi $t3,$t3,0xFFFE
	sw $t3,TRISE($t1)


while2:	lw $t0,PORTB($t1)	#read
	xori $t0,$t0,1			#negação
	sw $t0,LATE($t1)		#write
	
	j while2

#opção 3
opcao3:
	lui $t0,SFR_BASE_HI 	

	lw $t1,TRISB($t0)
	ori $t1, $t1,0x000F	#RB[3..0]=1111 (input)		
	sw $t1,TRISB($t0)
	
 	
	lw $t1,TRISE($t0)
	andi $t1,$t1,0xFFF0	#RE[3..0]=0000 [output]
	sw $t1,TRISE($t0)
	
while3:
	lw $t2,PORTB($t0)	#read
	xori $t2,$t2,9		#1001 
	sw $t2,LATE($t0)	#write
	j while3

	jr $ra
























	
# Leia em ciclo infinito od dip-switches
# Valor lido em complemento para 1
# Apresentar valor lido em led em modo gráfico de barra
# Led mais significativo indica numero

		.equ SFR_BASE_HI, 0xBF88
		#leds
		.equ  TRISE, 0x6100
		.equ  PORTE, 0x6110
		.equ  LATE, 0x6120
		#dip-switch
		.equ	PORTB, 0x6050
		.equ	LATB, 0x6060
		.equ	TRISB, 0x6040
		.equ	print_string, 8

		.data
str:	.asciiz	"oh hello"
		.text
		.globl 	main

main:	lui		$t0, SFR_BASE_HI
		#config entradas
		lw		$t1, TRISB($t0)
		ori		$t1, $t1, 0x0007
		sw		$t1, TRISB($t0)

		#config saidas
		lw		$t2, TRISE($t0)
		andi	$t2, $t2, 0xFFF0
		sw		$t2, TRISE($t0)

		#ler entradas
ciclo:	lw		$t3, PORTB($t0)
		andi	$t3, $t3, 0x0007
		andi	$t9, $t3, 0x0004					#isolar sinal do numero: pos ou neg
		beq		$t9, 4, neg

pos:	sll		$t3, $t3, 1

disp:	lw		$t4, LATE($t0)
		andi	$t4, $t4, 0xFFF0
		or		$t4, $t4, $t3
		sw		$t4, LATE($t0)
		j		ciclo

neg:	xori 	$t3, $t3, 0x0007				#negar o numero
		sll		$t3, $t3, 1
		ori		$t3, $t3, 0x0001			#1º led fica a um quando nº negativo
		j		disp

		jr	$ra

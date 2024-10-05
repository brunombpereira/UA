		.data
str1:	.asciiz "\nIntroduza um numero (sinal e módulo):"
str2:	.asciiz	"\nValor lido em base 2:"
str3:	.asciiz	"\nValor lido em base 16: "
str4:	.asciiz	"\nValor lido em base 10 (unsigned):"
str5:	.asciiz "\nValor lido em base 10 (signed): "
		.equ printStr,8
		.equ readInt10,5
		.equ printInt10,7
		.equ printInt,6
		.text
		.globl main
main:	la $a0, str1
		li $v0, printStr		#printStr("\nIntroduza um numero (sinal e módulo): ");
		syscall


		li $v0, readInt10
		syscall
		move $s0, $v0			#value = readInt10();

								
		la $a0, str2
		li $v0, printStr		
		syscall					#printStr("\nValor lido em base 2")

		li $v0, printInt
		move $a0, $s0			#printInt(value, 2);
		li $a1,2
		syscall

		la $a0, str3
		li $v0, printStr		
		syscall					#printStr("\nValor lido em base 16")

		li $v0, printInt
		move $a0, $s0			#printInt(value, 16);
		li $a1,16
		syscall


		la $a0, str4
		li $v0, printStr		
		syscall					#printStr("\nValor lido em base 10 unsigned")

		li $v0, printInt
		move $a0, $s0			#printInt(value,10);
		li $a1,10
		syscall

		la $a0, str5
		li $v0, printStr		
		syscall					#printStr("\nValor lido em base 10 signed")

		li $v0, printInt10
		move $a0, $s0			#printInt(value, 10);
		syscall

		j main

		jr $ra




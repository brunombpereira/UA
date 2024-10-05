	.data
	.equ printStr,8
	.equ readStr,9
	.equ printInt10,7
	.equ printInt,6
	.equ STR_MAX_SIZE, 20
	.equ PUT_CHAR,3
str: .asciiz "\nintroduza 2 strings: \n"
stre: .asciiz "\nresultados\n"
str1: .space STR_MAX_SIZE+1
str2: .space STR_MAX_SIZE+1
str3: .space 2*STR_MAX_SIZE+1
	.text
	.globl main

main:	subu $sp,$sp, 4
		sw $ra, 0($sp)

		li $v0, printStr
		la $a0, str
		syscall

		li $v0, readStr
		la $a0, str1
		li $a1, STR_MAX_SIZE
		syscall

		jal espaco

		li $v0, readStr
		la $a0, str2
		li $a1, STR_MAX_SIZE
		syscall


		li $v0, printStr
		la $a0, stre
		syscall

		jal espaco

		la $a0, str1
		jal strlen
		li $a1, 10					#prinInt( strlen(str1), 10 );
		move $a0, $v0
		li $v0, printInt
		syscall

		jal espaco
		
		la $a0, str2
		jal strlen
		li $a1, 10					#prinInt( strlen(str2), 10 );
		move $a0, $v0
		li $v0, printInt
		syscall

		jal espaco

		la $a0, str3				#strcpy(str3, str1);
		la $a1, str1
		jal strcpy

		la $a0, str3				#strcat(str3, str2);
		la $a1,	str2
		jal strcat
		move $a0, $v0
		li $v0, printStr
		syscall	

		jal espaco

		la $a0, str1				
		la $a1, str2						#strcmp(str1, str2)
		jal strcmp
		move $a0, $v0
		li $v0, printInt10
		syscall	

		lw $ra, 0($sp)
		subu $sp,$sp, -4
		
		li $v0, 0
		jr $ra


#------------------------------------------------
strlen:
		li $t0, 0				#t0= len
for1:	lb $t1, 0($a0)			#a0=s (char)
		beqz $t1, endstrlen		#t1=*s
		addi $t0, $t0, 1		#len++
		addi $a0, $a0, 1		#s++
		j for1

endstrlen:	move $v0, $t0			#return len
		jr $ra

#----------------------------------------------
strcat:	subu $sp,$sp,16
		sw $ra, 0($sp)
		sw $s0, 4($sp)
		sw $s1, 8($sp)
		sw $s2, 12($sp)
		move $s0,$a0
		move $s1,$a1
		move $s2, $a0			#char *rp = dst;
for2:	lb $t1, 0($s0)
		beqz $t1, endstrcat
		addi $s0, $s0, 1		#dst++
		j for2
endstrcat:	
		move $a0, $s0 
		move $a1, $s1
		jal strcpy				#strcpy(dst, src);
		move $v0, $s2			#return rp;
		lw $ra, 0($sp)
		lw $s0, 4($sp)
		lw $s1, 8($sp)
		lw $s2, 12($sp)
		subu $sp,$sp,-16
		jr $ra
#-----------------------------------------------
strcpy:
		move $t0, $a0			#char *rp = dst;

for3:	lb $t1, 0($a1)			#t1 =*src
		sb $t1, 0($a0)			#*dst = *src
		beq $t1, $0, endstrcpy
		addi $a0, $a0, 1		#dst++
		addi $a1, $a1, 1		#src++
		j for3
endstrcpy:
		move $v0, $t0			#return rp;
		jr $ra

#---------strcmp-------------
strcmp:
forcmp:
		lb $t0, 0($a0)
		lb $t1, 0($a1)
		bne $t0, $t1, endcmp
		beq $t0, $0, endcmp
		addi $a0,$a0,1		#s1++
		addi $a1,$a1,1		#s2++
		j forcmp

endcmp:
		sub $v0, $t0, $t1
		jr $ra


#---------espaços-----------
espaco:
		li $a0,'\n'
		li $v0,PUT_CHAR
		syscall	
		jr $ra


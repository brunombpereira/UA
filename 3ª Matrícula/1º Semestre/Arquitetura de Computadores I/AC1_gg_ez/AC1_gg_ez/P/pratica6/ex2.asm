 # p : $t1
# pultimo: $t2 	
 	.eqv SIZE,3
# 	.eqv SIZE_4,12 #3*4
 	.data
array:	.word str1,str2,str3
str1:	.asciiz "Array"
str2:	.asciiz "de"
str3:	.asciiz "ponteiros"
	.eqv print_string,4
	.eqv print_char,11

	.text
	.globl main

main:
 	la $t1,array # $t1 = p = &array[0] = array
 	li $t0,SIZE #
 	sll $t0,$t0,2 # 3*4
 	addu $t2,$t1,$t0 # $t2 = pultimo = array + SIZE

for: 	bge $t1,$t2,endf
	
	lw $a0,0($t1)
	li $v0,4
	syscall #print_string(*p);
	
	li $a0,'\n'
	li $v0,print_char
	syscall
	
	addiu $t1,$t1,4 #p++
 	j for
 
endf: 	jr $ra
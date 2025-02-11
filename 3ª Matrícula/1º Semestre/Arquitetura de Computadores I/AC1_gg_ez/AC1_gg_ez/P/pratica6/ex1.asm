# i: $t0
# &array[0]: $t1
# i*4: $t2
# &array[i]: $t3

 	.eqv SIZE,3
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
 	li $t0,0 #i=0
 	#la $t1,array

for: 	bge $t0,SIZE,endf
	
	la $t1,array # $t1 = &array[0]
 	
 	sll $t2,$t0,2 # i*4
 	addu $t3,$t2,$t1 # $t2 = &array[i]
 	
 	lw $a0,0($t3) # $a0 = array[i]
 	li $v0,print_string
	syscall
	
	li $a0,'\n'
	li $v0,print_char
	syscall
	
	addiu $t0,$t0,1
	j for

endf:	jr $ra
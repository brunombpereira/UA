	.data
	.align 2
stg:	.word 72343    #unsigned int id_number
	.asciiz "Napoleao" #char first_name[10]
	.space 9
	.asciiz "Bonaparte"  #char last_name[15]
	.space 5
	.align 2             #ou .space 3
	.float 9.1  #float grade

str1:	.asciiz "\nN. Mec: "
str2:	.asciiz "\nNome: "
str3:	.asciiz "\nNota: "
str4:	.asciiz "N.Mec: "
str5:	.asciiz "Primeiro Nome: "
 	.eqv print_string,4
 	.eqv print_intu10,36
 	.eqv print_char,11
 	.eqv print_float,2
 	.eqv read_int,5
 	.eqv read_string,8
	.text
	.globl main

main:	la $t0,stg
	
	la $a0,str4
	li $v0,print_string 
	syscall #print_string("N.Mec:") 
	li $v0,5
	syscall #read_int()
	sw $v0,0($t0) #stg.id_number()=read_int()
	
	la $a0,str5
	li $v0,4
	syscall #print_string("Primeiro Nome: ")
	addiu $a0,$t0,22
	li $a1,17 #pq stg.first_name,17
	li $v0,read_string
	syscall
	
	la $a0,str1
	li $v0,4
	syscall #print_string("\nN. Mec: ")
	lw $a0,0($t0)
	li $v0,print_intu10
	syscall #print_intu10(stg.id_number);


	#perceber a partir daqui
	la $a0,str2
 	li $v0,print_string
 	syscall#print_string("\nNome: ")
 	addiu $a0,$t0,22
 	li $v0,print_string
 	syscall#print_sting(stg.last_name)
 	li $a0,','
 	li $v0,print_char
 	syscall#print_char(",")
 	addiu $a0,$t0,4
 	li $v0,print_string
 	syscall#print_string(stg.first_name)
 	la $a0,str3
 	li $v0,print_string
 	syscall#print_string("\nNota: ")
 	l.s $f12,40($t0)
 	li $v0,print_float
 	syscall#print_float(stg.grade)
 	jr $ra

	
	
#	mapa de registos
#p = $t0
#*p = $t1
	#NAO FUNCIONA :)
	.data
	.eqv SIZE,20
	.eqv print_string,4
	.eqv read_string,8
str:	.space 21	#size+1
str1:	.asciiz  "Introduza uma string: "
	.text
	.globl main

main:	la $a0,str1
	li $v0,4
	syscall #print_string("Introduza uma string: ");
	
	la $a0,str
	li $a1,SIZE
	li $v0,8
	syscall #read_string(str, SIZE); 
	
	la $t0,str #$t0=p=str=&str[0]
	
	li $t3,0x61
	li $t4,0x41

while:	lb $t1,0($t0) #$t1=*p
	beq $t1,'\0',endw #while (*p != '\0') 
	sub $t5,$t1,$t3 #*p = *p – 'a' + 'A'; // 'a'=0x61, 'A'=0x41, 'a'-'A'=0x20
	add $t6,$t5,$t4
	sb $t6,0($t0)
	addiu $t0,$t0,1 #p++
	j while

endw:	la $a0,str
	li $v0,4
	syscall #print_string(str); 
	jr $ra

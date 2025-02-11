	.data
str1:	.asciiz "I serodatupmoC ed arutetiuqrA"
str2:	.space 31
enter:	.asciiz "\n"
str3:	.asciiz "String too long: "
	.eqv STR_MAX_SIZE,30
	.eqv print_string,4
	.eqv print_int10,1
	.text
	.globl main
	

#strcpy() começa
strcpy:	li $t0,0 #i=0

do:	addu $t1,$a0,$t0 #&dst[i]
	addu $t2,$a1,$t0 #&src[i]
	
	lb $t3,0($t2) #src[i]
	sb $t3,0($t1) #dst[i]=src[i]

	addiu $t0,$t0,1 #i++

while:	bne $t3,'\0',do 
	
	move $v0,$a0
	jr $ra #strcpy() acaba

#strrev começa
strrev:	addiu $sp,$sp,-16
	sw $ra,0($sp)
	sw $s3,4($sp)
	sw $s4,8($sp)
	sw $s5,12($sp)
	
	move $s3,$a0		#callee-saved
	move $s4,$a0		#p1=str
	move $s5,$a0		#p2=str
	
while1: lb $t0,0($s5)		#*p2
	beq $t0,'\0',endw1	#*p2 != '\0'
	addiu $s5,$s5,1	#p2++
	j while1
	
endw1:	addiu $s5,$s5,-1	#p2--

while2: bge $s4,$s5,endw2	#p1<p2

	lb $a0,0($s4)		
	lb $a1,0($s5)
	jal exc
	
	sb $a0,0($s4)
	sb $a1,0($s5)
	
	addiu $s4,$s4,1
	addiu $s5,$s5,-1

	j while2

endw2:	move $v0,$s3

	lw $ra,0($sp)
	lw $s3,4($sp)
	lw $s4,8($sp)
	lw $s5,12($sp)
	addiu $sp,$sp,16
	
	jr $ra #strrev acaba	
	
#exchange começa
exc:	move $t0,$a0
	move $a0,$a1
	move $a1,$t0
	jr $ra #exchange acaba

#strlen começa
strlen:	li $t1,0

whilz:	lb $t0,0($a0)
	addiu $a0,$a0,1
	beq $t0,'\0',endw
	addi $t1,$t1,1
	j whilz
endw:	move $v0,$t1
	jr $ra #strlen acaba

#main começa
main:	addiu $sp,$sp,-16 #prologo
	sw $ra,0($sp)
	sw $s0,4($sp) #exit_value
	sw $s1,8($sp) #str1
	sw $s2,12($sp) #str2
	
	la $t1,str1
	la $t2,str2
	
	move $s1,$t1 #str1
	move $s2,$t2 #str2
	move $s0,$t0 #exit_value
	
	move $a0,$s1 #passar str1 para o parametro de entrada da funçao strlen
	jal strlen #o valor vai ser retornado em $v0

if:	bgt $v0,STR_MAX_SIZE,else
	
	move $a0,$s2 #passar para os parametros de 
	move $a1,$s1 #entrada da funçao strcpy o str2 e str1
	jal strcpy
	
	move $s2,$v0 #meter no s2 o que vem da strcpy
	
	move $a0,$s2
	li $v0,4
	syscall #print_string(str2); 
	
	la $a0,enter
	li $v0,print_string
	syscall #print_string("\n");
	
	move $a0,$s2 #passar str2 p/ parametro de entrada
	jal strrev #da strrev
	
	move $a0,$v0 
	li $v0,4
	syscall #print_string(strrev(str2));
	
	li $s0,0 #exit_value = 0; 
	
	j endif
	
else:	la $a0,str3
	li $v0,print_string
	syscall
	
	move $a0,$s1
	jal strlen
	
	move $a0,$v0
	li $v0,print_int10
	syscall
	
	li $s0,-1


endif:	move $v0,$s0
	lw $ra,0($sp)
	lw $s0,4($sp) #exit_value
	lw $s1,8($sp) #str1
	lw $s2,12($sp) #str2
	addiu $sp,$sp,16 #epilogo
	
	jr $ra

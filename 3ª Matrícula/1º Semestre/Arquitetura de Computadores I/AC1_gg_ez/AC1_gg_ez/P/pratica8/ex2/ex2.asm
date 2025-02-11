	.data
	.eqv MAX_STR_SIZE,33
str:	.space MAX_STR_SIZE
	.eqv read_int,5
	.eqv print_string,4
	.eqv print_char,11
	.text
	.globl main

exchange: lb $t0,0($a0)
	lb $t1,0($a1)
	sb $t1,0($a0)
	sb $t0,0($a1)
	jr $ra
	
strrev:	addiu $sp,$sp,-16
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	move $s0,$a0
	move $s1,$a0
	move $s2,$a0
while_1: lb $t1,0($s2)
	beq $t1,'\0',endw_1
	addiu $s2,$s2,1 
	j while_1
endw_1:	addiu $s2,$s2,-1
while2:	move $a0,$s1
	move $a1,$s2
	bge $s1,$s2,endw2	
	jal exchange
	addiu $s1,$s1,1
	addiu $s2,$s2,-1
	j while2
endw2:	move $v0,$s0
	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	addiu $sp,$sp,16
	jr $ra

itoa:	addiu $sp,$sp,-24 #prologo
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	sw $s3,16($sp)
	sw $s4,20($sp)
	
	move $s0,$a0 #n
	move $s1,$a1 #b
	move $s2,$a2 #s
	move $s3,$a2 #p=s
	#$s4 -> digit
	
do:	rem $s7,$s0,$s1 #digit = n % b; 
	div $s0,$s0,$s1 #n = n / b; 
	
	move $a0,$s7 #para digit ser parametro de entrada 
	jal toascii # toascii( digit );
	
	sb $v0,0($s3) #*p=toascii( digit );
	addi $s3,$s3,1 #p++

while:	bgt $s0,0,do #}whlie(n>0)
	
	#li $t0,'\0'
	sb $0,0($s3) #*p = '\0'; 
	
	move $a0,$s2 #para s ser o parametro de entrada
	jal strrev #strrev(s)
	#o return de strrev ja vem em $v0
	
	lw $s4,20($sp)
	lw $s3,16($sp)
	lw $s2,12($sp)
	lw $s1,8($sp)
	lw $s0,4($sp)
	lw $ra,0($sp)
	addiu $sp,$sp,24 #epilogo
	
	jr $ra
	
toascii: addi $a0,$a0,'0'
if:	 ble $a0,'9',endif
	 addi $a0,$a0,7
	
endif:	move $v0,$a0
	jr $ra

main:	addiu $sp,$sp,-12 #prologo
	sw $ra,0($sp)
	sw $s0,4($sp) #str
	sw $s1,8($sp) #val
	
	la $s0,str

do_1:	li $v0,5
	syscall #read_int()
	move $s1,$v0 #val=read_int()
	
	move $a0,$s1
	li $a1,2
	move $a2,$s0 #para termos os parametros de entrada $a0,$a1 e $a2 da funçao
	jal itoa 
	
	move $a0,$v0
	li $v0,print_string
	syscall #print_string( itoa(val, 2, str) );
	
	li $a0,'\n'
	li $v0,print_char
	syscall 
	
	move $a0,$s1
	li $a1,8
	move $a2,$s0 #para termos os parametros de entrada $a0,$a1 e $a2 da funçao
	jal itoa 
	
	move $a0,$v0
	li $v0,print_string
	syscall #print_string( itoa(val,8, str) );
	
	li $a0,'\n'
	li $v0,print_char
	syscall
	
	move $a0,$s1
	li $a1,16
	move $a2,$s0 #para termos os parametros de entrada $a0,$a1 e $a2 da funçao
	jal itoa 
	
	move $a0,$v0
	li $v0,print_string
	syscall #print_string( itoa(val,8, str) );
	
	li $a0,'\n'
	li $v0,print_char
	syscall

while_do: bne $s1,0,do
	
	li $v0,0 #return 0
	
	lw $s1,8($sp)
	lw $s0,4($sp)
	lw $ra,0($sp)
	addiu $sp,$sp,12 #epilogo
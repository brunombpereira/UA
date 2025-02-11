#void main(void)
#{
# unsigned int value, bit, i;
#
# print_string("Introduza um numero: ");
# value = read_int();
# print_string("\nO valor em binário e': ");
#int i=0;
#int flag=0;
#do
# {
# 	bit = value >> 31;
# 	if(flag == 1 || bit != 0)
# 	{
# 		flag = 1;
# 		if((i % 4) == 0)
# 			print_char(' ');
# 		print_char(0x30 + bit);
# 	}
# 	value = value << 1;
#	i++;
# }while(i<32) 
#} 

#	MAPA DE REGISTOS
#	VALUE - $t0
#	BIT   - $t1
#	I     - $t2
#	FLAG  - $t3

	.data
str1:	.asciiz "Introduza um numero: "
str2:	.asciiz "\nO valor em binário e': "
	.eqv print_string,4
	.eqv read_int,5
	.eqv print_char,11
	.text
	.globl main

main:	la $a0,str1
	li $v0,print_string # (instrução virtual)
	syscall # print_string(str1);
	
	ori $v0,$0,5
	syscall
	move $t0,$v0 # value=read_int();
	
	la $a0,str2
	li $v0,print_string
	syscall # print_string(str2);
	
	li $t2,0 # i = 0

do:	srl $t1,$t0,31 

if_2:	beq $t3,1,in
	bne $t1,0,in
	
	j endif_2

in:	li $t3,1

if_1:	rem $t4,$t2,4 #i%4
	bne $t4,0,endif_1 #if((i % 4) == 0)
	
	li $a0,' '
	li $v0,11
	syscall #print_char(' ');
	
	
endif_1: 
	addi $a0,$t1,0x30 #(0x30 + bit)
	li $v0,11
	syscall #print_char(0x30 + bit);
	
endif_2: 
	sll $t0,$t0,1 #value = value << 1;
	addi $t2,$t2,1# i++;

while:	blt $t2,32,do # }while(i<32)
	jr $ra 
	

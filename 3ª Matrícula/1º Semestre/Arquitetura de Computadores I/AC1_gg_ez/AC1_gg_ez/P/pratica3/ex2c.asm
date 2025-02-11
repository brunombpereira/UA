#void main(void)
#{
 #unsigned int value, bit, i;

 #print_string("Introduza um numero: ");
 #value = read_int();
 #print_string("\nO valor em binário e': ");
 #for(i=0; i < 32; i++)
 #{
 #if((i % 4) == 0) // resto da divisão inteira
 #print_char(' ');
 #bit = (value & 0x80000000) >> 31;
 #print_char(0x30 + bit);
 
 # Mapa de registos:
# value: $t0
# bit: $t1
# i: $t2
 
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
	or $t0,$v0,$0 # value=read_int();
	
	la $a0,str2
	li $v0,print_string
	syscall # print_string(str2);
	
	li $t2,0 # i = 0

for:	bge $t2,32,endfor # while(i < 32) {

if_1:	rem $t4,$t2,4 #i%4
	bne $t4,0,endif_1 #if((i % 4) == 0)
	
	li $a0,' '
	li $v0,11
	syscall #print_char(' ');
	

endif_1: li $t3,0x80000000 #
	and $t1,$t0,$t3 # bit=value & 0x80000000
	srl $t1,$t1,31 #bit = (value & 0x80000000) >> 31;
	
	addi $a0,$t1,0x30 #(0x30 + bit)
	li $v0,11
	syscall #print_char(0x30 + bit);
	
	sll $t0,$t0,1 #value = value << 1;
	addi $t2,$t2,1# i++;
	j for # }

endfor: #
	jr $ra # fim do programa

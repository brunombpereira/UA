#	MAPA DE REGISTOS
#	VALUE - $t0
#	BIT   - $t1
#	I     - $t2
#	FLAG  - $t3
	.data
str1:	.asciiz "Introduza um numero: "
str2:	.asciiz "\nO valor em binario e: "
	.eqv print_string,4
	.eqv read_int,5
	.eqv print_char,11
	.text
	.globl main
main:	la $a0,str1

	li $v0, print_string
	syscall
	
	li $v0,read_int
	syscall
	
	move $t0,$v0
	
	la $a0,str2
	li $v0,print_string
	syscall

	li $t2,0
	li $t3,0
for:	bge $t2,32,endfor



	srl $t1,$t0,31
if_1:	beq $t3,1,in

	bnez $t1,in
	j endif_1
in:	li $t3,1

if:	rem $t3,$t2,4

	bnez $t3,endif
	li $a0,' '
	li $v0,print_char
	syscall
	
endif:addi $a0,$t1,0x30
	li $v0,print_char
	syscall
	
endif_1:sll $t0,$t0,1

	addi $t2,$t2,1
	j for
endfor:	jr $ra

#void main(void)
#{
# unsigned int value, bit, i;
#
# print_string("Introduza um numero: ");
# value = read_int();
# print_string("\nO valor em bin�rio e': ");
#for(i=0, flag=0; i < 32; i++)
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
# } 
#} 

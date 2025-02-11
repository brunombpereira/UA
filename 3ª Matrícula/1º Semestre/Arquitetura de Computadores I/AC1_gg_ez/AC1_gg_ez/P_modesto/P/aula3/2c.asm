#	MAPA DE REGISTOS
#	VALUE - $t0
#	BIT   - $t1
#	I     - $t2
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
for:	bge $t2,32,endfor

if:	rem $t3,$t2,4

	bnez $t3,endif
	li $a0,' '
	li $v0,print_char
	syscall
	
endif:	andi $t1,$t0,0x80000000

	srl $t1,$t1,31
	addi $a0,$t1,0x30
	li $v0,print_char
	syscall
		
	sll $t0,$t0,1

	addi $t2,$t2,1
	j for
endfor:	jr $ra

#void main(void)
#{
# unsigned int value, bit, i;
#
# print_string("Introduza um numero: ");
# value = read_int();
# print_string("\nO valor em binário e': ");
# for(i=0; i < 32; i++)
# {
#	if((i % 4) == 0) // resto da divisão inteira
#		print_char(' ');	
#	bit = (value & 0x80000000) >> 31;
# 	// ou, em alternativa: bit = (value >> 31) & 0x00000001;
# 	// ou, como value é do tipo unsigned: bit = value >> 31;
# 	print_char(0x30 + bit); // Ou: print_char('0' + bit); 
# 	value = value << 1; // shift left de 1 bit
#}
#} 

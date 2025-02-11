#void main(void)
#{
# unsigned int gray, bin, mask;
#
# print_string("Introduza um numero: ");
# gray = read_int();
# mask = gray >> 1;
# bin = gray;
# while(mask != 0)
# {
# bin = bin ^ mask;
# mask = mask >> 1;
# }
#
# print_string("\nValor em código Gray: ");
# print_int16(gray);
# print_string("\nValor em binario: ");
# print_int16(bin);
#} 

#	MAPA DE REGISTOS
#	$t0 - gray
#	$t1 - bin
#	$t2 - mask


##### NESTE PROGRAMA ELE ASSUME QUE O VALOR #####
##### COLOCADO E EM GRAY E DPS PASSA PARA BIN #####
	.data
str1:	.asciiz "Introduza um numero: "
str2:	.asciiz "\nO valor em gray e': "
str3:	.asciiz "\nO valor em binário e': "
	.eqv print_string,4
	.eqv read_int,5
	.eqv print_char,11
	.eqv print_int16,34
	.text
	.globl main

main:	la $a0, str1
	li $v0,4
	syscall # print_string("Introduza um numero: ");
	
	li $v0,5
	syscall #read_int()
	
	move $t0,$v0 # gray = read_int();
	
	srl $t2,$t0,1 #mask = gray >> 1;
	
	move $t1,$t0 #bin = gray;

while:	beq $t2,$0,endw
	
	xor $t1,$t1,$t2 #bin = bin ^ mask; 
	srl $t2,$t2,1 #mask = mask >> 1;

	j while

endw:	la $a0,str2
	li $v0,4
	syscall #print_string("\nValor em código Gray: ");
	
	move $a0,$t0
	li $v0,34
	syscall #print_int16(gray); 
	
	la $a0,str3
	li $v0,4
	syscall #print_string("\nValor em binario: ");
	
	move $a0,$t1
	li $v0,34
	syscall #print_int16(bin);
	
	jr $ra #fim do programa
	


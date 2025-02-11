#define SIZE 3
#void main(void)
#{
#	static char *array[SIZE]={"Array", "de", "ponteiros"};
# 	int i;
# 	for(i=0; i < SIZE; i++)
# 	{
# 		print_string(array[i]);
# 		print_char('\n');
# 	}
#} 
#		MAPA DE REGISTOS:
#	$t0-----------------------------&array[0]			 
#	$t1-----------------------------i
#	$t2-----------------------------&array[i]
#	$t3-----------------------------i*4

	.data
str1:	.asciiz "Array"
str2:	.asciiz "de"
str3:	.asciiz "ponteiros"
array:	.word str1, str2, str3
	.eqv SIZE,3
	.eqv print_string,4
	.eqv print_char,11
	.text
	.globl main
main:	la $t0,array

	li $t1,0
	
for:	bge $t1,SIZE,endf

	sll $t3,$t1,2
	addu $t2,$t0,$t3
	
	lw $a0,0($t2)
	li $v0,print_string
	syscall
	
	li $a0,'\n'
	li $v0,print_char
	syscall
	
	addiu $t1,$t1,1
	j for
	
endf:	jr $ra

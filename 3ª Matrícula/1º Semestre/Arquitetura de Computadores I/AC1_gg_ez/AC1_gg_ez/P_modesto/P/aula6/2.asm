##define SIZE 3
#void main(void)
#{
# 	static char *array[SIZE]={"Array", "de", "ponteiros"};
# 	char **p;
# 	char **pultimo;
# 	p = array;
# 	pultimo = array + SIZE;
# 	for(; p < pultimo; p++)
# 	{
# 		print_string(*p);
# 		print_char('\n');
# 	}
#} 
#		MAPA DE REGISTOS:
#	$t0-----------------------------p			 
#	$t1-----------------------------pultimo
	.data
str1:	.asciiz "Array"
str2:	.asciiz "de"
str3:	.asciiz "ponteiros"
array:	.word str1, str2, str3
	.eqv SIZE,3
	.eqv SIZE_4,12			#3*4
	.eqv print_string,4
	.eqv print_char,11
	.text
	.globl main
main:	la $t0,array

	addiu $t1,$t0,SIZE_4

for:	bge $t0,$t1,endf

	lw $a0,0($t0)
	li $v0,print_string
	syscall
	
	li $a0,'\n'
	li $v0,print_char
	syscall
	
	addiu $t0,$t0,4
	j for

endf:	jr $ra		

##define SIZE 5
#void main(void)
#{
# 	static int lista[SIZE]; // declara um array de inteiros
# 				// residente no segmento de dados
# 	static char str[]="\nIntroduza um numero: ";
# 	int i;
# 	for(i=0; i < SIZE; i++)
# 	{
# 		print_string(str);
# 		lista[i] = read_int();
# 	}
#} 
#	MAPA DE REGISTOS:
#	i 	  - 	$t0
#	&lista[0] - 	$t1
#	&lista[i] -	$t2
#	i*4	  -	$t3
	.data
lista:	.space 20
str:	.asciiz "\nIntroduza um numero: "
	.eqv SIZE,5
	.eqv read_int,5
	.eqv print_string,4
	.text
	.globl main
main:	li $t0,0
	li $t3,0
	
	la $t1,lista
for:	bge $t0,SIZE,endf
	
	
	la $a0,str
	li $v0,print_string
	syscall
	
	addu $t2,$t1,$t3
	li $v0,read_int
	syscall
	
	sw $v0,0($t2)
	addi $t0,$t0,1
	sll $t3,$t0,2
	j for
endf:	jr $ra
##define SIZE 4
#int array[4] = {7692, 23, 5, 234}; // Declara um array global de 4
# // posições e inicializa-o
#void main (void)
#{
#	int soma = 0;
#	int i = 0;
#	
#	while(i<SIZE)
#	{
#		soma=soma+array[i];
#		i++;
#	}
#	print_int10(soma);
#} 

#	MAPA DE REGISTOS:
#	&array[0] - 	$t0
#	&array[i] -	$t1
#	array[i]  -	$t2
#	soma	  -	$t3
#	i	  -	$t4
#	x	  - 	$t5

	.data
	.eqv print_int10,1
array:	.word 7692,23,5,234
	.eqv SIZE,4
	.text
	.globl main

main:	la $t0,array
	move $t1,$t0
	li $t3,0
	li $t4,0
	li $t5,0

while:	sll $t5,$t4,2 #x=i*4
	bge $t4,SIZE,endw
	
	addu $t1,$t0,$t5 #vir buscar &array[i]
	lw $t2,0($t1) #array[i]
	
	add $t3,$t3,$t2 #soma=soma+array[i];
	
	addi $t4,$t4,1 #i++
	
	j while

endw:	move $a0,$t3
	li $v0,1
	syscall #print_int10(soma);
	
	jr $ra #fim do prog

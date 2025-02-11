	#define SIZE 10
#void main(void)
#{
# 	static int lista[SIZE];
# 	int i, j, aux;
# 	print_string("\nInsira 10 numeros:\n");
#	for(i=0; i < SIZE;i++)
#	{
#		lista[i]=read_int();	
#	}
#
#
# 	for(i=0; i < SIZE-1; i++)
# 	{
# 		for(j = i+1; j < SIZE; j++)
# 		{
# 			if(lista[i] > lista[j])
# 			{
# 				aux = lista[i];
# 				lista[i] = lista[j];
# 				lista[j] = aux;
# 			}
# 		}
# 	}
# 	
#	// inserir aqui o código de impressão do conteúdo do array
#	for(i=0;i < SIZE;i++)
#	{
#		print_int10(lista[i]);
#		print_string("; ");
#	}
#} 
#		   MAPA DE REGISTOS:
#		&lista[0]  	-   $t0
#		i 		-   $t1
#	        i*4		-   $t2
#		&lista[i] 	-   $t3
#		j		-   $t4
#		j*4	        -   $t5
#		&lista[j]	-   $t6
#		lista[i]	-   $t7
#		lista[j]	-   $t8
	.data
lista:	.space 40
	.eqv SIZE, 10
	.eqv SIZE_1, 9
	.eqv SIZE_4, 40
	.eqv SIZE_1_4, 36
	.eqv print_string, 4
	.eqv print_int10, 1
	.eqv read_int, 5	
str1:	.asciiz "\nInsira 10 numeros:\n"
str2:	.asciiz "; "	
	.text
	.globl main
main:	la $a0,str1
	li $v0,print_string
	syscall
	
	li $t1,0		#i=0
	la $t0,lista		#$t0=&lista[0]

for1:	bge $t1,SIZE,endf1
	
	sll $t2,$t1,2		#i*4
	addu $t3,$t0,$t2	#&lista[i]
	
	li $v0,read_int
	syscall
	
	sw $v0,0($t3)
	
	addiu $t1,$t1,1
	j for1

endf1:	li $t1,0

for2:	bge $t1,SIZE_1,endf2

	sll $t2,$t1,2		#i*4
	addiu $t4,$t1,1		#j
	sll $t5,$t4,2		#j*4

	addu $t3,$t0,$t2	#&lista[i]
	
for3:	bge $t4,SIZE,endf3
	
	sll $t5,$t4,2
	addu $t6,$t0,$t5	#&lista[j]
	lw $t7,0($t3)		#lista[i]
	lw $t8,0($t6)		#lista[j]

if:	ble $t7,$t8,endif

	sw $t8,0($t3)
	sw $t7,0($t6)
	
endif:	addiu $t4,$t4,1		#j++
	
	j for3

endf3:	addiu $t1,$t1,1

	j for2

	
endf2:	li $t1,0	#i=0

for4:	bge $t1,SIZE,endf4

	sll $t2,$t1,2	#i*4
	addu $t3,$t0,$t2#&lista[i]
	
	lw $a0,0($t3)
	li $v0,print_int10
	syscall
	
	la $a0,str2
	li $v0,print_string
	syscall
	
	addiu $t1,$t1,1
	j for4
	
endf4:	jr $ra

##define SIZE 10
##define TRUE 1
##define FALSE 0
#void main(void)
	
#{
# 	static int lista[SIZE];
# 	int houveTroca, i, aux;
#	int* p;
# 					// inserir aqui o código para leitura de valores e
# 					// preenchimento do array
# 	print_string("\nInsira 10 numeros:\n");
#	for(p=lista;p<lista+SIZE;p++)
# 	{
#		*p=read_int();
# 	}
# 	do
# 	{
# 		houveTroca = FALSE;
# 		for (i=0; i < SIZE-1; i++)
# 		{
# 			if (lista[i] > lista[i+1])
# 			{
# 				aux = lista[i];
# 				lista[i] = lista[i+1];
# 				lista[i+1] = aux;
# 				houveTroca = TRUE;
# 			}
# 		}
# 	} while (houveTroca==TRUE);
# 					// inserir aqui o código de impressão do conteúdo do array
# 	print_string("Organizando por ordem crescente...\n");
#	for(i=0;i<SIZE;i++)
# 	{
# 		print_int10(lista[i]);
#		print_string("; ");
# 	}
#} 


# Mapa de registos
# SIZE - 1: $t3
# houve_troca: $t4
# i: $t5
# lista: $t6
# lista + i: $t7
	.data
	.eqv FALSE,0
	.eqv TRUE,1
	.eqv SIZE, 10
str1:	.asciiz "\nInsira 10 numeros:\n"
str1:	.asciiz "Organizando por ordem crescente...\n"
str1:	.asciiz ";\n"
	.text
	.globl main
main:	(...) # código para leitura de valores
	la $t6,lista #

do: # do {
	li $t4,FALSE # houve_troca = FALSE;
	li $t5,0 # i = 0;

for:	bge $t5,... # while(i < SIZE-1){

if:	sll $t7,... # $t7 = i * 4
	addu $t7,$t7,... # $t7 = &lista[i]
	lw $t8,0(...) # $t8 = lista[i]
	lw $t9,4(...) # $t9 = lista[i+1]
	b?? ...,...,endif # if(lista[i] > lista[i+1]){
	sw $t8,4(...) # lista[i+1] = $t8
	sw $t9,0(...) # lista[i] = $t9
	li $t4,TRUE #
 # }
endif:	(...) # i++;
	(...) ... # }
	(...) # } while(houve_troca == TRUE);
	(...) # codigo de impressao do
	# conteudo do array
	jr $ra # termina o programa 

##define SIZE 10
#void main(void)
#{
# 	static int lista[SIZE];
# 	int houveTroca;
# 	int aux;
# 	int *p, *pUltimo;
# 				// inserir aqui o código para leitura de valores e
# 				// preenchimento do array
# 	pUltimo = lista + (SIZE - 1);
# 	print_string("\nInsira 10 numeros:\n");
#	for(p=lista;p<lista+SIZE;p++)
# 	{
#		*p=read_int();
# 	}
# 	do
# 	{
# 		houveTroca = FALSE;
# 		for (p = lista; p < pUltimo; p++)
# 		{
# 			if (*p > *(p+1))
# 			{
# 				aux = *p;
# 				*p = *(p+1);
# 				*(p+1) = aux;
# 				houveTroca = TRUE;
# 			}
# 		}
# 	} while (houveTroca==TRUE);
# 				// inserir aqui o código de impressão do conteúdo do array
# 	print_string("Organizando por ordem crescente...\n");
#	for(p=lista;p<pUltimo;p++)
# 	{
# 		print_int10(*p);
#		print_string("; ");
# 	}
#} 
#}
#		   MAPA DE REGISTOS:
#		p  		-   $t0
#		*p 		-   $t1
#	        houveTroca      -   $t2
#		aux 		-   $t3
#		pUltimo		-   $t4
#		*pUltimo	-   $t5
#		*(p++)		-   $t6
	.data
lista:	.space 40
	.eqv FALSE,0
	.eqv TRUE,1
	.eqv SIZE,10
	.eqv SIZE_4,40
	.eqv SIZE_4_1,36
	.eqv read_int,5
	.eqv print_string,4
	.eqv print_int10,1
str:	.asciiz "\nInsira 10 numeros:\n"
str1:	.asciiz "Organizando por ordem crescente...\n"
str2:	.asciiz "; "
	.text
	.globl main 

main:	la $t0,lista			#p = static int lista[SIZE];

	addiu $t4,$t0,SIZE_4_1		#pUltimo = lista + (SIZE - 1);
	
	la $a0,str
	li $v0,print_string
	syscall

	addiu $t3,$t0,SIZE_4
	
for1:	bgeu $t0,$t3,do
	
	li $v0,read_int
	syscall
	
	sw $v0,0($t0)
	addiu $t0,$t0,4
	j for1	

do:	li $t2,FALSE
	
	la $t0,lista
	
for2:	bgeu $t0,$t4,while
	
	lw $t1,0($t0)		#*p
	lw $t6,4($t0)		#*(p+1)

if:	ble $t1,$t6,endif

	sw $t6,0($t0)
	sw $t1,4($t0)
	li $t2,TRUE		
	
endif:	addiu $t0,$t0,4

	j for2

while:	beq $t2,TRUE,do

	la $a0,str1
	li $v0,print_string
	syscall

	la $t0,lista

for3:	bgeu $t0,$t4,endf

	lw $a0,0($t0)
	li $v0,print_int10
	syscall
	
	la $a0,str2
	li $v0,print_string
	syscall
	
	addiu $t0,$t0,4
	j for3

endf:	jr $ra	

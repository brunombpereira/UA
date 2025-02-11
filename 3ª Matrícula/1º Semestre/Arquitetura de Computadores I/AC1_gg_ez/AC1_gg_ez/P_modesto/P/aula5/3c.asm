##define SIZE 10
##define TRUE 1
##define FALSE 0
#void main(void)
#{
# 	static unsigned int lista[SIZE];
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
# 		for (i=0; i <= SIZE-1; i++)
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

#		   MAPA DE REGISTOS:
#		&lista[0] e p  -   $t0
#		&lista[i] e *p -   $t1
#	        lista[i+1]     -   $t2
#		i e lista+SIZE -   $t3
#		i*4	       -   $t4
#		houve troca    -   $t5
#		aux	       -   $t6
	.data
lista:	.space 40
str:	.asciiz "\nInsira 10 numeros:\n"
str1:	.asciiz "; "
str2:	.asciiz "Organizando por ordem crescente...\n"
	.eqv read_int,5
	.eqv print_string,4
	.eqv print_int10,1
	.eqv SIZE_4,40	
	.eqv SIZE,10	
	.eqv SIZE_1,9
	.eqv TRUE,1
	.eqv FALSE,0
	.text
	.globl main
main:	la $t0,lista 			#p=lista
	
	addiu $t3,$t0,SIZE_4		#lista+SIZE
	
	la $a0,str	
	li $v0,print_string		#print_string
	syscall
	
for:	bgeu $t0,$t3,endf		# p<lista+SIZE condiçao
	
	li $v0,read_int			#read_int
	syscall
	
	move $t1,$v0			#guarda o valor introduzido em $t1
	sw $t1,0($t0)			#mete na lista
	addiu $t0,$t0,4			#incrementa p proxima posiçao
	j for
endf:	subu $t0,$t0,44			#p voltar a posiçao inicial 
	
do:	li $t5,FALSE			#houvetroca=false

	li $t3,0			#i=0
for1:	sll $t4,$t3,2			#i*4
	bgtu $t3,SIZE_1,while		#condiçao i<SIZE-1
	addu $t1,$t0,$t4		#&lista[i]
	lw $t6,0($t1)			#lista[i]
	lw $t2,4($t1)			#lista[i+1]
if:	ble $t6,$t2,endif		#condiçao lista[i]>lista[i+1]

	move $t7,$t6			#aux=lista[i]
	sw $t2,0($t1)			#lista[i]=lista[i+1]
	sw $t7,4($t1)			#lista[i+1]=aux
	li $t5,TRUE			#houvetroca=TRUE
		
endif:	addi $t3,$t3,1			#i++

	j for1
while:	beq $t5,TRUE,do

	la $a0,str2
	li $v0,print_string
	syscall
	
	li $t3,0
	la $t0,lista
for2:	bge $t3,SIZE,endf2

	sll $t4,$t3,2
	addu $t1,$t0,$t4
	
	lw $a0,0($t1)
	li $v0,print_int10
	syscall
	
	la $a0,str1
	li $v0,print_string
	syscall
	
	addi $t3,$t3,1
	j for2
endf2:	jr $ra
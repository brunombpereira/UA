##define SIZE 10
#void main(void)
#{
#	static int lista[]={8, -4, 3, 5, 124, -15, 87, 9, 27, 15};
# 	int *p; // Declara um ponteiro para inteiro (reserva
# 		// espaço para o ponteiro, mas não o inicializa)
# 	print_string("\nConteudo do array:\n");
# 	for(p = lista; p < lista + SIZE; p++)
# 	{
# 		print_int10( *p ); 	// Imprime o conteúdo da posição do
# 					// array cujo endereço é "p"
# 		print_string("; ");
# 	}
#} 
#	MAPA DE REGISTOS:
#	p	  - 	$t0
#	lista+size- 	$t1
#	*p        -	$a0

	.data
lista:	.word 8, -4, 3, 5, 124, -15, 87, 9, 27, 15
str:	.asciiz "\nConteudo do array:\n"
str1:	.asciiz "; "
	.eqv print_string,4
	.eqv print_int10,1
	.text
	.globl main
main:	la $t0,lista
	addiu $t1,$t0,40	#SIZE=10 10*4=40
	
	la $a0,str
	li $v0,print_string
	syscall
for:	bge $t0,$t1,endf	#p>=lista+size
	
	lw $a0,0($t0)
	li $v0,print_int10
	syscall
	
	la $a0,str1
	li $v0,print_string
	syscall
	
	addiu $t0,$t0,4
	j for
endf:	jr $ra
	

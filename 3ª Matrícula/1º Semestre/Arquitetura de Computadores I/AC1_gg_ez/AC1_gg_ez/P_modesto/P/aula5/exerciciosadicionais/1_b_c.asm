##define SIZE 10
#void main(void)
#{
#	static int lista[SIZE];
#	int *p;
#	int *ps;
#	int aux;
#	print_string("\nInsira 10 numeros:\n");
#	for(p=lista;p<lista+SIZE;p++)
#	{
#		p=read_int();
#	}
#	for(p=lista;p<lista+SIZE-1;p++)
#	{
#		for(ps=p+1;ps<lista+SIZE;ps++)
#		{
#			if(*p>*ps)
#			{
#				aux=*p;
#				p=*ps;
#				ps=aux;
#			}
#		}
#	}
#	for(p=lista;p<lista+SIZE;p++)
#	{
#		print_int10(*p);
#		print_string("; ");
#	}
#		   MAPA DE REGISTOS:
#		p	  	-   $t0
#		*p		-   $t1
#	      ps		-   $t2
#		*ps	 	-   $t3
#		lista+SIZE	-   $t4
#		lista+(SIZE-1)- $t5
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
	
	la $t0,lista		#p=lista
	addiu $t4,$t0,SIZE_4	#lista+SIZE
	addiu $t5,$t0,SIZE_1_4  #lista+SIZE-1

for1:	bge $t0,$t4,endf1
	
	li $v0,read_int
	syscall
	
	sw $v0,0($t0)	#p=read_int()
	
	addiu $t0,$t0,4	#p++
	j for1

endf1:	la $t0,lista	#p=lista
	
for2:	bge $t0,$t5,endf2

	addiu $t2,$t0,4	#ps=p+4
	
for3:	bge $t2,$t4,endf3
	
	
	lw $t1,0($t0)		#*p
	lw $t3,0($t2)		#*ps

if:	ble $t1,$t3,endif	#*p>*ps

	sw $t3,0($t0)
	sw $t1,0($t2)
	
endif:	addiu $t2,$t2,4		#ps++
	
	j for3

endf3:	addiu $t0,$t0,4		#p++

	j for2
	
endf2:	la $t0,lista	#p=lista

for4:	bge $t0,$t4,endf4

	lw $a0,0($t0)
	li $v0,print_int10
	syscall
	
	la $a0,str2
	li $v0,print_string
	syscall
	
	addiu $t0,$t0,4
	j for4
	
endf4:	jr $ra

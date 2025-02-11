#int main(int argc, char *argv[])
#{
# 	int i;
# 	print_string("Nr. de parametros: ");
# 	print_int10(argc);
#	for(i=0; i < argc; i++)
#	{
# 		print_string("\nP");
# 		print_int(i);
# 		print_string(": ");
# 		print_string(argv[i]);
# 	}
# 	return 0;
#} 
#		MAPA DE REGISTOS:
#	$t0-----------------------------argc			 
#	$t1-----------------------------&argv[0]
#	$t2-----------------------------i
#	$t3-----------------------------i*4
#	$t4-----------------------------&argv[i]

	.data
	.eqv print_string,4
	.eqv print_int10,1

str1:	.asciiz "Nr. de parametros: "
str2:	.asciiz "\nP"
str3:	.asciiz ": "
	.text
	.globl main
main:	move $t0,$a0
	move $t1,$a1
	
	la $a0,str1
	li $v0,print_string
	syscall
	
	move $a0,$t0
	li $v0,print_int10
	syscall
	
	li $t2,0		#i=0;

for:	bge $t2,$t0,endf

	la $a0,str2
	li $v0,print_string
	syscall
	
	move $a0,$t2
	li $v0,print_int10
	syscall
	
	la $a0,str3
	li $v0,print_string
	syscall
	
	sll $t3,$t2,2		#i*4
	addu $t4,$t1,$t3	#&argv[i]
	
	lw $a0,0($t4)
	li $v0,print_string
	syscall

	addiu $t2,$t2,1
	j for

endf:	li $v0,0		#return 0;	
	jr $ra
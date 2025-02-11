##define SIZE 3
#void main(void)
#{
#	 static char *array[SIZE]={"Array", "de", "ponteiros"};
# 	int i, j;
# 	for(i=0; i < SIZE; i++)
# 	{
# 		print_string( "\nString #" );
# 		print_string( ": " );
# 		j = 0;
# 		while(array[i][j] != '\0')
# 		{
# 			print_char(array[i][j]);
# 			print_char('-');
# 			j++;
# 		}
# 	}
#} 
#		MAPA DE REGISTOS:
#	$t0-----------------------------&array[0]			 
#	$t1-----------------------------i
#	$t2-----------------------------j
#	$t3-----------------------------i*4
#	$t4-----------------------------&array[i]
#	$t5-----------------------------&array[i][0]
#	$t6-----------------------------&array[i][j]
	.data
str1:	.asciiz "Array"
str2:	.asciiz "de"
str3:	.asciiz "ponteiros"
array:	.word str1, str2, str3
str4:	.asciiz "\nString #"
str5:	.asciiz ": "
	.eqv SIZE,3
	.eqv print_char,11
	.eqv print_int10,1
	.eqv print_string,4
	.text
	.globl main
main:	la $t0, array		#$t0-&array[0]
	
	li $t1,0		#i=0

for:	bge $t1,SIZE,endf

	la $a0,str4		#print_string( "\nString #" );
	li $v0,print_string
	syscall
	
	move $a0,$t1
	li $v0,print_int10	#print_int10( i ); 
	syscall
	
	la $a0,str5
	li $v0,print_string	#print_string( ": " );
	syscall
	
	li $t2,0		#j=0;
	sll $t3,$t1,2		#i*4
	addu $t4,$t0,$t3	#&array[i]
	lw $t5,0($t4)		#&array[i][0]

while:	addu $t6,$t5,$t2
	lb $a0,0($t6)
	beq $a0,'\0',endw
	
	li $v0,print_char
	syscall
	
	li $a0,'-'
	li $v0,print_char
	syscall
	
	addiu $t2,$t2,1
	j while
	
endw:
	
	addiu $t1,$t1,1		#i++
	j for

endf:	
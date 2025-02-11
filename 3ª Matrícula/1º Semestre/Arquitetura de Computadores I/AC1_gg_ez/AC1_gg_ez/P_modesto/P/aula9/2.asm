#double f2c(double ft)
#{
# 	return (5.0 / 9.0 * (ft – 32.0));
#}
#int main (void)
#{
#	double ft;
#	print_string("Insira a temperatura em Fahrenheit: ");
#	ft = read_double();
#	ft = f2c(ft);
#	print_string("\nEm graus Celsius: ");
#	print_double(ft);
#	return 0;
#} 
	.data
f1:	.double 32.0
f2:	.double 9.0
f3:	.double 5.0
str1:	.asciiz "Insira a temperatura em Fahrenheit: "
str2:	.asciiz "\nEm graus Celsius: "
	.eqv read_double,7
	.eqv print_string,4
	.eqv print_double,3
	.text 
	.globl main

main:	addiu $sp,$sp,-4
	sw $ra,0($sp)	

	la $a0,str1
	li $v0,print_string
	syscall
	
	li $v0,read_double
	syscall
	
	mov.d $f12,$f0#ft
	
	jal f2c
	
	mov.d $f12,$f0	
	
	la $a0,str2
	li $v0,print_string
	syscall

	li $v0,print_double
	syscall	
	
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	jr $ra
	
f2c:	l.d $f2,f1#32.0
	sub.d $f12,$f12,$f2
	l.d $f2,f2#9.0
	l.d $f4,f3#5.0
	div.d $f4,$f4,$f2
	mul.d $f0,$f4,$f12
	jr $ra
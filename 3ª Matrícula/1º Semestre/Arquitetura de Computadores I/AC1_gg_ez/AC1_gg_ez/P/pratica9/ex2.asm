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

#f2c function begin
#double f2c(double ft) -> ft:$f12 pq e parametro de entrada da funçao
f2c:	
	la $t0,f1
	l.d $f4,0($t0)
	sub.d $f12,$f12,$f4 #ft-32.0
	
	la $t1,f2
	l.d $f6,0($t1) #$f6=9.0
	
	la $t2,f3
	l.d $f8,0($t2) #$f8=5.0
	
	div.d $f10,$f8,$f6 #$f10=5.0/9.0
	mul.d $f0,$f10,$f12 #guardar no $f0 para ter o return
	
	jr $ra
#f2c function end


#main function begin
main:	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	la $a0,str1
	li $v0,print_string
	syscall
	
	li $v0,read_double
	syscall
	
	mov.d $f12,$f0
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
#main function end
#double sqrt(double val)
#{
# 	double aux, xn = 1.0;
# 	int i = 0;
# 	if(val > 0.0)
# 	{
# 		do
# 		{
# 			aux = xn;
# 			xn = 0.5 * (xn + val/xn);
# 		} while((aux != xn) && (++i < 25));
# 	} else
# 		xn = 0.0;
# 	return xn;
#} 
#int main (void)
#{
#	val=read_double();
#	result=sqrt(val);
#	print_double(result);
#}
	.data
d1:	.double 1.0
d2:	.double 0.5
d3:	.double 0.0
	.eqv print_double,3
	.eqv read_double,7
	.text
	.globl main
	
#####sqrt function begin
sqrt:	l.d $f0,d1
	li $t0,0
	
	l.d $f6,d3

if:	c.le.d $f12,$f6
	bc1t else
	
do:	mov.d $f2,$f0

	l.d $f4,d2
	div.d $f0,$f12,$f0
	add.d $f0,$f0,$f2
	mul.d $f0,$f0,$f4
	
	c.eq.d $f2,$f0
	bc1t endw
	addi $t0,$t0,1
	blt $t0,25,do

endw:	j endif

else:	l.d $f0,d3
		
endif:	jr $ra
#####sqrt function end

#####main begin
main:	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	li $v0,read_double
	syscall
	
	mov.d $f12,$f0
	jal sqrt
	
	mov.d $f12,$f0
	li $v0,print_double
	syscall
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	jr $ra
#####main end
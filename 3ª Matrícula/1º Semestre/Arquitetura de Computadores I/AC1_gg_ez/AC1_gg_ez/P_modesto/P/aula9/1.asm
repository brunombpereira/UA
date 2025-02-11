#int main(void)
#{
# 	float res;
# 	int val;
# 	do
# 	{
# 		val = read_int();
# 		res = (float)val * 2.59375;
# 		print_float( res );
# 	} while(res != 0.0);
# 	return 0;
#} 
	.data 
f1:	.float 2.59375
f2:	.float 0.0
	.eqv read_int,5
	.eqv print_float,2
	.text
	.globl main

main:	l.s $f4,f1	#guardar o float
	l.s $f6,f2	#guardar o 0.0

do:	li $v0,read_int
	syscall
	
	move $t0,$v0
	mtc1 $t0,$f2	#passar para float
	cvt.s.w $f2,$f2
	
	mul.s $f12,$f2,$f4	#res no $f12 p entrar ja na syscall
	
	li $v0,print_float
	syscall
	
	 c.eq.s $f12,$f6
	 bc1f do
	
	li $v0,0
	
	jr $ra
	
	
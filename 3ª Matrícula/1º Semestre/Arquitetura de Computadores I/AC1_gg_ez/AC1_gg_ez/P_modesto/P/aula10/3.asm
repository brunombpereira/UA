#double var(double *array, int nval)
#{
# 	int i;
# 	float media, soma;
# 	media = (float)average(array, nval);
# 	for(i=0, soma=0.0; i < nval; i++)
# 		soma += xtoy((float)array[i] - media, 2);
# 	return (double)soma / (double)nval;
#}
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
#float xtoy(float x, int y)
#{
# 	int i;
# 	float result;
# 	for(i=0, result=1.0; i < abs(y); i++)
# 	{
# 		if(y > 0)
# 			result *= x;
# 		else
# 			result /= x;
# 	}
# 	return result;
#}
#int abs(int val)
#{
# 	if(val < 0)
# 		val = -val;
# 	return val;
#} 
#double stdev(double *array, int nval)
#{
# 	return sqrt( var(array, nval) );
#}
#double average(double *array, int n)
#{
# 	int i = n;
# 	double sum = 0.0;
# 	for(; i > 0; i--)
# 	{
# 		sum += array[i-1];
# 	}
# 	return sum / (double)n;
#}
 
	.data
d1:	.double 1.0
d2:	.double 0.5
d3:	.double 0.0
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
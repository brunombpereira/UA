#double max(double *p, unsigned int n)
#{
# 	double max;
# 	double *u = p+n–1;
#
# 	max = *p++;
# 	for(; p <= u; p++)
# 	{
# 		if(*p > max)
# 		max = *p;
# 	}
# 	return max;
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
#A seguinte função main() serve para teste da função average().
##define SIZE 10
#int main(void)
#{
# 	static double a[SIZE];
# 	int i;
# 	for(i = 0; i < SIZE; i++)
# 	{
# 		a[i] = (double)read_int();
# 	}
#	print_double (max(a,SIZE))
# 	print_double( average(a, SIZE) );
# 	return 0;
#} 
	.data
array:	.space,80
	.eqv SIZE,10
	.eqv SIZE_8,80
	.eqv read_int,5
	.eqv print_double,3
	.text
	.globl main
#####average function begin
average:move $t0,$a1		#i=n
	
	li $t5,0
	mtc1 $t5,$f2		#passar para double
	cvt.d.w $f2,$f2		#double sum é agr $f2=0.0
	
for1:	blez $t0,endf1

	addiu $t1,$t0,-1	#i-1
	sll $t1,$t1,3		#(i-1)*8
	addu $t2,$a0,$t1	#&a[i-1]
	l.d $f4,0($t2)
	add.d $f2,$f2,$f4
	addiu $t0,$t0,-1
	
	j for1
	
endf1:	mtc1.d $a1,$f6#meti t0
	cvt.d.w $f6,$f6		#double n
	div.d $f0,$f2,$f6
	jr $ra
#####average function end

#####max function begin
max:	addu $t0,$a0,$a1
	addiu $t0,$t0,-1		#u
	
	l.d $f0,0($a0)			#max
	addiu $a0,$a0,8			#p++

fore:	bgt $a0,$t0,endfe

ife:	l.d $f2,0($a0)			#*p
	c.le.d $f2,$f0
	bc1t endife
	
	mov.d $f0,$f2

endife: addiu $a0,$a0,8			#p++
	
	j fore
	
endfe:	jr $ra
#####max function end

#####main function begin
main:	addiu $sp,$sp,-8
	sw $ra,0($sp)
	sw $s0,4($sp)

	
	la $a0,array		#&array[0]
	li $t0,0		#i=0

for:	bge $t0,SIZE,endf
	
	sll $t1,$t0,3		#i*4
	addu $t2,$t1,$a0	#&array[i]
	
	li $v0,read_int
	syscall
	
	mtc1.d $v0,$f2
	cvt.d.w $f2,$f2		#double read_int()
	s.d $f2,0($t2)		#a[i]=(double)read_int()
	
	addiu $t0,$t0,1		#i++
	j for

endf:	li $a1,SIZE_8
	
	move $s0,$a0
	
	jal max
	
	mov.d $f12,$f0
	li $v0,print_double
	syscall
	
	move $a0,$s0
	li $a1,SIZE
	
	jal average
	
	mov.d $f12,$f0
	li $v0,print_double
	syscall
	
	li $v0,0

	lw $ra,0($sp)
	lw $s0,4($sp)
	addiu $sp,$sp,8
	jr $ra
#####main function begin
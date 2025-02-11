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
#int main(void)
#{
#	x=read_float();
#	y=read_int();
#	result=xtoy(x,y);
#	print_float(result);
#	return 0;
#}
	.data
result:	.float 1.0
	.eqv read_float,6
	.eqv print_float,2
	.eqv read_int,5
	.text
	.globl main
	
#####abs function begin
abss:	move $v0,$a0
	
	bgez $v0,end
	mul $v0,$v0,-1

end:	jr $ra
#####abs function end

#####xtoy function begin
xtoy:	addiu $sp,$sp,-20
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	s.s $f20,12($sp)
	s.s $f22,16($sp)
	
	mov.s $f20,$f12
	move $s0,$a0
	li $s1,0
	la $t0,result
	l.s $f22,0($t0)
	
xtoy_for:
	move $a0,$s0
	jal abss
	
	bge $s1,$v0,xtoy_endf
	blez $s0, xtoy_else
	
	mul.s $f22,$f22,$f20
	j xtoy_endif
	
xtoy_else:
	div.s $f22,$f22,$f20

xtoy_endif:
	addi $s1,$s1,1
	j xtoy_for

xtoy_endf:	
	mov.s $f0,$f22

	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	l.s $f20,12($sp)
	l.s $f22,16($sp)
	addiu $sp,$sp,20
	jr $ra
#####xtoy function end

#####main begin
main:	addiu $sp,$sp,-12
	sw $ra,0($sp)
	sw $s0,4($sp)
	s.s $f20,8($sp)
	
	li $v0,read_float
	syscall
	
	mov.s $f20,$f0
	
	li $v0,read_int
	syscall
	
	move $s0,$v0
	
	move $a0,$s0
	mov.s $f12,$f20
	jal xtoy
	
	mov.s $f12,$f0
	li $v0,print_float
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	l.s $f20,8($sp)
	addiu $sp,$sp,12
	jr $ra
#####main end

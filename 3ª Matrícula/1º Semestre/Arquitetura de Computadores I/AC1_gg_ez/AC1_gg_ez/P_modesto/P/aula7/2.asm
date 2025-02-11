#void exchange(char *c1, char *c2)
#{
#	char aux = *c1;
# 	*c1 = *c2;
# 	*c2 = aux;
#} 
#char *strrev(char *str)
#{
# 	char *p1 = str;
# 	char *p2 = str;
#
# 	while(*p2 != '\0')
# 		p2++;
# 	p2--;
# 	while( p1 < p2 )
# 	{
# 		exchange(p1, p2);
# 		p1++;
# 		p2--;
# 	}
# 	return str;
#} 
#int main(void)
#{
# 	static char str[]="ITED - orievA ed edadisrevinU";
#
# 	print_string( strrev(str) );
# 	return 0;
#} 
#MAPA DE REGISTOS:
#str: $a0 $s0
#p1:$s1
#p2=$s2
	.data
str:	.asciiz "ITED - orievA ed edadisrevinU"
	.eqv print_string,4
	.text
	.globl main
	
#####main begin	
main:	addiu $sp,$sp,-4
	sw $ra,0($sp)

	la $a0,str

	jal strrev

	move $a0,$v0
	li $v0,print_string
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
#####main end

#####strrev function begin
strrev:	addiu $sp,$sp,-16
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	
	move $s0,$a0		#callee-saved
	move $s1,$a0		#p1=str
	move $s2,$a0		#p2=str
	
while1: lb $t0,0($s2)		#*p2
	beq $t0,'\0',endw1	#*p2 != '\0'
	addiu $s2,$s2,1	#p2++
	j while1
	
endw1:	addiu $s2,$s2,-1	#p2--

while2: bge $s1,$s2,endw2	#p1<p2

	lb $a0,0($s1)		
	lb $a1,0($s2)
	jal exc
	
	sb $a0,0($s1)
	sb $a1,0($s2)
	
	addiu $s1,$s1,1
	addiu $s2,$s2,-1

	j while2

endw2:	move $v0,$s0

	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	addiu $sp,$sp,16
	
	jr $ra
#####strrev function end	
	
#####exchange function begin
exc:	move $t0,$a0
	move $a0,$a1
	move $a1,$t0
	jr $ra
#####exchange function end

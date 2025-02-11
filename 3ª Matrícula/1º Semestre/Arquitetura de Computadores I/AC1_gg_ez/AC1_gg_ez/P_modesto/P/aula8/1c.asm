#void myexchange(char *c1, char *c2)
#{
#	char aux = *c1;
# 	*c1 = *c2;
# 	*c2 = aux;
#} 

#char *mystrrev(char *str)
#{
#	char *p1 = str;
# 	char *p2 = str;

# 	while(*p2 != '\0')
# 		p2++;
# 	p2--;
# 	while( p1 < p2 )
# 	{
# 		myexchange(p1, p2);
# 		p1++;
# 		p2--;
# 	} 	return str;
#} 

#unsigned int myatoi(char *s)
#{
#       s=mystrrev(s);
#	unsigned int digit, res = 0,expo=0;
# 	while( *s != '\0' )
# 	{
#		digit=1;
#		if(*s == '1')
#			if(expo==0)
#			{
#				digit = 1;
#			}
#			if(expo==1)
#			{
#				digit=2;
#			}
#			else
#			{
#				for(int i=0;i<expo;i++)
#				{
#					digit = digit*2;
#				}
#			}
#		}
#		if(*s=='0')
#		{
#			digit=0;
#		}
#		s++;
#		expo++;
# 		res = res + digit;
# 	}
# 	return res;
#} 

#int main(void)
#{
# 	static char str[]="101101";
# 	printf( "%d",myatoi(str) );
# 	return 0;
#} 
	.data
str:	.asciiz "101101"
	.eqv print_int10,1
	.text
	.globl main
#####strrev function begin
strrev:	addiu $sp,$sp,-16
	sw $ra,0($sp)
	sw $s3,4($sp)
	sw $s4,8($sp)
	sw $s5,12($sp)
	
	move $s3,$a0		#callee-saved
	move $s4,$a0		#p1=str
	move $s5,$a0		#p2=str
	
while1: lb $t0,0($s5)		#*p2
	beq $t0,'\0',endw1	#*p2 != '\0'
	addiu $s5,$s5,1	#p2++
	j while1
	
endw1:	addiu $s5,$s5,-1	#p2--

while2: bge $s4,$s5,endw2	#p1<p2

	lb $a0,0($s4)		
	lb $a1,0($s5)
	jal exc
	
	sb $a0,0($s4)
	sb $a1,0($s5)
	
	addiu $s4,$s4,1
	addiu $s5,$s5,-1

	j while2

endw2:	move $v0,$s3

	lw $ra,0($sp)
	lw $s3,4($sp)
	lw $s4,8($sp)
	lw $s5,12($sp)
	addiu $sp,$sp,16
	
	jr $ra
#####strrev function end	
	
#####exchange function begin
exc:	move $t0,$a0
	move $a0,$a1
	move $a1,$t0
	jr $ra
#####exchange function end

#####atoi function begin
atoi:	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	jal strrev
	move $a0,$v0
	
	li $t0,0		#res
	li $t1,0		#expo
	
while:	lb $t3,0($a0)
	beq $t3,'\0',endw
	
	li $t2,1		#digit

if1:	bne $t3,'1',if2

if1_1:	bne $t1,'0',if1_2
	
	li $t2,1		#digit
	
	j endif1_

if1_2:	bne $t1,'1',else1_3

	li $t2,2		#digit
	
	j endif1_
	
else1_3:li $t4,0		#i=0

for:	bge $t4,$t1,endif1_
	
	mul $t2,$t2,2
	addiu $t4,$t4,1
	
	j for

endif1_:j endif
		
if2:	bne $t3,'0',endif

	li $t2,0		#digit
	
endif:	addiu $a0,$a0,1
	addiu $t1,$t1,1
	addu $t0,$t0,$t2	

	j while

endw:	move $v0,$t0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
#####atoi function end

#####main begin
main:	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	la $a0,str
	jal atoi
	
	move $a0,$v0
	li $v0,print_int10
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4 
	jr $ra
#####main end
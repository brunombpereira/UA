#define MAX_STR_SIZE 33
#char toascii( char );
#char *strrev( char *);
#char *itoa(unsigned int n, unsigned int b, char *s)
#{
# 	char *p = s;
# 	char digit;
# 	do
# 	{
# 		digit = n % b;
# 		n = n / b;
# 		*p++ = toascii( digit );
# 	} while( n > 0 );
# 	*p = '\0';
# 	strrev( s );
# 	return s;
#}
#// Converte o digito "v" para o respetivo código ASCII
#char toascii(char v)
#{
# 	v += '0';
# 	if( v > '9' )
# 		v += 7; // 'A' - '9' - 1
# 	return v;
#} 
#void exchange(char *c1, char *c2)
#{
#	char aux = *c1;
# 	*c1 = *c2;
# 	*c2 = aux;
#} 
#char *strrev(char *str)
#{
#	char *p1 = str;
# 	char *p2 = str;
#
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
#int main(void)
#{
# 	static char str[MAX_STR_SIZE];
# 	int val;
# 	do {
# 		val = read_int();
# 		print_string( itoa(val, 2, str) );
# 		print_string( itoa(val, 8, str) );
# 		print_string( itoa(val, 16, str) );
# 	} while(val != 0);
# 	return 0;
#} 
	.data
	.eqv MAX_STR_SIZE,33
str:	.space MAX_STR_SIZE
	.eqv read_int,5
	.eqv print_string,4
	.eqv print_char,11
	.text
	.globl main
#####strrev function begin
strrev:	move $t3,$a0		#callee-saved
	move $t4,$a0		#p1=str
	move $t5,$a0		#p2=str
	
while1: lb $t0,0($t5)		#*p2
	beq $t0,'\0',endw1	#*p2 != '\0'
	addiu $t5,$t5,1	#p2++
	j while1
	
endw1:	addiu $t5,$t5,-1	#p2--

while2: bge $t4,$t5,endw2	#p1<p2

	lb $a0,0($t4)		
	lb $a1,0($t5)
	
	move $t0,$a0
	move $a0,$a1
	move $a1,$t0
	
	sb $a0,0($t4)
	sb $a1,0($t5)
	
	addiu $t4,$t4,1
	addiu $t5,$t5,-1

	j while2

endw2:	move $v0,$t3
	
	jr $ra
#####strrev function end	

#####toascii function begin
toascii:addiu $a0,$a0,'0'

ifz:	ble $a0,'9',endifz

	addiu $a0,$a0,7
	
endifz:	move $v0,$a0
	
	jr $ra
#####toascii function end

#####itoa function begin
itoa:	addiu $sp,$sp,-24
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	sw $s6,16($sp)
	sw $s7,20($sp)
	
	move $s2,$a2	#s na stack
	move $s6,$a2	#ponteiro
	move $s0,$a0	#n
	move $s1,$a1	#b
			#$s7 digit
doz:	remu $s7,$s0,$s1

	divu $s0,$s0,$s1
	
	move $a0,$s7
	jal toascii
	
	sb $v0,0($s6)
	addiu $s6,$s6,1
	
	bgtz $s0,doz
	
	li $t0,'\0'
	sb $t0,0($s6)
	
	move $a0,$s2
	jal strrev 
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	lw $s6,16($sp)
	lw $s7,20($sp)
	addiu $sp,$sp,24
	jr $ra
#####itoa function end

#####main begin
main:	addiu $sp,$sp,-12
	sw $ra,0($sp)
	sw $s3,4($sp)
	sw $s4,8($sp)
	
	la $s3,str
	
dox:	li $v0,read_int
	syscall
	
	move $s4,$v0	#val
	
	move $a0,$s4
	li $a1,2
	move $a2,$s3
	jal itoa
	
	move $a0,$v0
	li $v0,print_string
	syscall
	
	li $a0,'\n'
	li $v0,print_char
	syscall 
	
	move $a0,$s4
	li $a1,8
	move $a2,$s3
	jal itoa
	
	move $a0,$v0
	li $v0,print_string
	syscall 
	
	li $a0,'\n'
	li $v0,print_char
	syscall
	
	move $a0,$s4
	li $a1,16
	move $a2,$s3
	jal itoa
	
	move $a0,$v0
	li $v0,print_string
	syscall 	
	
	bnez $s4,dox
	
	li $v0,0
	
	lw $ra,0($sp)
	lw $s3,4($sp)
	lw $s4,8($sp)
	addiu $sp,$sp,12
	jr $ra
#####main end
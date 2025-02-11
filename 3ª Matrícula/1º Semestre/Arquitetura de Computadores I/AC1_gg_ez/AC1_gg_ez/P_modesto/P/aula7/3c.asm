#define STR_MAX_SIZE 30

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

#int strlen(char *s)
#{
# 	int len=0;
# 	while(*s++ != '\0')
# 		len++;
# 	return len;
#}

#char *strcpy(char *dst, char *src)
#{
# 	char *p=dst;
# 	
#	do
# 	{
# 		*p++ = *src;
# 	} while(*src++ != '\0');
# 	
#	return dst;
#}

#int main(void)
#{
# 	static char str1[]="I serodatupmoC ed arutetiuqrA";
# 	static char str2[STR_MAX_SIZE + 1];
# 	int exit_value;
# 	if(strlen(str1) <= STR_MAX_SIZE) {
# 		strcpy(str2, str1);
# 		print_string(str2);
# 		print_string("\n");
# 		print_string(strrev(str2));
# 		exit_value = 0;
# 	} 
#	else {
# 		print_string("String too long: ");
# 		print_int10(strlen(str1));
# 		exit_value = -1;
# 	}
# 	return exit_value;
#}
	.data
str1:	.asciiz "I serodatupmoC ed arutetiuqrA"
str2:	.space 31
str3:	.asciiz "String too long: "
	.eqv STR_MAX_SIZE,30
	.eqv print_string,4
	.eqv print_int10,1
	.text
	.globl main
	
#####strcpy function begin
strcpy:	move $t0,$a0		#char *p=dst

do:	lb $t1,0($a1)		#*src
	
	sb $t1,0($t0)
	addiu $t0,$t0,1
				#p++
	addiu $a1,$a1,1
	
while:	bne $t1,'\0',do		#src[i]!='\0'

	move $v0,$a0		#return dst
	
	jr $ra
#####strcpy function end

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

while2: bgeu $s1,$s2,endw2	#p1<p2

	move $a0,$s1		
	move $a1,$s2
	jal exchange
	
	addiu $s1,$s1,1
	addiu $s2,$s2,-1

	j while2

endw2:	move $v0,$s0

	lw $ra,0($sp)
	lw $s3,4($sp)
	lw $s4,8($sp)
	lw $s5,12($sp)
	addiu $sp,$sp,16
	jr $ra
#####strrev function end	
	
#####exchange function begin
exchange:
	lb $t0,0($a0)
	lb $t1,0($a1)
	sb $t0,0($a1)
	sb $t1,0($a0)
	jr $ra
#####exchange function end


#####strlen function begin
strlen:	li $v0,0

whilz:	lb $t0,0($a0)
	addiu $a0,$a0,1
	beq $t0,'\0',endw
	addi $v0,$v0,1
	j whilz
	
endw:	jr $ra
#####strlen function end

#####main begin
main:	addiu $sp,$sp,-4
	sw $ra,0($sp)
		
	la $a0,str1
	jal strlen
	
if:	bgt $v0,STR_MAX_SIZE,else

	la $a0,str2
	la $a1,str1
	jal strcpy
	
	la $a0,str2
	li $v0,print_string
	syscall
	
	li $a0,'\n'
	li $v0,11
	syscall
	
	la $a0,str2
	jal strrev 
	
	move $a0,$v0
	li $v0,print_string
	syscall
	
	li $v0,0
	j endif
	
else:	la $a0,str3
	li $v0,print_string
	syscall
	
	la $a0,str1
	jal strlen
	
	move $a0,$v0
	li $v0,print_int10
	syscall
	
	li $v0,-1

endif:	lw $ra,0($sp)
	addiu $sp,$sp,4
	jr $ra
#####main end

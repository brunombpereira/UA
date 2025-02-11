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
#
#char *strcat(char *dst, char *src)
#{
# 	char *p = dst;
# 	while(*p != '\0')
# 		p++;
# 	strcpy(p, src);
# 	return dst;
#} 

#int main(void)
#{
# 	static char str1[]="Arquitetura de ";
# 	static char str2[50];
# 	strcpy(str2, str1);
# 	print_string(str2);
# 	print_string("\n");
# 	print_string( strcat(str2, "Computadores I") );
# 	return 0;
#} 
	.data
str1:	.asciiz "Arquitetura de "
str2:	.space 50
str3:	.asciiz "\n"
str4:	.asciiz "Computadores I"
	.eqv print_string,4
	.text
	.globl main

#####strcpy function begin
strcpy:	move $t0,$a0		#char *p=dst

do:	lb $t1,0($a1)			#*src
	
	sb $t1,0($t0)
	addiu $t0,$t0,1		#p++
	addiu $a1,$a1,1
	
while:	bne $t1,'\0',do		#src[i]!='\0'

	move $v0,$a0		#return dst
	
	jr $ra
#####strcpy function end

#####strcatfunction begin
strcat:	addiu $sp,$sp,-8
	sw $ra,0($sp)
	sw $s0,4($sp)
	
	move $t0,$a0
	move $s0,$a0
	
w1:	lb $t1,0($t0)
	beq $t1,'\0',endw1
	
	addiu $t0,$t0,1
	j w1
	
endw1:	move $a0,$t0
	jal strcpy
	
	move $v0,$s0

	lw $ra,0($sp)
	lw $s0,4($sp)
	addiu $sp,$sp,8
	jr $ra
#####strcatfunction end

#####main begin
main:	addiu $sp,$sp,-8
	sw $ra,0($sp)
	sw $s0,4($sp)
	
	la $s0,str2
	move $a0,$s0
	la $a1,str1
	jal strcpy
	
	move $a0,$s0
	li $v0,print_string
	syscall
	
	la $a0,str3
	li $v0,print_string
	syscall
	
	move $a0,$s0
	la $a1,str4
	
	jal strcat
	
	move $a0,$v0
	li $v0,print_string
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	addiu $sp,$sp,8
	jr $ra
#####main end

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
# 	int i=0;
# 	
#	do
# 	{
# 		dst[i] = src[i];
# 	} while(src[i++] != '\0');
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
strcpy:	li $t0,0		#i=0

do:	addu $t2,$a1,$t0	#&src[i]
	addu $t3,$a0,$t0	#&dst[i]
	
	lb $t4,0($t2)		#src[i]
	sb $t4,0($t3)		#dst[i]=src[i]
	addiu $t0,$t0,1		#i++
	
while:	bne $t4,'\0',do		#src[i]!='\0'

	move $v0,$a0		#return dst
	
	jr $ra
#####strcpy function end

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


#####strlen function begin
strlen:	li $t1,0

whilz:	lb $t0,0($a0)
	addiu $a0,$a0,1
	beq $t0,'\0',endw
	addi $t1,$t1,1
	j whilz
endw:	move $v0,$t1
	jr $ra
#####strlen function end

#####main begin
main:	addiu $sp,$sp,-16
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	
	la $t1,str1
	la $t2,str2
	move $s1,$t1
	move $s2,$t2
	move $s0,$t0
	
	move $a0,$s1
	jal strlen
	
if:	bgt $v0,STR_MAX_SIZE,else

	move $a0,$s2
	move $a1,$s1
	jal strcpy
	
	move $s2,$v0
	
	move $a0,$s2
	li $v0,print_string
	syscall
	
	li $a0,'\n'
	li $v0,print_string
	syscall
	
	move $a0,$s2
	jal strrev 
	
	move $a0,$v0
	li $v0,print_string
	syscall
	
	li $s0,0

	j endif
	
else:	la $a0,str3
	li $v0,print_string
	syscall
	
	move $a0,$s1
	jal strlen
	
	move $a0,$v0
	li $v0,print_int10
	syscall
	
	li $s0,-1

endif:	move $v0,$s0
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	addiu $sp,$sp,16
	
	jr $ra
#####main end

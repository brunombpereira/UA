#int main(void)
#{
# 	static char str[]="2020 e 2024 sao anos bissextos";
# 	print_int10( atoi(str) );
# 	return 0;
#} 
#unsigned int atoi(char *s)
#{
#	unsigned int digit, res = 0;
# 	while( (*s >= '0') && (*s <= '9') )
# 	{
# 		digit = *s++ - '0';
# 		res = 10 * res + digit;
# 	}
# 	return res;
#} 
#Mapa de Registos
#res:$v0
#s:$a0
#*s:$t0
#digit:$t1
	.data
str:	.asciiz "2020 e 2024 sao anos bissextos"
	.eqv print_int10,1
	.text
	.globl main

atoi:	li $t2,0		#res=0

while:	lb $t0,0($a0)		#*s
	blt $t0,'0',endw
	bgt $t0,'9',endw

	sub $t1,$t0,'0'
	addiu $a0,$a0,1
	mul $t2,$t2,10
	add $t2,$t2,$t1
	
	j while
			
endw:	move $v0,$t2
	jr $ra

main:	addiu $sp,$sp,-8
	sw $ra,0($sp)
	sw $s0,4($sp)
	
	la $s0,str
	move $a0,$s0
	jal atoi
	
	move $a0,$v0
	li $v0,print_int10
	syscall
	
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	addiu $sp,$sp,8
	
	li $v0,0
	
	jr $ra

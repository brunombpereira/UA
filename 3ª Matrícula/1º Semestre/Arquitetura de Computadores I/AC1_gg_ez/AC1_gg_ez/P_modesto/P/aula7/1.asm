#int strlen(char *s)
#{
# 	int len=0;
# 	while(*s++ != '\0')
# 		len++;
# 	return len;
#}
#int main(void)
#{
# 	static char str[]="Arquitetura de Computadores I";
#
# 	print_int10(strlen(str));
# 	return 0;
#} 
#MAPA DE REGISTOS:
#$t0	-	*s
#$s0	-	len
#$a0	-	str
	.data
str:	.asciiz "Arquitetura de Computadores I"
	.eqv print_int10,1
	.text
	.globl main

strlen:	li $t1,0

while:	lb $t0,0($a0)
	addiu $a0,$a0,1
	beq $t0,'\0',endw
	addi $t1,$t1,1
	j while
endw:	move $v0,$t1
	jr $ra

main:	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	la $a0,str
	
	jal strlen

	move $a0,$v0
	li $v0,print_int10
	syscall
	
	lw $ra,0($sp)

	addiu $sp,$s0,4
	
	jr $ra

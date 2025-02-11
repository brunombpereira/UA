# O argumento da função é passado em $a0
# O resultado é devolvido em $v0
# Sub-rotina terminal: não devem ser usados registos $sx
	
	#int strlen(char *s)
	#len :  $v0
	#*s : $t0
	.eqv print_int10,1	
	.text
strlen:	li $t1,0 # len = 0;
while:	lb $t0,0($a0) # while(*s++ != '\0')
	addiu $a0,$a0,1 #*s++
	beq $t0,'\0',endw # {
	addi $t1,$t1,1 # len++;
	j while # }
endw:	 # return len (usamos o $v0 para o len
	#pq damos return do len;
	move $v0,$t1
	jr $ra #
	
	.data
str:	.asciiz "Arquitetura de Computadores I"
	.text
	.globl main
main:	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	la $a0,str
	jal strlen
	
	move $a0,$v0
	li $v0,print_int10
	syscall #print_int10(strlen(str));
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	li $v0,0 #return 0

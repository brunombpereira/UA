# Mapa de registos
# num: $t0
# p: $t1
# *p: $t2 (Registo temporário para guardar o valor armazenado na posição de memória p)
	.data
	.eqv SIZE,20
	.eqv read_string,8
	.eqv print_int10,1
str:	.space 21
	.text
	.globl main
main:	li $t0,0  # num = 0;
	
	la $a0,str
	li $a1,SIZE
	li $v0,8
	syscall #read_string(str, SIZE);
	
	la $t1,str # p = str ou &str[0];

while:	# while(*p != '\0')
	lb $t2,0($t1) #
	beq $t2,0,endw # {
	blt $t2,'0',endif # if(str[i] >='0' &&
	bgt $t2,'9',endif # str[i] <= '9')
	addi $t0,$t0,1 # num++;

endif:
	addiu $t1,$t1,1 # p++;
	
	j while # }

endw:	move $a0,$t0
	li $v0,1
	syscall # print_int10(num);
	
	jr $ra # termina o programa 

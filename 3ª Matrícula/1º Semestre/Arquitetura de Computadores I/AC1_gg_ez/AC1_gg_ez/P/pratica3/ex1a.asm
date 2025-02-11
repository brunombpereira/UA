# Mapa de registos:
# soma: $t0
# value: $t1
# i: $t2
	.data
str1:	.asciiz "Introduza um numero: "
str2:	.asciiz "Valor ignorado \n"
str3:	.asciiz "A soma dos positivos e: "
	.eqv print_string,4
	.eqv read_int,5
	.eqv print_int10,1
	.text
	.globl main
main:	li $t0,0 # soma = 0;
	li $t2,0 # i = 0;
	
for:	bge $t2,5,endfor # while(i < 5) {
 	
 	la $a0, str1
 	ori $v0,$0,print_string 
 	syscall	# print_string("Introduza um numero:");
 	
 	ori $v0,$0,read_int
 	syscall
 	or $t1,$v0,$0 # value=read_int();
 	
 	ble $t1,$0,else # if(value > 0)
 	add $t0,$t0,$t1 # soma += value;
 	j endif 
	
else: la $a0,str2 # else
 	      ori $v0,$0,print_string
 	      syscall # print_string("Valor ignorado \n");
endif: 	addi $t2,$t2,1 # i++;
 	j for # }
endfor:
 	la $a0,str3
 	ori $v0,$0,print_string
 	syscall # print_string("...");
 	
 	or $a0,$t0,$0
 	ori $v0,$0,1
 	syscall # print_int10(soma);
 	
 	jr $ra

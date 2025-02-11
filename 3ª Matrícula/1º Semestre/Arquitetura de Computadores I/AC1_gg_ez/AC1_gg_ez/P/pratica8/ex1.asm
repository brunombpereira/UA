#res:$v0
#s:$a0
#*s:$t0
#digit:$t1
#aux:$t2
		#falta alinea c
	.eqv print_int10,1
	.text
atoi:	li $t3,0 #res=0
while:	lb $t0,0($a0)#le *s
	blt $t0,'0',endw
	bgt $t0,'9',endw
	li $t2,'0'
	sub $t1,$t0,$t2 
	addiu $a0,$a0,1 #s++
	mul $t3,$t3,10 #res= 10*res
	add $t3,$t3,$t1
	j while
	
endw:	move $v0,$t3
	jr $ra

 	.data
str:	.asciiz "2020 e 2024 sao anos bissextos"
 	.text
 	.globl main
main:	addiu $sp,$sp,-8
 	sw $ra,0($sp)
 	
 	
 	la $a0,str
	jal atoi

 	move $a0,$v0
 	li $v0,print_int10
 	syscall #print_int10( atoi(str) );
 	
 	
 	lw $ra,0($sp)
 	addiu $sp,$sp,8
 	
 	li $v0,0 
 	
 	jr $ra #fim do prog

#mapa de registos
#$t0-i
#$t1-v
#$t2- &val[0]
#$t3-i*4
#$t4-&val[i]---> val[i]
#$t5 - SIZE/2
#$t6- #&val[i+SIZE/2]
#$t7- val[i+SIZE/2]
	.data
val:	.word 8,4,15,-1987,327,-9,27,16
str0:	.asciiz "Result is: "
	.eqv SIZE,8
	.eqv SIZE_4,32
	.eqv SIZE_2_4,16
	.eqv SIZE_2,4
	.eqv print_string,4
	.eqv print_int10,1
	.eqv print_char,5
	.text
	.globl main
main:
	li $t0,0 #i=0
	la $t2,val #$t2=&val[0]
do:
	sll $t3,$t0,2 #i*4
	addu $t4,$t3,$t2 #&val[i]
	lw $t1,0($t4) #v=val[i]
	
	li $t5, SIZE_2_4
	div $t5, $t5, 2 #SIZE/2
	addu $t6,$t5,$t4 #&val[i+SIZE/2]
	
	lw $t7,0($t6) #val[i+SIZE/2]
	
	sw $t7,0($t4) #val[i]=val[i+SIZE/2]
	sw $t1,0($t6) #val[i+SIZE/2]=v
	
	addiu $t0,$t0,1 #i++
while:
	bge $t0,SIZE_2,endw 
	
	j do
endw:
	la $a0,str0
	li $v0,4
	syscall #print_string(str0)

	li $t0,0 #i=0
	la $t2, val #&val[0]
do1:
	sll $t3,$t0,2 #i*4
	
	addu $t4,$t2,$t3 #&val[i]
	 
	lw $a0,0($t4)
	li $v0,1
	syscall #print_int(val[i++])
	
	addiu $t0,$t0,1 #i++

	li $a0, ','
	li $v0,11
	syscall #print_char(',')
while1:
	blt $t0,SIZE, do1
	jr $ra
	
	 

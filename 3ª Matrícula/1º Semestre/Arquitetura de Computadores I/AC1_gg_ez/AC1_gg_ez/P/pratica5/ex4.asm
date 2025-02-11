#	mapa de registos
#	p = $t0
#	*p = $t1
#	pultimo = $t2
#	*pultimo = $t3
#	lista + SIZE = $t4
#	houvetroca = $t5
#	*(p+1) = $t6
	.data
lista:	.space 40 #10*4
	.eqv FALSE,0
	.eqv TRUE,1
	.eqv print_int10,1
	.eqv print_string,4
	.eqv read_int,5
	.eqv SIZE,10
	.eqv SIZE_4,40 #size * 4 = 10 * 4, pq sao ints
	.eqv SIZE_4_1,36 #size - 1 = 40 - 4 = 36
str:	.asciiz "\nInsira 10 numeros:\n"
str1:	.asciiz "Organizando por ordem crescente...\n"
str2:	.asciiz ";"
	.text
	.globl main

main:	la $t0,lista #p=&lista[0]
	addiu $t2,$t0,SIZE_4_1 #pUltimo = lista + (SIZE - 1);
	
	la $a0,str
	li $v0,4
	syscall #print_string
	
	addiu $t4,$t0,SIZE_4 #lista + SIZE

for:	bgeu $t0,$t4,do
	
	li $v0,5
	syscall #read_int()
	
	sw $v0,0($t0) 
	
	 addiu $t0,$t0,4 #p++ 
	j for

do:	li $t5,FALSE
	la $t0,lista

for1:	bgeu $t0,$t2,while
	
	lw $t1,0($t0) #*p=$t1
	lw $t6,4($t0) #*(p+1)=$t6

if:	bleu $t1,$t6,endif
	
	sw $t6,0($t0) # aux = *p;
	sw $t1,4($t0) # *p = *(p+1); 
		      # *(p+1) = aux; 
	li $t5,TRUE
		      
endif:	addiu $t0,$t0,4 #p++
	
	j for1

while:	beq $t5,TRUE,do 
	
	la $a0,str1
	li $v0,4
	syscall

	la $t0,lista
	
for2:	bgeu $t0,$t2,endf2
	
	lw $t1,0($t0)		 
	move $a0,$t1
	li $v0,1
	syscall
	
	la $a0,str2
	li $v0,4
	syscall

	addiu $t0,$t0,4
	
	j for2


endf2:
	jr $ra








#		   MAPA DE REGISTOS:
#		&lista[0]  	-   $t0
#		i 		-   $t1
#	        i*4		-   $t2
#		&lista[i] 	-   $t3
#		j		-   $t4
#		j*4	        -   $t5
#		&lista[j]	-   $t6
#		lista[i]	-   $t7
#		lista[j]	-   $t8

	.data
lista:	.space 40 #SIZE*4
	.eqv SIZE,10
	.eqv SIZE_4,40
	.eqv SIZE_1,9
	.eqv SIZE_1_4, 36
	.eqv print_string, 4
	.eqv print_int10, 1
	.eqv read_int, 5	
str1:	.asciiz "\nInsira 10 numeros:\n"
str2:	.asciiz "; "	
	.text
	.globl main

main:	la $t0,lista #&lista[0]
	li $t1,0 #i=0
	la $a0,str1
	li $v0,4
	syscall #print_string("\nInsira 10 numeros:\n");
	
for: 	bge $t1,SIZE,endf #for(i=0; i < SIZE;i++)
	sll $t2,$t1,2 #i*4
	addu $t3,$t2,$t0 #&lista[i]
	
	li $v0,5
	syscall #read_int()
	
	sw $v0,0($t3) #lista[i]=read_int()
	
	addiu $t1,$t1,1 #i++
	
	j for

endf:	li $t1,0 #i=0

for1:	bge $t1,SIZE_1,endf1
	addiu $t4,$t1,1 #j=i+1
	sll $t2,$t1,2 #i*4
	#sll $t5,$t4,2 #j*4
	addu $t3,$t0,$t2 #&lista[i]

for2:	bge $t4,SIZE,endf2
	
	sll $t5,$t4,2 #j*4
	addu $t6,$t0,$t5 #&lista[j]
	lw $t7,0($t3)#lista[i]
	lw $t8,0($t6)#lista[j]

if:	ble $t7,$t8,endif
	
	sw $t8,0($t3) 
	sw $t7,0($t6)
	
endif:	addiu $t4,$t4,1 #j++
	j for2
	
endf2:	addiu $t1,$t1,1 #i++

	j for1
	
endf1:	li $t1,0 #i=0

for3:	bge $t1,SIZE,endf3

	sll $t2,$t1,2	#i*4
	addu $t3,$t0,$t2#&lista[i]
	
	lw $a0,0($t3)
	li $v0,print_int10
	syscall
	
	la $a0,str2
	li $v0,print_string
	syscall
	
	addiu $t1,$t1,1
	j for3
	
endf3:	jr $ra




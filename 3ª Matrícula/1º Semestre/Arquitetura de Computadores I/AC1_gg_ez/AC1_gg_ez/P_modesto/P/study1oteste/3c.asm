	.data
	.eqv SIZE,10
	.eqv SIZE_1,9
	.eqv SIZE_4,40
	.eqv TRUE,1
	.eqv FALSE,0
	.align 2
lista:	.space 40
	.eqv print_string,4
	.eqv read_int,5
	.eqv print_int10,1
str1:	.asciiz "\nInsira 10 numeros:\n"
str2:	.asciiz "Organizando por ordem crescente...\n"
str3:	.asciiz "; "
	.text
	.globl main
main:	la $a0,str1
	li $v0,print_string
	syscall
	
	la $t0,lista		#p=lista
	addiu $t1,$t0,SIZE_4	#lista+SIZE
	
for1:	bgeu $t0,$t1,endf1	

	li $v0,read_int
	syscall
	
	sw $v0,0($t0)
	
	addiu $t0,$t0,4
	j for1
	
endf1:	la $t0,lista		#&lista[0]

do:	li $t2,FALSE		#houve troca=false

	li $t3,0		#i=0

for2:	bgt $t3,SIZE_1,while	#i<=SIZE-1
	
	sll $t4,$t3,2		#i*4
	addu $t5,$t0,$t4	#&lista[i]
	lw $t6,0($t5)		#lista[i]]
	lw $t7,4($t5)		#lista[i+1]
	
if:	ble $t6,$t7,endif	#lista[i] > lista[i+1]

	sw $t7,0($t5)		#lista[i]=lista[i+1]
	sw $t6,4($t5)		#lista[i+1]=lista[i]
	li $t2,TRUE		#houvetroca=true
	
endif:addiu $t0,$t0,1		#i++
	
	j for2

while:	beq $t2,TRUE,do

	la $a0,str2
	li $v0,print_string
	syscall
	
	li $t3,0
	la $t0,lista

for3:	bge $t3,SIZE,endf3	
	sll $t4,$t3,2
	addu $t5,$t0,$t4
	
	lw $a0,0($t5)
	li $v0,print_int10
	syscall
	
	la $a0,str3
	li $v0,print_string
	syscall
	
	addiu $t3,$t3,1
	j for3
	
endf3:	jr $ra
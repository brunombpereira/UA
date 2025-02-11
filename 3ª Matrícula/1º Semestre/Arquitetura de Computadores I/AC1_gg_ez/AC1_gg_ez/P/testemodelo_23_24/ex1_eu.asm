#mapa de registos
#$t0-val
#$t1-n
#$t2-min
#$t3-max

	.data
str0:	.asciiz "Digite até 20 inteiros(zero para terminar): "
str1:	.asciiz "Máximo/minimo são: "
	.eqv print_char,11
	.eqv print_string,4
	.eqv print_int10,1
	.eqv read_int,5
	.text
	.globl main

main:	li $t1,0 #n=0
	li $t2,0x7FFFFFFF #min=0x7FFFFFFF
	li $t3,0x80000000 #max=0x80000000
	
	la $a0,str0
	li $v0,4
	syscall #print_string(...)
	
do:
	li $v0,5
	syscall #read_int()
	
	move $t0,$v0 #val = read_int()

if:	beq $t0,'0',endif

if1:	ble $t0,$t3,if2
	move $t3,$t0 #max=val

if2:	bge $t0,$t2,endif
	move $t2,$t0 #min=val
	
endif:	addiu $t1,$t1,1 #n++

while:	bge $t2,20,enddo
	bne $t0,0,do

enddo:	la $a0,str1
	li $v0,4
	syscall #print_string("Máximo/minimo são: ")
	
	move $a0,$t3
	li $v0,1
	syscall #print_int10(max)
	
	li $a0,':'
	li $v0,11
	syscall #print_char(:)
	
	move $a0,$t2
	li $v0,1
	syscall #print_int10(max)
	
	jr $ra
	

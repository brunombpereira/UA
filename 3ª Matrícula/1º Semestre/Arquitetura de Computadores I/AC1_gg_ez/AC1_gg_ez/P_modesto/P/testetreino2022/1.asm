# Mapa de registos
#val:$t0
#n:$t1
#min:$t2
#max:$t3
	.data
	.eqv print_string,4
	.eqv read_int,5
	.eqv print_char,11
	.eqv print_int10,1
str1:	.asciiz "Digite até 20 inteiros (zero para terminar):"
str2:	.asciiz "Máximo/mínimo são: "
	.text
	.globl main
main:	la $a0,str1
	li $v0,print_string
	syscall
	
	li $t2,0x7FFFFFFF	#min=$t2
	li $t3,0x80000000	#max=$t3
	li $t1,0
	
do:	li $v0,read_int
	syscall
	
	move $t0,$v0		#val=read_int()

if1:	beqz $t0,endif1		#val!=0

if2:	ble $t0,$t3,if3

	move $t3,$t0

if3:	bge $t0,$t2,endif1

	move $t2,$t0

endif1:	addiu $t1,$t1,1

while:	bge $t1,20,endw
	beqz $t0,endw

	j do

endw:	la $a0,str2
	li $v0,print_string
	syscall
	
	move $a0,$t3
	li $v0,print_int10
	syscall
	
	li $a0,':'
	li $v0,print_char
	syscall
	
	move $a0,$t2
	li $v0,print_int10
	syscall
	
	jr $ra
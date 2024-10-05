	.data
	.equ inkey, 1
	.equ up,1
	.equ down,0
	.equ putchar,3
	.equ printint,6
	.text
	.globl main
main:	li $t0,0			# state = 0
	li $t1,0			# cnt = 0
do:	li $a0, '\r'
	li $v0, putchar
	syscall
	
	li $t2,3				
	sll $t2,$t2,16
	ori $t2,$t2,10			# $t2 = 10 | 3<<16
	move $a0,$t1
	move $a1,$t2
	li $v0, printint
	syscall
	
	li $a0, '\t'
	li $v0, putchar
	syscall

	li $t3,8
	sll $t3,$t3,16
	ori $t3,$t3,2			# $t3 = 2 | 8<<16
	move $a0,$t1
	move $a0,$t3
	li $v0, printint		
	syscall

	li $a0,5
	jal wait
	
	li $v0,inkey
	syscall
	move $t4,$v0			# c = inkey()
if:	bne $t4,'+',if2
	la $t0,up
if2:	bne $t4,'-',if3
	la $t0,down
if3:	bne $t0,up,else
	addi $t1,$t1,1
	and $t1,$t1,0xFF
else:	addi $t1,$t1,-1
	and $t1,$t1,0xFF
while:	bne $t4,'q',do
	li $v0,0
	jr $ra



wait:	li $t9,0
	li $t7,515000
	mul $t8,$a0,$t7
for:	bge $t9,$t8,endf
	addi $t9,$t9,1
	j for
endf:	li $v0,0
	jr $ra	













#Mapa de registos
# f1: s0
# k: s1
# av: s2
#i: s3
# res: t0
	.data
	.eqv SIZE,15
str:	.asciiz "Invalid argc"
	.eqv print_string,4
	.eqv print_int10,1
	.text
func2:
	addiu $sp,$sp,-20
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	sw $s3,16($sp)
	
	move $s0,$a0	#f1
	move $s1,$a1	#k
	move $s2,$a2	#av
	
	
if:	blt $s1,2,else
	bgt $s1,SIZE,else
	li $s3,2		#i = 2
do:				
	sll $t1,$s3,2		#i*4
	add $t1,$s2,$t1		#&av[i]
	lw $a0,0($t1)		#av[i]  (parametro de entrada do toi)
	jal toi	
	sll $t1,$s3,2		#i*4	(podia poupar esta linha mas tinha de 
				#	mudar a linha 31)
	add $t1,$s0,$t1		#&f1[i]
	sw $v0,($t1)		#f1[i] = toi(av[i])
	addi $s3,$s3,1		#i++

while:	blt $s3,$s1,do

	move $a0,$s0
	move $a1,$s2
	jal avz
	move $t0,$v0		#res = avz(fl,k)
	li $v0,print_int10
	move $a0,$t0
	syscall			#print_int10
				
	j endif						
else:	li $v0,print_string
	la $a0,str	#print string
	syscall
	
	li $t0,-1	#res = -1
endif:	
	move $v0,$t0	#return res
		
	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	lw $s3,16($sp)
	addu $sp,$sp,20
	
	jr $ra
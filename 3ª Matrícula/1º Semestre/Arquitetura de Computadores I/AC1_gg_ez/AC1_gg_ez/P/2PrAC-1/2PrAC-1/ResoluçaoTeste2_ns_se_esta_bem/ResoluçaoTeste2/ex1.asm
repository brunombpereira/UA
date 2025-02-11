#mapa de registos
#argc-$a0--->$s0
#argv-$a1--->$s1
#i-$s2
#p-$s3
	.data
	.eqv SIZE,20
fla:	.space 80
str0:	.asciiz "Invalid argc"
	.eqv print_float,2
	.eqv print_string,4
	.text
	.globl print
print:
	addiu $sp,$sp,-20
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp) #i
	sw $s3,16($sp) #p
	
	move $s0,$a0#argc
	move $a1,$s1#char*argv[]
	
	la $s3,fla #fla
if:
	ble $s0,1,else
	bgt $s0,SIZE,else
	
	li $s2,0 #i=0
for:
	bge $s2,$s0,endf
	
	sll $t0,$s2,2 #i*4
	addu $t1,$s1,$t0 #&argv[i] 
	lw $t2,0($t1) #argv[i]
	
	move $a0,$t2 #argv[i]
	li $a1,10
	jal tof
	
	s.s $f0,0($s3)#*p=tof(argv[i],argc)
	
	addi $s2,$s2,1 #i++
	addi $s3,$s3,4 #p++
	j for
endf:
	la $a0,fla
	move $a1,$s0
	jal aver
	mov.s $f12,$f0
	li $v0,2
	syscall
	j endif
else:
	la $a0,str0
	li $v0,4
	syscall
endif:
	move $v0,$s3 #return fla em $v0, pq e um array
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	lw $s3,16($sp)
	addiu $sp,$sp, 20
	
	jr $ra
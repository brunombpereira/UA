#mapa de registos
#argc-$a0-->$s0
#argv-$a1-->$s1
#i-$s2
#p-$s3

	.data
	.eqv SIZE,20
fla:	.space 80 #size*4
	.eqv print_float,2
	.eqv print_string,4
	.text
	.globl print

print:	addiu $sp,$sp,-20
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	sw $s3,16($sp)
	
	move $s0,$a0 #agrc
	move $s1,$a1 #argv
	
	la $s3,fla #*p=fla

if:	ble $s0,1,else
	bgt $s0,SIZE,else
	li $s2,0 #i=0

for:	bge $s0,$s1,endf
	sll $t9,$s2,2 #i*4, apesar de ser char e um array de ponteiros
	addu $t0,$s0,$t9 #&agrv[i]
	lb $t1,0($t0) #agrv[i]
	
	move $a0,$t1 #passar argv[i] para parametro de entrada
	li $a1,10 #meter 10 como parametro de entrada
	jal tof
	
	s.s $f0,0($s3) #*p=tof(agrv[i],10)
	
	addiu $s2,$s2,1 #i++
	addiu $s3,$s3,4 #p++
	j for

endf:	move $a0,$s3 #fla parametro de entrada
	move $a1,$s0 #argc para de entrada
	jal aver
	
	mov.s $f12,$f0
	li $v0,print_float
	syscall
	
	j endif
	
else:	la $a0,str0
	li $v0,4
	syscall
	
	move $v0,$s3 #return fla
	
endif:	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	lw $s3,16($sp)	
	addiu $sp,$sp,-20
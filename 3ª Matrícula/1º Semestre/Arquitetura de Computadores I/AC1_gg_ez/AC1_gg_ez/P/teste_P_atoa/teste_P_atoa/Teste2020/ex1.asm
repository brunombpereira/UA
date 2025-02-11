#mapa de registos
#array-$a0--->$s0
#low-$a1---->$s1
#high-$a2---->$s2
#i- $s3
#npr-$s4--->$v0
#p-$s5
	.data
	.text
	.globl prime
prime:
	addiu $sp,$sp,-28
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	sw $s3,16($sp)
	sw $s4,20($sp)
	sw $s5,24($sp)
	
	move $s0,$a0 #array
	move $s1,$a1 #low
	move $s2,$a2#high
	
	move $s5,$s0 #p=array
	addi $t0,$s1,1 #low+i
	move $s3,$t0 #i=low+1
	
	li $s4,0 #npr=0
for:
	bge $s3,$s2,endf
if:
	move $a0,$s3
	jal checkp #checkp(i)
	
	move $t8,$v0
	
	bne $t8,1,endif
	
	sw $s3,0($s0) #*array=i
	
	
	addi $s0,$s0,4 #array++
	addi $s4,$s4,1 #npr++
endif:
	addi $s3,$s3,1 #i++		
	j for
endf:	
	add $t2,$s5,$s3 #p+npr
	
	sw $s4,0($t2) #*(p+npr)=npr
	
	move $v0,$s4
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	lw $s3,16($sp)
	lw $s4,20($sp)
	lw $s5,24($sp)
	addiu $sp,$sp,28
	
	jr $ra
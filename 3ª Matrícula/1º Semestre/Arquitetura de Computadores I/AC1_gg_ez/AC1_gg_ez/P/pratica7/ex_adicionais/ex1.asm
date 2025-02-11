	.data
	.eqv print_string,4
	.eqv print_int10,1
str:	.asciiz ","
	.text
	.globl main

insert:	
if:	ble $a2,$a3,else
	li $v0,1
	jr $ra 

else:	addi $a3,$a3,-1 #size-1
	move $t0,$a3 #i = size-1

for:	blt $t0,$a2,endf
	addiu $t3,$t0,1 #i+1
	sll $t3,$t3,2 #i*4
	addu $t2,$t3,$a0 #&array[i+1]
	sll $t5,$t0,2 #i*4
	addu $t4,$t5,$a0 #&array[i]
	
	lw $t6,0($t4)
	sw $t6,0($2) #array[i+1] = array[i]
	
	addiu $t0,$t0,-1 #i--
	
	j for

endf:	sll $a2,$a2,2 #pos*4
	addu $a0,$a0,$a2 #&array[pos]
	sw $a1,0($a0) #array[pos]=value
	
	li $v0,0 #return 0
	
	jr $ra

print_array:
	move $t1,$a0 #dar move pq e um ponteiro ig
	sll $a1,$a1,2 #n*4
	addu $t0,$t1,$a1 #$t0 = int *p = a+n

for_a:	bge $t1,$a1,enf_a
	
	lw $a0,0($t1)
	li $v0,print_int10
	syscall #print_int10(*a)
	
	la $a0,str
	li $v0,4
	syscall
	
	addiu $t1,$t1,4 #a++
	
	j for_a

endf_a: jr $ra
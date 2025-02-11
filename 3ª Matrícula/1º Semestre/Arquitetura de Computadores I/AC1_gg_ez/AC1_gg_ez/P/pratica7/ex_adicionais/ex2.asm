	.data
array:	.space 200 #50*4
	.eqv print_string,4
	.eqv print_int10,1
	.eqv read_int,5
str1:	.asciiz ", "
str2:	.asciiz "Size of array : "
str3:	.asciiz "array["
str4:	.asciiz "] = "
str5:	.asciiz "Enter the value to be inserted: "
str6:	.asciiz "Enter the position: "
str7:	.asciiz "\nOriginal array: "
str8:	.asciiz "\nModified array: "
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

for_a:	bge $t1,$a1,endf_a
	
	lw $a0,0($t1)
	li $v0,print_int10
	syscall #print_int10(*a)
	
	la $a0,str1
	li $v0,4
	syscall
	
	addiu $t1,$t1,4 #a++
	
	j for_a

endf_a: jr $ra

main:	addiu $sp,$sp,-20
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	sw $s2,12($sp)
	sw $s3,16($sp)

	la $s0,array #array[50]

	la $a0,str2
	li $v0,print_string
	syscall
	
	li $v0,read_int
	syscall
	
	move $s1,$v0 #array_size = read_int()
	
	li $t2,0 #i=0

for_m:	bge $t2,$s1,endf_m
	
	la $a0,str3
	li $v0,print_string
	syscall
	
	move $a0,$t2
	li $v0,print_int10
	syscall
	
	la $a0,str4
	li $v0,print_string
	syscall
	
	
	sll $t4,$t2,2 #i*4
	addu $t5,$s0,$t4 #&array[i]
	li $v0,read_int
	syscall
	sw $v0,0($t5) #array[i]=read_int()
	
	addiu $t2,$t2,1 #i++
	j for_m

endf_m:	la $a0,str5
	li $v0,print_string
	syscall
	
	li $v0,read_int
	syscall
	
	move $s2,$v0 #insert_value=read_int()
	
	la $a0,str6
	li $v0,print_string
	syscall
	
	li $v0,read_int
	syscall
	
	move $s3,$v0 #insert_pos=read_int()
	
	la $a0,str7
	li $v0,print_string
	syscall
	
	move $a0,$s0
	move $a1,$s1
	jal print_array
	
	move $a0,$s0
	move $a1,$s2
	move $a2,$s3
	move $a3,$s1
	jal insert
	
	la $a0,str8
	li $v0,print_string
	syscall
	
	move $a0,$s0
	addiu $s1,$s1,1
	move $a1,$s1
	jal print_array
	
	li $v0,0
	lw $ra,0($sp)
	lw $s0,4($sp)
	lw $s1,8($sp)
	lw $s2,12($sp)
	lw $s3,16($sp)
	addiu $sp,$sp,20
	jr $ra

	.data
result: .float 1.0
	.eqv read_float,6
	.eqv print_float,2
	.eqv read_int,5
	.text
	.globl main
	
#-------func abs começa------
abs:	move $v0,$a0

if:	bge $v0,'0',end
	mul $v0,$v0,-1
end:	jr $ra	
#-------func abs acaba----


#-------func xtoy começa------
xtoy:	addiu $sp,$sp,-20
	sw $ra,0($sp)
	sw $s0,4($sp) #i
	sw $s1,8($sp) #y
	s.s $f20,12($sp) #float x
	s.s $f22,16($sp) #result
	
	mov.s $f20,$f12 #guardar x
	
	li $s0,0 #i=0
	
	la $t3,result
	l.s $f22,0($t3) #result=1.0
	
	move $s1,$a0 #preservar y para uso futuro
	jal abs
	#move $t1,$v0 #acho q esta linha n e preciso

for_xt: bge $s0,$t1,end_fxt
	blez $s1,else_xt
	mul.s $f22,$f22,$f20 #result *= x
	j xt1

else_xt: div.s $f22,$f22,$f20 #result /= x

xt1:	addi $s0,$s0,1 #i++
 	j for_xt

end_fxt: mov.s $f0,$f22
	l.s $f22,16($sp)
	l.s $f20,12($sp)
	lw $s1,8($sp)
	lw $s0,4($sp)
	lw $ra,0($sp)
	addiu $sp,$sp,20
	jr $ra
#-------func xtoy acaba----


#-------func main começa------
main:	addiu $sp,$sp,-4
	sw $ra,0($sp)
	s.s $f20,4($sp)
	
	li $v0,read_float
	syscall #o read_float retorna no $f0
	
	mov.s $f20,$f0
	
	li $v0,read_int
	syscall
	
	move $a0,$v0
	mov.s $f12,$f20
	jal xtoy
	
	mov.s $f12,$f0
	li $v0,print_float
	syscall
	
	li $v0,0
	
	l.s $f20,4($sp)
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
#-------func main acaba------

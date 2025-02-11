	.data
result:	.float 1.0
	.eqv read_float,6
	.eqv print_float,2
	.eqv read_int,5
	.text
	.globl main
	
#######nao esta a funcionar a 100% ns pq

abs:	move $v0,$a0 #pq o parametro de entrada tmb vai ser o de saida
	
	bge $v0,0,end
	mul $v0,$v0,-1
	
end:	jr $ra

xtoy:	addiu $sp,$sp,-20 #prologo
	sw $ra,0($sp)
	sw $s0,4($sp)
	sw $s1,8($sp)
	s.s $f20,12($sp)
	s.s $f22,16($sp)
	
	mov.s $f20,$f12 #salvaguardar float x
	move $s0,$a0 #salvaguardar int y
	li $s1,0 #i=0
	la $t0,result
	l.s $f22,0($t0)

xtoy_for: move $a0,$s0 #meter y como parametro de entrada
	  jal abs
	  
	  bge $s1,$v0,xtoy_else #aquela condiçao lixo i<abs(y)
	  ble $s0,0,xtoy_else #if(y>0)
	  
	  mul.s $f22,$f22,$f20 #result*=x
	  j xtoy_endif 
	 	  
xtoy_else: div.s $f22,$f22,$f20 #result /= x 

xtoy_endif: addi $s1,$s1,1 #i++
	    j xtoy_for

xtoy_endf:  mov.s $f0,$f22 #passar result para o return da funçao
	
	l.s $f22,16($sp)
	l.s $f20,12($sp)
	lw $s1,8($sp)
	lw $s0,4($sp)
	lw $ra,0($sp)
	addiu $sp,$sp,20 #epilogo

main:	addiu $sp,$sp,-12
	sw $ra,0($sp)
	sw $s0,4($sp)
	s.s $f20,8($sp)
	
	li $v0,6
	syscall
	
	mov.s $f20,$f0
	
	li $v0,read_int
	syscall
	
	move $s0,$v0
	
	move $a0,$s0
	mov.s $f12,$f20
	jal xtoy
	
	mov.s $f12,$f0
	li $v0,print_float
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	lw $s0,4($sp)
	l.s $f20,8($sp)
	addiu $sp,$sp,12
	jr $ra

#void main(void)
#{
#	unsigned int res=0, i=0, mdor, mdo;
#
#	print_string("Introduza dois numeros: ");
#	mdor = read_int() & 0x0F;
# 	mdo = read_int() & 0x0F;
# 	while( (mdor != 0) && (i++ < 4) )
# 	{
# 	if( (mdor & 0x00000001) != 0 )
# 		res = res + mdo;
# 	mdo = mdo << 1;
# 	mdor = mdor >> 1;
# 	}
# 	print_string("Resultado: ");
# 	print_int10(res);
#}


#	MAPA DE REGISTOS
#	$t0 - res
#	$t1 - i
#	$t2 - mdor
#	$t3 - mdo
#	$t4 - mdor & 0x00000001 (variavel)	
#	$t5 - 0x0F
#	$t6 - 0x00000001
	.data
str1:	.asciiz "Introduza dois numeros: "
str2:	.asciiz "Resultado: "
	.eqv print_string,4
	.eqv read_int,5
	.eqv print_int10,1
	.text
	.globl main

main:	li $t0,0 #res=0
	li $t1,0 #i=0
	
	la $a0, str1
	li $v0,4
	syscall #print_string("Introduza dois numeros: ");
	
	li $v0,5
	syscall #read_int()
	
	move $t2,$v0
	li $t5,0x0F
	and $t2,$t2,$t5 #mdor = read_int() & 0x0F;
	
	li $v0,5
	syscall #read_int()
	
	move $t3,$v0
	li $t5,0x0F
	and $t3,$t3,$t5 #mdo = read_int() & 0x0F;

while:	beq $t2,$0,endw
 	bge $t1,4,endw
 	
 	li $t6,0x00000001
 	
if:	and $t4,$t2,$t6 #(mdor & 0x00000001)
	beq $t4,0,endif
	
	addu $t0,$t0,$t3 #res = res + mdo; 

endif:	sll $t3,$t3,1 #mdo = mdo << 1;
	srl $t2,$t2,1 #mdor = mdor >> 1; 
 	
 	addiu $t1,$t1,1 #i++
 	j while
 
endw:	la $a0,str2
 	li $v0,4
 	syscall #print_string("Resultado: ");
 	
 	move $a0,$t0
 	li $v0,1
 	syscall #print_int10(res);
 	
 	jr $ra #fim do programa

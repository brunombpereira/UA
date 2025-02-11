#mapa de registos
#n_even : $t0
#n_odd : $t1
#p1 : $t3
#p2 : $t4
#n : $t5
#a+n : $t6

	.data
	.eqv n, 35
	.eqv print_int10, 1
	.eqv print_char, 11
	.eqv read_int, 5
	.align 2
a:	.space 140
a1:	.space 140
	.text
	.globl main
	
main:		li $t0, 0			#int n_even = 0;
		li $t1, 0			#int n_odd = 0;
		la $t3, a			#$t3 = &a[0]
		li $t5, n			
		sll $t5, $t5, 2			#$t5 = n
		addu $t6, $t3, $t5		#$t5 = &a[n]
		
for1:		bge $t3, $t6, endf1		#for(p1 = a; p1 < (a+n); p1++)
		
		li $v0, read_int
		syscall				#read_int
		sw $v0, 0($t3)			#*p1 = read_int();
		
		addi $t3, $t3, 4		#p1++;
		
		j for1
endf1:
		
		la $t3, a			#p1 = a
		la $t4, a1			#p2 = a1
		
for2:		bge $t3, $t6, endf2		#for(p1 = a; p2 = b; pi < (a+n); p1++)
		
		lw $t7, 0($t3)
		rem $t8, $t7, 2			#$t7 = *p1 % 2;
		
if1:		beq $t8, 0, else		#if(*p1 % 2 != 0)
		sw $t7, 0($t4)			#*p2 = *p1;
		addi $t4, $t4, 4		#p2++;
		addi $t1, $t1, 1		#n_odd++;
		j endif1
		
else:		addi $t0, $t0, 1		#else
						#n_even++;
endif1:
		addi $t3, $t3, 4		#p1++;
		j for2
endf2:

		la $t4, a1			#p2 = a1
		sll $t8, $t1, 2
		addu $t8, $t8, $t4		#$t8 = a1 + n_odd
		
for3:		bge $t4, $t8, endf3		#for(p2 = b; p2 < (b+ n_odd); p2++)
		li $v0, print_int10
		lw $a0, 0($t4)
		syscall				#print_int10(*p2);
		
		li $a0, ','
		li $v0, print_char
		syscall
		
		addiu $t4, $t4, 4		#p2++;

		j for3
endf3:
		jr $ra	
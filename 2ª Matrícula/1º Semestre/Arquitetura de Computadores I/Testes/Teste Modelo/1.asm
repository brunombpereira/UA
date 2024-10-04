#1
        .data

    # eqvs:
        .eqv SIZE, 15
        .eqv print_int10, 1
        .eqv print_string, 4
    #labels:    
str1:   .asciiz "Invalid argc"
        .globl main
        .text

### func2   
# Mapa de registos
# f1 :  $s0
# k  :  $s1
# av :  $s2
# i  :  $s3
# res:  $t2     
main:  addi	$sp, $sp, -20
        sw      $s0, 16($sp)	# save f1 to stack
	sw	$s1, 12($sp)	# save k to stack
	sw	$s2, 8($sp)	# save av to stack
        sw	$s3, 4($sp)	# save i to stack
        sw	$ra, 0($sp)

        li   	$t1, 0 # i = 0
        li   	$t2, 0 # res = 0
    
    	move 	$s0, $a0        # f1 = $a0 -> $s0       
    	move 	$s1, $a1        # k = $a1 -> $s1
        move    $s2, $a2        # av = $a2 -> $s2

func2_if:
        blt     $s1, 2, func2_else # if k < 2 
        bgt     $s1, SIZE, func2_else # if k > SIZE 

        li      $t1, 0 # i = 0

func2_do:
        add     $t3, $s0, $t1 # $t3 = f1 + i -> f1[i]
        add     $t4, $s2, $t1 # $t4 = av + i -> av[i]

        move    $a0, $s2        # $a0 = av[i]
        jal     toi             # toi(av[i])

        sw      $v0, 0($t3)     # f1[i] = toi(av[i])

        addi    $t1, $t1, 1     # i++
        blt     $t1, $s1, func2_do # while i < k 
        
        move    $a0, $s0        # $a0 = f1
        move    $a1, $s1        # $a1 = k
        jal     avz             # avz(f1, k)    
        move    $t2, $v0        # res = avz(f1, k)

        j	func2_endif				
func2_else:
        la	$a0, str1	# $a0 = str1
        li	$v0, print_string	# print_string(str1)
        syscall
        
        li	$t2, -1	        # res = -1
func2_endif:
        
        
        move 	$v0, $t2   # return res
        lw   	$ra, 0($sp)
        lw      $s3, 4($sp)
        lw      $s2, 8($sp)
        lw	$s1, 12($sp)
        lw	$s0, 16($sp)
        addi 	$sp, $sp, 20
        
        jr   $ra

toi:
avz:


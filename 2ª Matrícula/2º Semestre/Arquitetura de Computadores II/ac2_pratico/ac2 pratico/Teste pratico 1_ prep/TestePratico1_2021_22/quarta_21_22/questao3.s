                    .data
                    .equ SFR_BASE_HI,0xBF88
                    .equ TRISE, 0x6100
                    .equ LATE, 0x6120
                    .equ resetCoreTimer,12
                    .equ readCoreTimer,11
                    .equ putChar,3
                    .equ printInt,6
                    .text 
                    .globl main

main:               lui $t0,SFR_BASE_HI

                    lw $t1,TRISE($t0)               # configurar o valor inicial
                    andi $t1,$t1,0xFFE1             # RE4..1 como saídas  x x x 0  0 0 0 x
                    sw $t1,TRISE($t0)

                    li $t3, 0x12                     # RB4 RB3 RB2 RB1 RB0 = 1 0 0 1 x

while:              lw $t2,LATE($t0)
                    andi $t2,$t2,0xFFE1
                    or $t2,$t2,$t3
                    sw $t2,LATE($t0)

                    li $v0,12                       # resetCoreTimer()
                    syscall

delay:              li $v0,11                       # readCoreTimer()
                    syscall

                    blt $v0,2857142,delay           # freq = 7hz

                    andi $t4,$t3,0x001E
                    srl $t4,$t4,1
                    move $a0,$t4
                    #li $a0,0x00040002               # binário com 4 bits
                    li $a1,4
                    sll $a1,$a1,16
                    ori $a1,$a1,2
                    li $v0,6                        # printInt(contador, 2 | 4 << 16) binário com 4 dígitos
                    syscall

                    li $a0,'\n'                     # putChar('\n')
                    li $v0,3
                    syscall

                    xori $t3,$t3,0x1E                # x x x 1  1 1 1 x
                    j while

                    jr $ra

                
                .data
                .equ resetCoreTimer,12
                .equ readCoreTimer,11
                .equ SFR_BASE_HI,0xBF88
                .equ TRISE,0x6100
                .equ LATE,0x6120
                .text
                .globl main

main:           addiu $sp,$sp,-8
                sw $ra,0($sp)
                sw $s0,4($sp)

                lui $t0,SFR_BASE_HI
                lw $t1,TRISE($t0)       # porto RE0 como saída
                andi $t1,$t1,0xFFFE     # x x x 0
                sw $t1,TRISE($t0)       

                ori $s0,$0,0            # v = 0

while:          lw $t2,LATE($t0)        # ler o que está na saída
                andi $t2,$t2,0xFFFE     # colocar o bit de interesse a zero
                or $t2,$t2,$s0          # convergir a saída com o contador
                sw $t2,LATE($t0)        

                li $v0,12               # resetCoreTimer()
                syscall

delay:          li $v0,11               # readCoreTimer()
                syscall

                blt $v0,10000000,delay  # f = 2 hz

                xori $s0,$s0,1          # complementar o bit 0
                j while

                jr $ra
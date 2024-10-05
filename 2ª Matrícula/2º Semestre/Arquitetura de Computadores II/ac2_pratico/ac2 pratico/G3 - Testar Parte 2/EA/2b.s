                .data
                .equ resetCoreTimer,12
                .equ readCoreTimer,11
                .equ SFR_BASE_HI,0xBF88
                .equ TRISE,0x6100
                .equ LATE,0x6120
                .equ TRISD,0x60C0
                .equ LATD, 0x60E0
                .text
                .globl main

main:           addiu $sp,$sp,-8
                sw $ra,0($sp)
                sw $s0,4($sp)

                lui $t0,SFR_BASE_HI
                lw $t1,TRISE($t0)       # porto RE0 como saída
                andi $t1,$t1,0xFFFE     # _ _ _ 0
                sw $t1,TRISE($t0)   

                lw $t2,TRISD($t0)       # configurar RD0 como saída
                andi $t2,$t2,0xFFFE
                sw $t2,TRISD($t0)

                ori $s0,$0,0            # v = 0

while:          lw $t3,LATE($t0)        # ler o que está na saída
                lw $t4,LATD($t0)
                andi $t3,$t3,0xFFFE     # colocar o bit de interesse a zero
                andi $t4,$t4,0xFFFE
                or $t3,$t3,$s0          # convergir a saída com o contador
                or $t4,$t4,$s0
                sw $t3,LATE($t0) 
                sw $t4,LATD($t0)       

                li $v0,12               # resetCoreTimer()
                syscall

delay:          li $v0,11               # readCoreTimer()
                syscall

                blt $v0,10000000,delay  # f = 2 hz

                xori $s0,$s0,1          # complementar o bit 0
                j while

                jr $ra
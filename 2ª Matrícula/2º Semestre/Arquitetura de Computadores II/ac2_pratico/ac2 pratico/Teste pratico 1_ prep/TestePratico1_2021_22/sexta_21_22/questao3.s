                .data
                .equ SFR_BASE_HI, 0xBF88
                .equ resetCoreTimer,12
                .equ readCoreTimer,11
                .equ printInt,6
                .equ putChar,3
                .equ TRISE,0x6100
                .equ LATE, 0x6120
                .text
                .globl main

main:           lui $t0,SFR_BASE_HI     # x 0 0 0  0 0 x x
                lw $t1,TRISE($t0)
                andi $t1,$t1,0xFF83     # RE6..2 como saídas
                sw $t1,TRISE($t0)

                lw $t2,LATE($t0)
                andi $t2,$t2,0xFF83
                sw $t2,LATE($t0)        # leds começam apagados, como se tivesse o valor 0

                li $t3,0                # valor inicial do counter = 0

while:          lw $t2,LATE($t0)
                andi $t2,$t2,0xFF83
                #sll $t3,$t3,2           # shift de 2 bits do contador
                or $t2,$t2,$t3          # convergir com o contador
                sll $t2,$t2,2
                sw $t2,LATE($t0)

                li $v0,12               # resetCoreTimer()
                syscall   

delay:          li $v0,11               # readCoreTimer()
                syscall      

                blt $v0,6153846,delay   # f = 3.5hz

                move $a0,$t3
                li $a1,5                # formatacao:   2 | 5 << 16
                sll $a1,$a1,16
                ori $a1,$a1,2
                li $v0,6                # printInt(counter, 2 | 5 << 16)
                syscall

                li $a0,'\n'             # putChar('\n')
                li $v0,3
                syscall

                bne $t3,0,j             # if counter = 0, reinicia a 24
                li $t3,24
                j while

j:              addi $t3,$t3,-1         # contagem decrescente
                j while

                jr $ra

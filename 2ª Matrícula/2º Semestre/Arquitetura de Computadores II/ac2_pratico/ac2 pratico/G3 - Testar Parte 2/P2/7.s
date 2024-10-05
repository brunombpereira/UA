                .data
                .equ resetCoreTimer,12
                .equ readCoreTimer,11
                .equ SFR_BASE_HI,0xBF88
                .equ TRISE,0x6100
                .equ LATE,0x6120
                .equ TRISB,0x6040
                .equ PORTB,0x6050
                .text
                .globl main

main:           addiu $sp,$sp,-8
                sw $ra,0($sp)
                sw $s0,4($sp)

                lui $t0,SFR_BASE_HI         # configurar saídas RB4..1
                lw $t1,TRISE($t0)
                andi $t1,$t1 0xFFE1
                sw $t1,TRISE($t0)

                lw $t2,TRISB($t0)           # configurar RB2 como entrada
                ori $t2,$t2,0x0004  
                sw $t2,TRISB($t0)

                ori $s0,$0,0                # iniciar a variável de contagem

while:          lw $t3,LATE($t0)
                andi $t3,$t3,0xFFE1         # colocar as saídas a 0
                or $t3,$t3,$s0              # convergir as saídas com o valor do contador
                sw $t3, LATE($t0)           # write  

                li $v0,12                   # resetCoreTimer()
                syscall   

delay:          li $v0,11                   # readCoreTimer()
                syscall

                blt $v0,13333333,delay      # f = 1.5hz

                lw $t4,PORTB($t0)           # ler registos RB
                andi $t4,$t4,0x0004         # isolar o RB2

                bne $t4,0,else              
                andi $t5,$s0,0x1            # RB2 = 0 deslocamento á direita
                sll $t5,$t5,3               # isolar o LSB e deslocá-lo para o MSB
                xor $t5,$t5,8               # negar esse mesmo bit

                srl $t6,$s0,1               # fazer o actual shift á direita do counter
                andi $t6,$t6,0xF            # manter os 4 bits apenas

                or $s0,$t5,$t6              # or das variáveis auxiliares
                j while

else:           andi $t5,$s0,0x8            # RB2 = 1 deslocamento de esquerda
                srl $t5,$t5,3               # colocar o MSB no lugar do LSB
                xor $t5,$t5,1               # negar esse MSB

                sll $t6,$s0,1               # fazer o actual shift do contador
                andi $t6,$t6,0xF            # manter 4 bits

                or $s0,$t5,$t6              # convergir as 2 variáveis auxiliares
                j while

                lw $ra,0($sp)
                lw $s0,4($sp)
                addiu $sp,$sp,8

                jr $ra

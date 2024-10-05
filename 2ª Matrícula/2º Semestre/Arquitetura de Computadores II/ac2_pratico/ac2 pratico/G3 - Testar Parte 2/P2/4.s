# Contador em anel de 4 bits (ring counter) com deslocamento à esquerda ou à direita, 
# dependendo do valor lido do porto RB1: se RB1=1, deslocamento à esquerda. Frequência 
# de atualização de 3 Hz (deslocamento à esquerda: 0001, 0010, 0100, 1000, 0001, …).             
            
            .data
            .equ resetCoreTimer,12
            .equ readCoreTimer,11
            .equ SFR_BASE_HI,0xBF88
            .equ TRISE,0x6100
            .equ TRISB,0x6040
            .equ PORTB, 0x6050
            .equ LATE,0x6120
            .equ LATB,0x6060
            .text
            .globl main

main:       addiu $sp,$sp, -8
            lw $ra,0($sp)
            lw $s0,4($sp)

            lui $t0,SFR_BASE_HI     # RE4..1 como saidas
            lw $t1,TRISE($t0)       # READ
            and $t1,$t1,0xFFE1      # modify    1 1 1 _   _ _ _ 1
            sw $t1,TRISE($t0)       # write

            lw $t2,TRISB($t0)       # RB1 como entrada, para delinear deslocamento á esquerda ou á direita
            ori $t2,$t2,0x0002      # _ _ _ _  _ _ 1 _  qq coisa or 1 = 1
            sw $t2,TRISB($t0)

            ori $s0,$0,1            # inicializar variável de contagem

while:      lw $t3,LATE($t0)        # atualizar os portos de saída
            andi $t3,$t3,0xFFE1
            or $t3,$t3,$s0
            sw $t3,LATE($t0)        # aqui na saída devem estar _ _ _ 1

            li $v0, 12              # resetCoreTimer()
            syscall
delay:      li $v0,11               # # readCoreTimer()
            syscall                

            blt $v0, 6666667,delay

            lw $t4,PORTB($t0)       # ler o porto de entrada RB1
            andi $t4,$t4,0x00020    # isolá-lo para depois ser alvo de comparação

if:         bne $t4,2,else          # se RB1 = 1, descolamento á esquerda
            bne $s0,8,cont          # verificar que o contador já não está no seu valor máximo : 1 _ _ _       
            ori $s0,$0,1            # se já tiver atingido o valor máximo, fazer o reset para _ _ _ 1
            j while

cont:       sll $s0,$s0,1           # deslocamento á esquerda
            j while                 # para atualizar as saídas

else:       bne $s0,0x1,elsecont    # se o $s0 tiver diferente de _ _ _ 1 continuamos a fazer shifts
            ori $s0,$0,0x8          # no caso do contador já estar _ _ _ 1 temos de dar reset e colocá-lo a 1 _ _ _ 
            j while

elsecont:   srl $s0,$s0,1           # se RB1 = 0, deslocamento á direita            
            j while                 # atualizar saídas

            lw $ra,0($sp)
            lw $s0,4($sp)
            addiu $sp,$sp,8

            jr $ra
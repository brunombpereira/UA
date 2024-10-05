                .data
                .equ SFR_BASE_HI,0xBF88
                .equ TRISE,0x6100
                .equ LATE,0x6120
                .equ TRISB,0x6040
                .equ LATB, 0x6060
                .text
                .globl main

main:           lui $t0,SFR_BASE_HI
                lw $t1,TRISE($t0)           # configurar RE2..RE5 como saídas
                andi $t1,$t1,0xFFC3         # 1 1 _ _   _ _ 1 1 
                sw $t1,TRISE($t0)

                lw $t2,TRISB($t0)           # configurar RB0..RB3 como entradas
                ori $t2,$t2,0x000F          # x x x x  1 1 1 1 
                sw $t2,TRISB($t0)           

while:          lw $t3,PORTB($t0)           # ler o porto de entrada
                andi $t3,$t3,0x000F         # isolar os bits de 0..3
                xori $t3,$t3,0x0009         # negar os bits 0 e 3 e por isso fazer o xor com 9 -  1 0 0 1

                lw $t4,LATE($t0)
                andi $t4,$t4,0x0xFFC3       # colocar saídas a 0
                or $t4,$t4,$t3              # convergir as entradas com as saídas
                sw $t4,LATE($t0)            # escrever nas saídas

                j while

                jr $ra

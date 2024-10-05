            .data
            .equ  SFR_BASE_HI,0xBF88
            .equ TRISE,0x6100
            .equ TRISD,0x60C0
            .equ PORTD,0x60D0
            .equ LATE,0x6120
            .text
            .globl main

main:       lui $t0,SFR_BASE_HI
            lw $t1,TRISE($t0)               # READ
            andi $t1,$t1,0xFFFE             # modify - bit RE0 a zero 
            sw $t1,TRISE($t0)               # WRITE

            lw $t2,TRISD($t0)
            ori $t2,$t2,0x0080              # configurar RD8 como porto de entrada
            sw $t2,TRISD($t0)

while:      lw $t3,PORTD($t0)               # ler do porto de entrada
            srl $t3,$t3,8                   # shift left para colocar o bit RD8 em RD0
            xor $t3,$t3,0x0001              # para fazer o negativo de tudo o que estiver á entrada

            lw $t4,LATE($t0)                # ler o porto de saída
            andi $t4,$t4,0xFFFE             # colocar o bit RE0 a 0
            or $t3,$t3,$t4                  # fazer o merge de 0's com qualquer coisa dá qualquer coisa e por isso o que estiver e RD8 fica em RE0 
            sw $t3,LATE($t0)                # escrever no porto de saida

            j while

            li $v0,0
            jr $ra
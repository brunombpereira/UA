            .data
            .equ  SFR_BASE_HI,0xBF88
            .equ TRISE,0x6100
            .equ TRISB,0x6040
            .equ PORTB,0x6050
            .equ LATE,0x6120
            .text
            .globl main

main:       lui $t0,SFR_BASE_HI
            lw $t1,TRISE($t0)               # READ
            andi $t1,$t1,0xFFFE             # modify - bit RE0 a zero 
            sw $t1,TRISE($t0)               # WRITE

            lw $t2,TRISB($t0)
            ori $t2,$t2,0x0001              # RB0 como porto de entrada
            sw $t2,TRISB($t0)

while:      lw $t3,PORTB($t0)               # ler do porto de entrada
            xor $t3,$t3,0x0001              # negar este bit
            sw $t3,LATE($t0)                # escrever no porto de saida

            j while

            li $v0,0
            jr $ra
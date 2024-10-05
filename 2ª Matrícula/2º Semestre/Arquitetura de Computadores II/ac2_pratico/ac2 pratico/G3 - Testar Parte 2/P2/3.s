# Contador binário crescente/decrescente cujo comportamento depende do valor lido do porto 
# de entrada RB3: se RB3=1, contador crescente; caso contrário contador decrescente; 
# frequência de atualização de 2 Hz

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

main:       addiu $sp,$sp,-8
            sw $ra,0($sp)
            sw $s0,4($sp)           # uma vez que o contador será uma variável incrementada depois de chamadas á função delay, temos de salvaguardar contexto

            lui $t0,SFR_BASE_HI     # RE4..1 como saidas
            lw $t1,TRISE($t0)       # READ
            and $t1,$t1,0xFFE1      # modify    1 1 1 _   _ _ _ 1
            sw $t1,TRISE($t0)       # write

            lw $t2,TRISB($t0)       # RB3 como entrada, para delinear contagem crescente ou decrescente
            ori $t2,$t2,0x0008      # _ _ _ _  1 _ _ _  qq coisa or 1 = 1
            sw $t2,TRISB($t0)

            ori $s0,$0,0            # inicializar o counter

while:      lw $t3,LATE($t0)        # atualizar os portos de saída com o valor do contador
            andi $t3,$t3,0xFFE1
            sll $t4,$s0,1           # dar shift ao contador por causa dos bits específicos das saídas
            or $t3,$t3,$t4
            sw $t3,LATE($t0)

            li $v0,12               # resetCoreTimer()
            syscall
delay:      li $v0,11               # readCoreTimer()
            syscall
            blt $v0,10000000,delay  # 500ms -> 10 000 000

            lw $t5,PORTB($t0)       # ler o RB3 e isolar esse bit
            andi $t5,$t5,0x0008

            beq $t5,8, else         # se RB3 = 1 , contador crescente
            addi $s0,$s0,-1         # se RB3 = 0 , contador decrescente
            j while

else:       addi $s0,$s0,1          # contador ++ 
            j while


            lw $ra,0($sp)
            lw $s0,4($sp)
            addi $sp,$sp,8
            jr $ra




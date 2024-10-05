# Contador binario crescente de 4 bits, atualizado com uma frequencia de 1Hz

            .data
            .equ resetCoreTimer,12
            .equ readCoreTimer,11
            .equ SFR_BASE_HI,0xBF88
            .equ TRISE,0x6100
            .equ LATE,0x6120
            .text
            .globl main

main:       lui $t0,SFR_BASE_HI         # RE4..1 como saidas
            lw $t1,TRISE($t0)           # READ
            andi $t1,$t1,0xFFE1         # modify
            sw $t1,TRISE($t0)           # write 

            li $t2,0                    # variavel de contagem - $t2

ciclo:      lw $t3,LATE($t0)
            andi $t3,$t3,0xFFE1         # RE4..0 desligados, a 0
            sll $t2,$t2,1               # alinhar o contador com os bits que quero alinhar
            or $t3,$t3,$t2              # convergir a saida apagada com o valor do contador
            sw $t3,LATE($t0)            # escrever o valor na saida

        # ------------------------------------------------- Alternativa á função delay 
            #li $v0,12
            #syscall
#delay:      li $v0,11
            #syscall
            #blt $v0,20000000,delay
        # ----------------------------------------------

            jal 1000                    # delay(1000ms)

            addi $t2,$t2,1              # atualizar a variavel de contagem

            blt $t2,16,cont
            li $v0,0                    # dar reset á variavel de contagem

cont:       j ciclo
            jr $ra

# -----------------------------------------------------------
delay:      move $t0,$a0                # colocar em $t0 o valor passado em argumento na chamada da funcao delay

            li $v0,12                   # resetCoreTimer();
            syscall

            li $t1,20000                # K = 20000
            mul $t0,$t0,$t1             # variavel = $t0 = K * ms

while2:     li $v0,11                   # readCoreTimer()
            syscall

            bge $v0,$t0,endw2
            j while2

endw2:      jr $ra

# -----------------------------------------------------------




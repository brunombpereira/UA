.data
                .equ SFR_BASE_HI, 0xBF88
                .equ resetCoreTimer,12
                .equ readCoreTimer,11
                .equ TRISE,0x6100
                .equ LATE, 0x6120
                .text
                .globl main

main:           lui $t0,SFR_BASE_HI
                lw $t1,TRISE($t0)           # RE6..2 como saídas 
                andi $t1,$t1,0xFF83         # _ 0 0 0   0 0 _ _ 
                sw $t1,TRISE($t0)

                ori $t2,$0,1                # $t0 = 1, contador com o valor inicial
		    sll $t2,$t2,2               # para convergir com o RB2

while:          lw $t3,LATE($t0)            # convergir o contador com as saídas
                andi $t3,$t3,0xFF83         # primeiro valor nos leds será 00001
                or $t3,$t3,$t2
                sw $t3,LATE($t0)

		    li $v0,12                   # resetCoreTimer()
                syscall

delay:          li $v0,11                   # readCoreTimer()
                syscall

                blt $v0,8695652,delay       # while(readCoreTimer() < 8695652) - f = 2.3Hz

                sll $t2,$t2,1               # shift ao contador
                bne $t2,0x0080,j            # se o contador tiver a 1000 0000(SITUAÇAO DE OVERFLOW JA)(já com o shift de 2 para convergir com o RB2), temos de lhe dar reset  
                li $t2,1                    # dar reset ao contador, se fizer ORI aqui era fazer 1000 000 ori 0000 0001 = 1000 0001 que não é o que queremos
                sll $t2,$t2,2               # dar sempre o shift de 2 sempre que se der reset
j:              j while

                jr $ra

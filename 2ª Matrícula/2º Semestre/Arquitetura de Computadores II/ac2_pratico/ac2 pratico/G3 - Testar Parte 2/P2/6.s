# exatamente o mesmo racíocinio do anterior mas para a direita

                .data
                .equ resetCoreTimer,12
                .equ readCoreTimer,11
                .equ SFR_BASE_HI,0xBF88
                .equ TRISE,0x6100
                .equ LATE,0x6120
                .text
                .globl main

main:           addiu $sp,$sp,8
                sw $ra,0($sp)
                sw $s0,4($sp)

                lui $t0,SFR_BASE_HI
                lw $t1,TRISE($t0)
                andi $t1,$t1,0xFFE1     # configurar 1 1 1 _  _ _ _ 1
                sw $t1,TRISE($t0)

                ori $s0,$0,0            # começar com o contador a  _ _ _ _ 

while:          lw $t2,LATE($t0)
                andi $t2,$t2,0xFFE1     # emergir o valor do contador com as saídas
                or $t2,$t2,$s0
                sw $t2,LATE($t0)

                li $v0,12               # resetCoreTimer()
                syscall
delay:          li $v0,11               # readCoreTimer()
                syscall

                blt $v0,13333333,delay  # f = 1.5hz
                
                # $t4 será o auxiliar 1
                # $t5 será o auxiliar 2
                andi $t4,$s0,0x1        # isolar o bit mais significativo do contador
                sll  $t4,$t4,3          # colocá-lo no bit menos significativo 
                xor $t4,$t4,8           # para negar o bit menos significativo que isolamos no passo anterior
                srl $t5,$s0,1           # o $s0 era _ _ _ _ passa a ser em $t5 _ _ _ 1
                andi $t5,$t5,0xF        $ ao acrescentar um 0 á direita no passo anterior, fiquei com 5 bit mas quer manter 4 bits apenas
                or $t5,$t5,$t4          # fazer o or do contador com shift com o bit MSB negado

                move $s0,$t5
                j while

                lw $ra,0($sp)
                lw $s0,4($t0)
                addiu $sp,$sp,8

                jr $ra
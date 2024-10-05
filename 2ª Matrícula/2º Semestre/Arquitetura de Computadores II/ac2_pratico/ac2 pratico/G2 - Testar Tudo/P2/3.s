            .data
            .equ printInt,6
            .equ putChar,3
            .equ resetCoreTimer,12
            .equ readCoreTimer,11
            .equ inkey,1
            .text
            .globl main

main:       addiu $sp,$sp,-16
            sw $ra,0($sp)
            sw $s0,4($sp)       # cnt1
            sw $s1,8($sp)       # cnt5
            sw $s2,12($sp)      # cnt10

            li $s0,0            # cnt1 = 0    
            li $s1,0            # cnt5 = 0
            li $s2,0            # cnt10 = 0
        
while:      li $v0,1            # inkey()
            syscall
            move $s4,$v0        # $s4 = c = inkey()
            
            bne $s4,'A',if2     # if(c == 'A')

            li $a0,50           # delay(50)
            jal delay
            addi $s2,$s2,1      # cnt10++

            rem $t0,$s2,2       # cnt10 % 2
            bnez $t0,c2         # salta se o resultado foi diferente de 0, se for igual incrementa cnt5
            addi $s1,$s1,1      # cnt++

c2:         rem $t0,$s2,10       # cnt10 % 10
            bnez $t0,imp
            addi $s0,$s0,1      # cnt1++

imp:        li $a0,'\r'
            li $v0,3            # putChar('\')
            syscall

            move $a0,$s0        # printInt(cnt1,10 | 5 << 16);
            li $a1,0x0005000A
            li $v0,6
            syscall

            li $a0,' '
            li $v0,3            # putChar(' ')
            syscall

            move $a0,$s1        # printInt(cnt5,10 | 5 << 16);
            li $a1,0x0005000A
            li $v0,6
            syscall

            li $a0,' '
            li $v0,3            # putChar(' ')
            syscall

            move $a0,$s2        # printInt(cnt10,10 | 5 << 16);
            li $a1,0x0005000A
            li $v0,6
            syscall

            j while

if2:        bne $t0,'N',while   #se não for nenhuma das opções volta ao while e volta a estar á escuta

            li $a0,100          # delay(100) - 10hz
            jal delay 

            addi $s2,$s2,1      # cnt10++

            rem $t0,$s2,2       # cnt10 % 2
            bne $t0,$0,c3       # if(cnt10 % 2 == 0)
            addi $s1,$s1,1      # cnt5++

c3:         rem $t0,$s2,10      # cnt10 % 10
            bne $t0,$0,imp2     # if(cnt10 % 10 == 0)
            addi $s0,$s0,1      # cnt1++

imp2:       li $a0,'\r'         # putChar('\r');
            li $v0,3
            syscall

            move $a0,$s0        # printInt(cnt1,10 | 5 << 16);
            li $a1,0x0005000A
            li $v0,6
            syscall

            li $a0,' '         # putChar(' ');
            li $v0,3
            syscall

            move $a0,$s1        # printInt(cnt5,10 | 5 << 16);
            li $a1,0x0005000A
            li $v0,6
            syscall

            li $a0,' '         # putChar(' ');
            li $v0,3
            syscall

            move $a0,$s2        # printInt(cnt10,10 | 5 << 16);
            li $a1,0x0005000A
            li $v0,6
            syscall

            j while

            lw $ra,0($sp)
            lw $s0,4($sp)
            lw $s1,8($sp)
            lw $s2,12($sp)
            addiu $sp,$sp,16
            
            jr $ra

delay:      move $t0,$a0             # colocar o valor passado em argumento num registo

            li $v0,12                # resetCoreTimer()
            syscall

            li $t1,20000            # 20000 para que o input seja um múltiplo de 1ms
            mul $t0,$t0,$t1         # 20 000 * ms

cond :      li $v0,11               # readCoreTimer()
            syscall         

            bge $v0,$t0,end
            j cond

end:        jr $ra
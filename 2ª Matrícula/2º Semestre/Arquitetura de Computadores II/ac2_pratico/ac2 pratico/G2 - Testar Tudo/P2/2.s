            .data
            .equ printInt,6
            .equ putChar,3
            .equ resetCoreTimer,12
            .equ readCoreTimer,11
            .text
            .globl main

main:       addiu $sp,$sp,-16
            sw $ra,0($sp)
            sw $s0,4($sp)
            sw $s1,8($sp)
            sw $s2,12($sp)

            li $s0,0            # cnt10 = 0    
            li $s1,0            # cnt5 = 0
            li $s2,0            # cnt1 = 0
        
while:      li $a0,100
            jal delay 

            addi $s0,$s0,1      # cnt10++

            rem $t0,$s0,2       # cnt10 % 2
            bne $t0,$0,if2      # if(cnt10 % 2 == 0)
            addi $s1,$s1,1      # cnt5++

if2:        rem $t0,$s0,10      # cnt10 % 10
            bne $t0,$0,else     # if(cnt10 % 10 == 0)
            addi $s2,$s2,1      # cnt1++

else:       li $a0,'\r'         # putChar('\r');
            li $v0,3
            syscall

            move $a0,$s2        # printInt(cnt1,10 | 5 << 16);
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

            move $a0,$s0        # printInt(cnt10,10 | 5 << 16);
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

while:      li $v0,11               # readCoreTimer()
            syscall         

            bge $v0,$t0,end
            j while

end:        jr $ra
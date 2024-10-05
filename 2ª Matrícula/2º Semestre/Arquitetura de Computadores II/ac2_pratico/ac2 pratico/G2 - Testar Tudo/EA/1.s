            .data
            .equ read_core_timer,11
            .equ reset_core_timer,12
            .equ putChar,3
            .equ print_int,6
            .text
            .globl main

main:       addiu $sp,$sp,-8
            lw $ra,0($sp)
            lw $s0,4($sp)

            li $s0,0                # $s0 = counter = 0
        
while:      li $a0,1                # 1 ms
            li $a1,200              # intervalos de 200ms
            jal TimeDone
            move $t2,$a0            # retValue

            move $a0,$s0
            li $a1,0x0004000A
            li $v0,6
            syscall                 # printInt(counter++, 10 | 4 << 16);

            li $a0,'\r'             # putChar('\r')
            li $v0,3
            syscall

            addi $s0,$s0,1          # counter ++
            j while

            li $v0,0
            jr $ra

TimeDone:   li $t0,0       # retValue = 0

            ble $a1,$0, else
            li $v0,12      # resetCoreTimer()
            syscall

            j endif

else:       li $v0,11      # readCoreTimer()
            syscall
            move $t1,$v0   # curCount = readCoreTimer()

            mul $t2,$a0,20000

            ble $t1,$t2,endif
            div $t0,$t1,20000

endif:      move $v0,$t0   # return retValue
            jr $ra
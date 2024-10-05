            .data
            .equ read_core_timer,11
            .equ reset_core_timer,12
            .equ putChar,3
            .equ print_int,6
            .text
            .globl main

main:   li $t0,0                # $t0 = counter = 0
        
while:  li $v0,12
        syscall

while1: li $v0,11
        syscall

        blt $v0,200000,while1

        move $a0,$t0
        li $a1,0x0004000A
        li $v0,6
        syscall                 # printInt(counter++, 10 | 4 << 16);

        li $a0,'\r'
        li $v0,3
        syscall

        addi $t0,$t0,1          # counter ++
        j while

        li $v0,0
        jr $ra

################### delay ####################

delay:  move $t0,$a0             # colocar o valor passado em argumento num registo

        li $v0,12                # resetCoreTimer()
        syscall

        li $t1,20000            # 20000 para que o input seja um múltiplo de 1ms
        mul $t0,$t0,$t1         # 20 000 * ms

while:  li $v0,11               # readCoreTimer()
        syscall         

        bge $v0,$t0,end
        j while

end:    jr $ra
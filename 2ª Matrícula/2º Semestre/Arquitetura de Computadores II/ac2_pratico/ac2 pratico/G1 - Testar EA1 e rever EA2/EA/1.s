# contador up/down de 8 bits, módulo 256, atualizado a cada 0.5s e é mostrado no ecrã em decimal e em binário
# o up será controlado pela tecla '+' e o down será controlado pela tecla '-'

        .data
        .equ up,1
        .equ down,0
        .equ putChar,3
        .equ printInt,6
        .equ inkey,1
        .text
        .globl main

main:   li $t0,0            # $t0 = state = 0
        li $t1,0            # $t1 = cnt = 0

do:     li $a0,'\r'         # putChar('\r');
        li $v0,3
        syscall

        or $a0,$t1,$0       # printInt( cnt, 10 | 3 << 16 );
        li $a1,0x0003000A   # arg2 -> decimal com 3 dígitos
        li $v0,6
        syscall

        li $a0,'\t'         # putChar('\t') - Tab character
        li $v0,3
        syscall

        or $a0,$t1,$0       # printInt( cnt, 2 | 8 << 16 );
        li $a1,0x00080002   # arg2 -> binário com 8 bits
        li $v0,6
        syscall

        li $a0,5            # passar o argumento para a função wait -> 5
        jal wait

        li $v0,1
        syscall
        or $t2,$t2,$v0      # c = $t2 = inkey();

if:     bne $t2,'+',else    # if( c == '+' )
        li $t0,up           # state = up

else:   li $v0,down         # state = down

if2:    bne $t0,up,else2
        addi $t1,$t1,1      # cnt + 1 
        andi $t1,$t1,0xFF   # cnt = (cnt+1) & 0xFF
        j while

else2:  addi $t1,$t1,-1     # cnt - 1
        andi $t1,$t1,0xFF   # cnt = (cnt-1) & 0xFF

while:  bne $t2,'q',do

        li $v0,0            # return 0
        jr $ra

# -------------------------------------------------------------------------------

wait:   addi $sp,$sp,-4         # Store the value of $ra (the return address) on the stack
        sw $ra,0($sp)

        li $t1,0                # Initialize the loop counter - $t1 = i = 0

loop:   move $t0,$a0            # passar em $t0 o valor passado em argumento na chamada da função wait
        lui $t2,515000          # Load the upper 16 bits of 515000 into $t2

        mul $t3,$t0,$t2         # Multiply ts by 515000
        slt $t4,$t1,$t3

        beq $t4,'0',done        # se $t4 = 0 então i >= 515000*ts e saímos do loop

        addi $t0,$t0,1          # incremento do counter
        j loop

done:   lw $ra,0($sp)
        addi $sp,$sp,4

        jr $ra
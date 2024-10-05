#int main(void)
#{
#    int value;
#    while(1)
#    {
#        printStr("\nIntroduza um inteiro (sinal e módulo): ");
#        value = readInt10();
#        printStr("\nValor em base 10 (signed): ");
#        printInt10(value);
#        printStr("\nValor em base 2: ");
#        printInt(value, 2);
#        printStr("\nValor em base 16: ");
#        printInt(value, 16);
#        printStr("\nValor em base 10 (unsigned): ");
#        printInt(value, 10);
#        printStr("\nValor em base 10 (unsigned), formatado: ");
#        printInt(value, 10 | 5 << 16); // ver nota de rodapé 3
#    }
    
#    return 0;
#}

        .data
        .equ printStr,8
        .equ printInt10,7
        .equ printInt,6
        .equ readInt10,5
str:    .asciiz "\nIntroduza um inteiro (sinal e módulo): "
str1:   .asciiz "\nValor em base 10 (signed): "
str2:   .asciiz "\nValor em base 2: " 
str3:   .asciiz "\nValor em base 16: "
str4:   .asciiz "\nValor em base 10 (unsigned): "
str5:   .asciiz "\nValor em base 10 (unsigned), formatado: "
        .text
        .globl main 

main:   

while:  la $a0,str                      # printStr("\nIntroduza um inteiro (sinal e módulo): ");   
        li $v0,8
        syscall

        li $v0,5                        # readInt10()
        syscall
        or $t0,$v0,$0                   # $t0 = value = readInt10();

        la $a0,str1                     # printStr("\nValor em base 10 (signed): ")
        li $v0,8
        syscall

        or $a0,$t0,$0                   # printInt10(value);
        li $v0,7
        syscall

        la $a0,str2                     # printStr("\nValor em base 2: ");
        li $v0,8
        syscall

        or $a0,$t0,$0                   # printInt(value, 2);
        li $a1,2
        li $v0,6
        syscall

        la $a0,str3                     #  printStr("\nValor em base 16: ");
        li $v0,8
        syscall

        or $a0,$t0,$0                   # printInt(value, 16);
        li $a1,16
        li $v0,6
        syscall

        la $a0,str4                     # printStr("\nValor em base 10 (unsigned): ")
        li $v0,8
        syscall 

        or $a0,$t0,$0                   # printInt(value, 10);
        li $a1,10
        li $v0,6
        syscall

        la $a0,str5                     # printStr("\nValor em base 10 (unsigned), formatado: ");
        li $v0,8
        syscall

        or $a0,$t0,$0                   # verificar esta constante ou se tenho de fazer cada operação. 
        li $a1,0x0005000A
        li $v0,6
        syscall

        li $v0,0
        jr $ra
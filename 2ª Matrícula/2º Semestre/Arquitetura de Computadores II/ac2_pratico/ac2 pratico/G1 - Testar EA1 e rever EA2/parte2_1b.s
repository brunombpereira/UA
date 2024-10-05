//int main(void)
// {
//    char c;
//    do {
//    c = inkey();
//    if( c != 0 )
//        putChar( c );
//    else
//        putChar('.');
//    } while( c != '\n' );
//    
//    return 0;
// }

// NOTA: O system call inkey() não é bloqueante, ou seja, se foi premida uma tecla devolve o
// respetivo codigo ASCII, mas se não foi premida qualquer tecla devolve o valor 0 (0x00)

// Funcionalidade: imprime o caracter premido pelo utilizado se este for diferente de 0, se for igual a 0 imprimi '.'
// Em assembly:

            .data
            .equ putChar, 3
            .equ inkey,1
ponto:      .asciiz '.' 
            .text
            .globl main

main:       

do:         li $v0,1        // colocar o inkey() á escuta de caracteres premidos
            syscall
            or $t0,$v0,$0    // $t0 = c = inkey();

            beq $t0,0,else  // branch if (c == 0)
            move $a0,$t0    // putChar( c )
            li $v0,3
            syscall         

else:       la $a0,ponto    // putChar('.')
            li $v0,3
            syscall   

while:      bne $t0,'\n',do

            li $v0,0
            jr $ra


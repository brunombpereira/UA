//int main(void)
// {
//    char c;
//    do
//    {
//    c = getChar();
//    putChar( c );
//    } while( c != '\n' );
//    
//    return 0;
// }

// NOTA: O system call getChar() é bloqueante, ou seja, só regressa ao programa chamador 
// quando for premida uma tecla, retornando o respetivo código ASCII.


//Funcionalidade do sistema: ler um caracter introduzido pelo utilizador e imprimi-lo no ecrã da consola.
// Em Assembly:

        .data
        .equ putChar,3
        .equ getChar,2
        .text
        .globl main

main:   li $t0,0                // c = $t0 = 0, inicializar a variável
        
ciclo:  li $v0,2                // getChar()
        syscall         
        move $t0,$v0            // c = getChar();

        move $a0,$t0            // colocar c como argumento de entrada para o putChar
        li $t0,3                // putChar( c )
        syscall 
        
        bne $t0,"\n",ciclo      // enquanto o caracter introduzido for diferente de \n continuar a imprimir

        li $v0,0                // return 0
        jr $ra



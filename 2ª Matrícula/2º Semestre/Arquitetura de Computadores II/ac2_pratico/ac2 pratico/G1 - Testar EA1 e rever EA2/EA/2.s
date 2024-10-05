            .data
            .equ size,20
            .equ printStr,8
            .equ readStr,9
            .equ printInt,6
            .equ printInt10,7
            .equ putChar,3
str:        .asciiz "\nIntroduza 2 strings:\n"
stre:       .space "\nResultados:\n"
str1:       .space size+1
str2:       .space size+1
str3:       .space 2*size+1      
            .text
            .globl main

main:       addiu $sp, $sp,-4
            sw $ra,0($sp)

            la $a0,str              # printStr("Introduza 2 strings: "); 
            li $v0,8
            syscall

            la $a0,str1             # readStr( str1, SIZE );
            li $a1,size
            li $v0,9
            syscall

            la $a0,str2             # readStr( str2, SIZE );
            li $a1,size
            li $v0,9
            syscall

            jal espaco

            la $a0,str3             # printStr("Resultados:\n");
            li $v0,8
            syscall

            la $a0,str1             # strlen(str1)
            jal strlen

            move $a0,$v0            # o que strlen retorna entra como argumento
            li $a1,10               # printInt( strlen(str1), 10 );
            li $v0,6
            syscall

            la $a0,str2             # strlen(str2)
            jal strlen

            move $a0,$v0            # o que strlen retorna entra como argumento
            li $a1,10               # printInt( strlen(str2), 10 );
            li $v0,6
            syscall

            la $a0,str3             # strcpy(str3, str1)
            la $a1,str1
            jal strcpy

            la $a0,str3             # strcat(str3, str2)
            la $a1,str2
            jal strcat

            move $a0,$v0            # printStr( strcat(str3, str2) );
            li $v0,8
            syscall 

            la $a0,str1             # strcmp(str1, str2)
            la $a1,str2
            jal strcmp

            move $a0,$v0            # printInt10( strcmp(str1, str2) )
            li $v0, 7
            syscall 

            lw $ra,0($sp)
            addiu $sp,$sp,4

            li $v0,0                # return 0; 
            jr $ra

# ------------------------------------------
# a função strlen  devolve o comprimento da string 'str' sem o caracter nulo '\0'

strlen:     li $t0,0                # $t0 = len = 0

for1:       lb $t1,0($a0)           # vou ao argumento da função que é um endereço para o carater e coloco-o num registo interno(16 bits)
            beqz $t1,endstrlen
            addi $t0,$t0,1          # len++
            addi $t1,$t1,1          # str++

            j for1

endstrlen:  move $v0,$t0
            jr $ra

# -----------------------------------------
# a função strcpy copia a string apontada por 'src' incluindo o '\0' caracter, para o enderenço de destino apontado por 'dst'

strcpy:     move $t0,$a0           # $t0 tem o conteúdo de dst(que é um endereço?   

for2:       lb $t1,0($a1)          # retirar o conteúdo de $a1 e colocar em t1
            sb $t1,0($a0)          # *p = dst
                                   # como o conteúdo do end. é um caracter -> 1 byte e posso utlizar lb e sb para retirar a informação do endereço
                                   # posso modificar $a0 pois já copiei o seu conteúdo para $t0
            beqz $t1,endstrlen     # usar aqui o 0 que é o código ascii do '\0'
            addi $a0,$a0,1         # dst++
            addi $a1,$a1,1         # src++
            j for2

endstrlen:  move $v0,$t0           # return p 
            jr $ra

# -----------------------------------------

# concatenates "dst" and "src" strings- O resultado é armazenado na string "dst"

strcat:     addiu $sp,$sp,-16
            sw $ra,0($sp)
            sw $s0,4($sp)
            sw $s1,8($sp)
            sw $s2,12($sp)
            move $s0,$a0               # move - move cnonteúdo 
            move $s1,$a1
            move $s2,$a0               # *p = dst, coloca no endereço apontado por p o conteúdo de dst

for3:       lb $t1,0($s0)              # conteúdo de dst é que vai estar a ser comparado com '\0'
            beqz $t1,endcat
            addi $s0,$s0,1             # dst++
            j for3

endcat:     move $a0,$s0               # strcpy( dst, src );
            move $a1,$s1
            jal strcpy
            move $v0,$s2               # return p;
            lw $ra,0($sp)
            lw $s0,4($sp)
            lw $s1,8($sp)
            lw $s2,12($sp)
            addiu $sp,$sp,16
            jr $ra

# -------------------------------------
# Compares two strings character by character 
# Returned value is: 
# < 0 string "str1" is "less than" string "str2" (first 
# non-matching character in str1 is lower, in ASCII, than 
# that of str2) 
# = 0 string "str1" is equal to string "str2" 
# > 0 string "str1" is "greater than" string "str2" (first 
# non-matching character in str1 is greater, in ASCII, than 
# that of str2) 

strcmp:     
for4:       lb $t0,0($a0)
            lb $t1,0($a1)
            bne $t0,$t1,endcmp
            bnez $t0,endcmp
            addi $a0,$a0,1              # str1++
            addi $a1,$a1,1              # str2++
            j for4

endcmp:     sub $v0,$t0,$t1
            jr $ra

# -----------------------------------

espaco:     li $a0,'\n'
            li $v0,3
            syscall
            jr $ra
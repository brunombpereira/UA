# Leia em ciclo infinito od dip-switches
# Valor lido em complemento para 1
# Apresentar valor lido em led em modo gráfico de barra
# Led mais significativo indica numero 

.equ SFR_BASE_HI, 0xBF88
.equ TRISE, 0x6100
.equ PORTE, 0x6110
.equ LATE, 0x6120


#LED RE0 to RE3 - output

.equ RE0, 0x0001   
.equ RE0_N,0xFFFE
.equ RE1, 0x0002
.equ RE1_N,0xFFFD
.equ RE2, 0x0004   
.equ RE2_N,0xFFFB
.equ RE3, 0x0008
.equ RE3_N,0xFFF7


.data

.text

init:
 	
 lui $a2,SFR_BASE_HI
 #posso usar qualquer registo, visto que vou chamar a função no
 #inicio da main 
 lw $t0,TRISE($a2) 
 # input  - 1 || output - 0 

 andi $t0,$t0,RE0_N 
 andi $t0,$t0,RE1_N
 andi $t0,$t0,RE2_N 
 andi $t0,$t0,RE3_N 

 sw $t0,TRISE($a2) 

  lw $t5,LATE($a2)
 andi $t5,$t5,0xFFF0 #limpa saida
 
  sw $t5,LATE($a2)

 jr $ra

.globl main #----------------------------------------
main:

 jal init 

whi:
 
 li $v0,2
 syscall #Get char
 
 beq $v0,'-',negativo # s1 == '-' é negativo
 
positivo: # ------------------------------------------
 
 li $v0,5
 syscall 
 
 move $s1,$v0

 li $t3,1  # i = 1
 li $t4,0  # out = 0 
whi1:
 bgt $t3,$s1,endwhi1 
 
 sll $t4,$t4,1
 addi $t4,$t4,1 #anda um bit para a esquerda e soma um, para criar o gráfico

 addi $t3,$t3,1 # i++	

 j whi1  
 
endwhi1:
 lw $t5,LATE($a2)
 andi $t5,$t5,0xFFF0 #limpa saida
 or $t5,$t5,$t4      # grava no LATE previamente limpa
 sw $t5,LATE($a2)    # manda para as saidas  
 j end

negativo: # -----------------------------------------------
  
 li $v0,5
 syscall
 
 move $s1,$v0
 
 li $t3,1  # i = 1
 li $t4,0  # out = 0 

whi2:
 bgt $t3,$s1,endwhi2  #if i< RE5|RE4  
 
 sll $t4,1
 addi $t4,$t4,1       #anda um bit para a esquerda e soma um, para criar o gráfico

 addi $t3,$t3,1 # i++	
 j whi2 

endwhi2:

 lw $t5,LATE($a2)
 andi $t5,$t5,0xFFF0  #limpa saida
 or $t5,$t5,$t4       # grava no LATE previamente limpa
 ori $t5,$t5,RE3
 
 sw $t5,LATE($a2)     # manda para as saidas  
  
end: #----------------------------------------- 

 j whi  #loop infinito 
  
 jr $ra # nunca chega cá

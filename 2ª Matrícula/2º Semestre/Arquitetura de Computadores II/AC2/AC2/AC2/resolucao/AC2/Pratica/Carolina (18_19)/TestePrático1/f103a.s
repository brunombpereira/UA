# Leia em ciclo infinito od dip-switches
# Valor lido em complemento para 1
# Apresentar valor lido em led em modo gráfico de barra
# Led mais significativo indica numero 

.equ SFR_BASE_HI, 0xBF88
.equ TRISE, 0x6100
.equ PORTE, 0x6110
.equ LATE, 0x6120

#dipswitch RE7 to RE4 - input

.equ RE4, 0x0010   
.equ RE4_N,0xFFE0
.equ RE5, 0x0020   
.equ RE5_N,0xFFDF
.equ RE6, 0x0040
.equ RE6_N,0xFFBF


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
 
 ori $t0,$t0,RE4
 ori $t0,$t0,RE5
 ori $t0,$t0,RE6

 andi $t0,$t0,RE0_N 
 andi $t0,$t0,RE1_N
 andi $t0,$t0,RE2_N 
 andi $t0,$t0,RE3_N 

 sw $t0,TRISE($a2) 

 jr $ra

.globl main #----------------------------------------
main:

 jal init 

whi:
 lw $t0,PORTE($a2)# read inputs
  
 move $t1,$t0
 andi $t1,RE6
 srl $t1,6   # guarda o estado do bit RE6 no bit0 | 1 numero é negativo, 0 numero é positivo 

 bne $t1,0,negativo # if RE6 != 0 ->Vai para NEGATIVO

posito: # ------------------------------------------
 
 move $t2,$t0 	 # t2 = PORTE state
 srl $t2,4       # t2 =  (bit0 = RE4) | (bit1 = RE5)
 andi $t2,0x0003 # so deixa o bit RE5 RE4 nos bit0 e bit1
 

li $t3,1  # i = 1
 li $t4,0  # out = 0 
whi1:
 bgt $t3,$t2,endwhi1 # if i< RE5|RE4  
 
 sll $t4,1
 addi $t4,$t4,1 #anda um bit para a esquerda e soma um, para criar o gráfico

 addi $t3,$t3,1 # i++	
 j whi1 
 lw $t5,LATE($a2)
 andi $t5,$t5,0xFFF0 #limpa saida
 or $t5,$t5,$t4 # grava no LATE previamente limpa
 sw $t5,LATE($a2) # manda para as saidas  
 
 j end


negativo: # -----------------------------------------------
  
 move $t2,$t0 	 # t2 = PORTE state
 not $t2,$t2     # inverte tudo
 srl $t2,4       # t2 =  (bit0 = RE4) | (bit1 = RE5)
 andi $t2,0x0003 # so deixa o bit RE5 RE4 nos bit0 e bit1
 
 li $t3,1  # i = 1
 li $t4,0  # out = 0 
whi2:
 bgt $t3,$t2,endwhi2 # if i< RE5|RE4  
 
 sll $t4,1
 addi $t4,$t4,1 #anda um bit para a esquerda e soma um, para criar o gráfico

 addi $t3,$t3,1 # i++	
 j whi2 

endwhi2:

 ori $t4,$t4,RE4	

 lw $t5,LATE($a2)
 andi $t5,$t5,0xFFF0 #limpa saida
 or $t5,$t5,$t4 # grava no LATE previamente limpa
 ori $t5,$t5,RE3


 

 sw $t5,LATE($a2) # manda para as saidas  
 
 j end
 
end: #----------------------------------------- 

 j whi  #loop infinito 
  
 jr $ra # nunca chega cá

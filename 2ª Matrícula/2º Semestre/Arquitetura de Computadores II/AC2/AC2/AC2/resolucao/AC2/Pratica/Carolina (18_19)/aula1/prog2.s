	.data
str: 	.asciiz "Key pressed\n"
	.globl main
	.text
main:	
wh2:	li $v0,1
	syscall
	beq $v0,$0,wh2
	beq $v0,'\n',end
	ori $v0,$0,8
	la $a0,str
	syscall
	j main
end:	jr $ra

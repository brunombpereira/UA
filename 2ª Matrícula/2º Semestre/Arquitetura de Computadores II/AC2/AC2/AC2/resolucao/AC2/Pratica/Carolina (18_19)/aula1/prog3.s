.data	

	.text
	.globl main
main:	li $v0,2
	syscall

	beq $v0,'\n',end
	li $v0,3
	move $a0,$v0
	syscall
	j main

end:	jr $ra

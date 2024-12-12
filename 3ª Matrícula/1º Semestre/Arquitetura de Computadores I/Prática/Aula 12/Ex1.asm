# typedef struct {		Alinhamento	Dimensão	Offset
# unsigned int id_number	4		4		0
# char first_name[18]		1		18		4
# char last_name[15]		1		15		22
# float grade			4		4		37->40
# }student			4		44

	.data
	
	.eqv MAX_STUDENTS,4
	.eqv print_string,4
	.eqv print_float,2
	.eqv read_int,5
	.eqv read_string,8
	.eqv read_float,6
	.eqv print_intu10,36
	
str0:	.asciiz "\nMedia: "
str1:	.asciiz "N. Mec: "
str2:	.asciiz "Primeiro Nome: "
str3:	.asciiz "Último Nome: "
str4:	.asciiz "Nota:	"

	.align 2
starr:	.space 176
media:	.space 4
max_grade:
	.float -20.0
sum:	.float 0.0

	.text
	.globl main
	
read_data:
	li $t0,0
	move $s0,$a0
	move $s1,$a1
for:
	bge $t0,$s1,endf
	
	mulu $t1,$t0,44
	addu $t2,$t1,$s0
	
	la $a0,str1
	li $v0,print_string
	syscall
	
	li $v0,read_int
	syscall
	sw $v0,0($t2)
	
	la $a0,str2
	li $v0,print_string
	syscall
	
	addiu $a0,$t2,4
	li $a1,17
	li $v0,read_string
	syscall
	
	la $a0,str3
	li $v0,print_string
	syscall
	
	addiu $a0,$t2,22
	li $a1,14
	li $v0,read_string
	syscall
	
	la $a0,str4
	li $v0,print_string
	syscall
	
	li $v0,read_float
	syscall
	
	s.s $f0,40($t2)
	
	addi $t0,$t0,1
	j for
endf:
	jr $ra
	
max:
	la $t0,max_grade
	l.s $f2,0($t0)
	la $t0,sum
	l.s $f4,0($t0)
	
	addu $t1,$a0,$a1
for2:
	bge $a0,$t1,endf2
	
	l.s $f6,40($a0)
	add.s $f4,$f4,$f6
if:
	c.le.s $f6,$f2
	bc1t endif
	
	mov.s $f2,$f6
	move $v0,$a0
endif:
	addiu $a0,$a0,44
	j for2
endf2:
	mtc1 $a1,$f8
	cvt.s.w $f8,$f8
	div.s $f4,$f4,$f8
	s.s $f8,0($a2)
	
	jr $ra
	
print_student:
	move $t0,$a0
	
	la $a0,str1
	li $v0,print_string
	syscall
	
	lw $a0,0($t0)
	li $v0,print_intu10
	syscall
	
	la $a0,str2
	li $v0,print_string
	syscall
	
	addiu $a0,$t0,4
	li $v0,print_string
	syscall
	
	la $a0,str3
	li $v0,print_string
	syscall
	
	addiu $a0,$t0,22
	li $v0,print_string
	syscall
	
	la $a0,str4
	li $v0,print_string
	syscall
	
	l.s $f12,40($t0)
	li $v0,print_float
	syscall
	
	jr $ra
	
main:
	addiu $sp,$sp,-4
	sw $ra,0($sp)
	
	la $a0,starr
	li $a1,MAX_STUDENTS
	jal read_data
	
	la $a0,starr
	li $a1,MAX_STUDENTS
	la $a3,media
	jal max
	move $t0,$v0
	
	la $a0,str0
	li $v0,print_string
	syscall
	
	la $t1,media
	l.s $f12,0($t1)
	li $v0,print_float
	syscall
	
	move $a0,$t0
	jal print_student
	
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra
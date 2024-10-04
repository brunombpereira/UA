# typedef struct
# {                         Align       Size        Offset
#     int acc;              4           4           0
#     unsigned char nm;     1           1           4
#     double grade;         8           8           5->8
#     char quest[14];       1           14          16
#     int cq;               4           4           30->32
# } t_kvd;                  8           36          

    .data

# labels  
sum:    .double 0.0

# offsets
        .eqv   acc, 0
        .eqv   nm, 4
        .eqv   grade, 8
        .eqv   quest, 16
        .eqv   cq, 32

        .globl main
        .text

# func4
# Mapa de registos
# nv:   $t0
# pt:   $t1
# i:    $t2
# j:    $t3
# sum:  $f0

main:
        # init 
        move   $t0, $a0        # nv = a0
        move   $t1, $a1        # pt = a1

        li     $t2, 0          # i = 0


        la     $t4, sum        # 
        l.d    $f0, 0($t4)     # sum = 0.0

        # loop
func4_for:
        bge     $t2, $t0, func4_enfor   # if (i >= nv) goto endfor
        
        li     $t3, 0          # j = 0

func4_do:

        lb      $t4, quest($t1) # $t4 = pt->quest
        add     $t4, $t4, $t3   # $t4 = pt->quest + j => pt->quest[j]
        
        mtc1    $t4, $f4        # $f4 = pt->quest[j]
        cvt.d.w $f4, $f4        # $f4 = (double) pt->quest[j]

        add.d   $f0, $f0, $f4   # sum += (double) pt->quest[j]
    
        addi    $t3, $t3, 1     # j++

        lb		$t5, nm($t1)		# $t5 = pt->nm

func4_while: blt    $t3, $t5, func4_do   # if (j < i) goto endo

        
        l.d     $f4, 0($t1)     # $f4 = pt->grade
        div.d   $f4, $f0, $f4   # $f4 = sum / pt->grade
        cvt.w.d $f4, $f4        # $f4 = (int) $f4

        mfc1    $t4, $f4        # $t4 = (int) $f4
        sw		$t4, acc($t1)	# pt->acc = (int) $f4 
    
        addi    $t2, $t2, 1      # i++
        addi    $t1, $t1, 36     # pt + 36 to go to the next struct (i guess)
        j       func4_for       # goto for

func4_enfor:

        # return
        lw      $t4, cq($t1)    # $t4 = pt->cq
        mtc1    $t4, $f4        # $f4 = pt->cq
        cvt.d.w $f4, $f4        # $f4 = (double) pt->cq

        l.d     $f6, grade($t1) # $f6 = pt->grade

        mul.d   $f12, $f4, $f6  # return(pt->cq * (double)pt->grade)	 
        

        jr      $ra

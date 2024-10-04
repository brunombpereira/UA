
        .data
# lables

oldg:   .float -1.0
g:      .float 1.0
s:      .float 0.0

        .text
        .globl  main

# Mapa de registros
# a : $t0
# t : $f0
# n : $t1
# oldg : $f2
# g : $f4
# s : $f6
# k : $t2

main:
        # t ja esta em $f0
        move    $t0,$a0      # $t0 = a
        move    $t1,$a1      # $t1 = n
        

        la     $t0,oldg      # $t0 = &oldg
        l.s    $f2,0($t0)    # $f2 = oldg

        la     $t0,g         # $t0 = &g
        l.s    $f4,0($t0)    # $f4 = g
        
        la     $t0,s         # $t0 = &s
        l.s    $f6,0($t0)    # $f6 = s

        li     $t2,0        # k = 0
func3_for:
        bge	   $t2,$t1,func3_endfor # for (k = 0; k < n; k++)	
        
func3_while:
        sub.s   $f8,$f4,$f2  # $f8 = g - oldg
        c.le.s  $f0,$f8      # (t <= g - oldg) 
        bc1f    func3_endwhile

        mov.s   $f2,$f4      # oldg = g

        add    $t0,$t0,$t2  # &a[k]
        l.s    $f10,0($t0)   # $f10 = a[k]
        add.s   $f14,$f4,$f10 # $f14 = g + a[k]
        div.s  $f4, $f14, $f0 # g = (g + a[k]) / t

        j      func3_while
func3_endwhile:        

        add.s   $f6,$f6,$f4  # s += g

        add    $t0,$t0,$t2  # &a[k]
        l.s    $f10,0($t0)   # $f10 = a[k]
        mov.s  $f10,$f4      # a[k] = g
        s.s    $f10,0($t0)   # a[k] = g

        addi    $t2,$t2,1    # k++
        j       func3_endfor
func3_endfor:

        mtc1    $t1,$f16      # $f14 = (int)n
        cvt.s.w $f16,$f16     # $f14 = (float)n
        div.s   $f12,$f6,$f16 # return s / (float)n 

        jr      $ra


TimeDone:     li $t0,0       # retValue = 0

              ble $a1,$0, else
              li $v0,12      # resetCoreTimer()
              syscall

              j endif

else:         li $v0,11      # readCoreTimer()
              syscall
              move $t1,$v0   # curCount = readCoreTimer()

              mul $t2,$a0,20000

              ble $t1,$t2,endif
              div $t0,$t1,20000

endif:        move $v0,$t0   # return retValue
              jr $ra
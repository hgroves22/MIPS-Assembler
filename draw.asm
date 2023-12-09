#This is starter code, so that you know the basic format of this file.
#Use _ in your system labels to decrease the chance that labels in the "main"
#program will conflict

.data
picture: .word 255 8 16 8 16 255 16 255 8

.text
main:
    la $t0, picture
    addi $t1, $0, 0 //counter
    addi $s0, $0, 0 // x cord
    addi $s1, $0, 0 // y cord
    draw:
        xLoop:
            lw $t2, 0($t0)
            sw $s0, -224($0) # set x
            sw $s1, -220($0) # set y
            sw $t2, -216($0) # color
            sw $0, -212($0) # write 

            addi $t6, $0, 2
            addi $t0, $t0, 4
            beq $s0, $t6, helper
            j xLoop

        helper:
            addi $s0, $0, 0
            addi $s1, $s1, 1

            addi $t4, $0, 2
            beq $s1, $t4, endDraw
            j xLoop
        
    endDraw:
        addi $t0, $0, 100
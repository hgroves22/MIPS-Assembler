.data 
.text 
.globl main
main:
    addi $t0, $0, 15
    addi $t1, $0, 16
    j firstJump
    addi $t0, $0, 15
    addi $t0, $0, 15
    addi $t0, $0, 15
    addi $t0, $0, 15
    addi $t0, $0, 15
firstJump:
    addi $t0, $0, 16
    jal secondJump
    addi $t0, $0, 100
    jr $ra
    j endLoop
secondJump:
    jalr $ra
    addi $t0, $0, 105
endLoop:
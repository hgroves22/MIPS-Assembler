.data 
.text 
.globl main
main:
    addi $t0, $0, 15
    addi $t1, $0, 16
    beq $t0, $t1, endLoop
    j firstJump
    addi $t0, $0, 15
    addi $t0, $0, 15
    addi $t0, $0, 15
    addi $t0, $0, 15
    addi $t0, $0, 15
firstJump:
    addi $t0, $0, 16
    jal main
endLoop:
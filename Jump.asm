.data

dogLabel: .asciiz dog
numLabel: .word 1 2 3

.text
.globl main
main:
    j realTest
    addi $t2, $0, 4
    beq $t1, $t2, _syscallEnd_
    addi $t0, $0, 8
    j second    
    addi $s0, $0, 314
    addi $s0, $0, 3414
    addi $s0, $s0, 1
    second:
    addi $t1, $0, 4
    
    j main

    _syscallEnd_:
    addi $sp, $0, 9999

    realTest:
    addi $t0, $0, 96
    

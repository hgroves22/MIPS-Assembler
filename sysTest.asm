.data

dogLabel: .asciiz dog
numLabel: .word 1 2 3

.text
.globl main
main:
    la $t0 dogLabel
    addi $a0, $t0, 0
    addi $v0, $0, 4
    syscall
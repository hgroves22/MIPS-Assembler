.data

dogLabel: .asciiz dog
numLabel: .word 1 2 3

.text
.globl main
main:
    addi $v0, $0, 1
    addi $a0, $0, 100
    syscall
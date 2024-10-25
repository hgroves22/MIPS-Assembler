.data 
.text 
.globl main
main:
    addi $t0, $0, 10
    addi $t1, $0, 100
    blt $t0, $t1, first
    addi $s0, $0, 999 # should not reach
first:
    addi $t0, $0, 50
    bge $t0, $t1, first
    addi $t0, $0, 100
    blt $t0, $t1, first
    ble $t0, $t1, second
    addi $s0, $0, 999 # should not reach
second:
    addi $t0, $t0, 1
    bgt $t0, $t1, third
    addi $s0, $0, 999 # should not reach
third:
    addi $t0, $t0, -1
    bge $t0, $t1, fourth
    addi $s0, $0, 999 # should not reach
fourth:
    addi $s0, $0 10
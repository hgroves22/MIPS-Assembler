.data 
.text 
.globl main
main:
    li $t0, 10
    mov $t1 $t0
    li $t0, 7
    li $t1, -50
    abs $t0
    abs $t1
    addi $t1, $t1, 1
    abs $t1
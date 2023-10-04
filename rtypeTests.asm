.data 
.text 
.globl main
main:
    add $t0, $t1, $t2 //works
    sub $t0, $t1, $t2 //works
    mult $t0, $t1 //works
    div $t0, $t1 //works
    mflo $t0 //works
    mfhi $t0 //works
    sll $t0, $t1, 2 //works
    srl $t0, $t1, 3 //works
    slt $t0, $t1, $t2 //works
    jalr $t0, $t1 // works
    jr $t0 //works
    syscall //works
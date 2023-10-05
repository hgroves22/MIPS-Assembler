.data 
.text
.globl main
main:
    secondLabel:
    # addi tests
    addi $t0, $t1, 0 # works

    addi $t0, $t1, 5 # works
    addi $t0, $t1, 32767 # works (max bound)
    ## addi $t0, $t1, 32768 (error message works)
    
    addi $t0, $t1, -5 # works
    addi $t0, $t1, -32767 # works (max bound)
    ## addi $t0, $t1, -32768 (error message works)

    beq $t0, $t1, label
    bne $t0, $t1, secondLabel

    label:
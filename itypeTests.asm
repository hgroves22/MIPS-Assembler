.data 
.text 
.globl main
main:
    # addi tests
    addi $t0, $t1, 0 # works

    addi $t0, $t1, 5 # works
    addi $t0, $t1, 32767 # works (max bound)
    ## addi $t0, $t1, 32768 (error message works)
    
    addi $t0, $t1, -5 # works
    addi $t0, $t1, -32767 # works (max bound)
    ## addi $t0, $t1, -32768 (error message works)
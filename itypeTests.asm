.data

testNumber: .word 1500
secondNumber: .word 100

#secondTest: .asciiz "Hello"

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

    beq $t0, $t1, label //works
    bne $t0, $t1, secondLabel //works

    label:

    addi $t0, $0, 1500 //works
    la $t0, testNumber //works

    la $t0, secondNumber

    #need to test

    //j

    //jal

    sw $t0, 4($t1)

    lw $t0, 12($0)
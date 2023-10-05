.data

testNumber: .word 1500 200 5 
secondNumber: .word 100
thirdNumber: .word main
firstWord: .asciiz "Hello"

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
    la $t0, thirdNumber
    la $t0, firstWord

    #need to test

    //j

    //jal

    sw $t0, 4($t1) //work
    lw $t0, 12($0) //work
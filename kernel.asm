#This is starter code, so that you know the basic format of this file.
#Use _ in your system labels to decrease the chance that labels in the "main"
#program will conflict

.data
heap_pointer: .word 0 #TODO: Where should heap start?  OS/Kernel+ Static

.text
_syscallStart_:
    beq $v0, $0, _syscall0 #jump to syscall 0
    addi $k1, $0, 1
    beq $v0, $k1, _syscall1 #jump to syscall 1
    addi $k1, $0, 5
    beq $v0, $k1, _syscall5 #jump to syscall 5
    addi $k1, $0, 9
    beq $v0, $k1, _syscall9 #jump to syscall 9
    addi $k1, $0, 10
    beq $v0, $k1, _syscall10 #jump to syscall 10
    addi $k1, $0, 11
    beq $v0, $k1, _syscall11 #jump to syscall 11
    addi $k1, $0, 12
    beq $v0, $k1, _syscall12 #jump to syscall 12
    ##Error state - this should never happen - treat it like an end program
    j _syscall10

#Do init stuff
_syscall0:
    # Initialization goes here
    addi $sp, $0, -4096  #Initialize stack pointer
    # Set up heap_pointer
    la $k1, _END_OF_STATIC_MEMORY_
    addi $sp, $sp, 4 # allocate memory to store $t0
    sw $t0, 0($sp) #store $t0
    la $t0, heap_pointer #get the address of the heap pointer
    sw $k1, 0($t0) #load the heap pointer into static memory
    lw $t0, 0($sp) #load back $t0
    addi $sp, $sp, 4 # deallocate memory
    j _syscallEnd_

#Print Integer
_syscall1: 
    # Print Integer code goes here
    sw $a0, -256($0)
    jr $k0

#Read Integer
_syscall5:
    # Read Integer code goes here
    addi $sp, $sp, -12
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    sw $t2, 8($sp)

    addi $t0, $0, 0
    addi $t1, $0, 0
    addi $t2, $0, 0

    fiveLoop:
        lw $t0, -236($0)
        addi $t1, $0, 58 #is $t0 < 58
        slt $t1, $t0, $t1
        beq $t1, $0, fiveEnd
        addi $t1, $0, 47
        slt $t1, $t1, $t0 #is 47 < $t0
        beq $t1, $0, fiveEnd
        addi $t0, $t0, -48
        addi $t2, $t2, $t0
        sw $0, -240($0) #set keyboard ready to 0 to get next character
        j fiveLoop:

    fiveEnd:
        lw $t0, 0($sp)
        lw $t1, 4($sp)
        lw $t2, 8($sp)
        addi $sp, $sp, 12
        sw $0, -240($0)
        jr $k0

#Heap allocation
_syscall9:
    # Heap allocation code goes here
    la $v0, heap_pointer
    lw $v0, 0($t0)
    add $v0, $v0, $a0
    jr $k0

#"End" the program
_syscall10:
    j _syscall10

#read character
_syscall11:
    # read character code goes here
    elevenLoop:
        lw $v0, -240($0) # keyboard ready
        beq $v0, $0, elevenLoop #loop until key is pressed
        lw $v0, -236($0) #read keyboard character
        sw $0, -240($0) # sets keyboard ready to 0 to get next character
        jr $k0

#print character
_syscall12:
    # print character code goes here $a0
    sw $a0, -256($0)
    jr $k0

##extra credit syscalls go here?

_syscallEnd_:
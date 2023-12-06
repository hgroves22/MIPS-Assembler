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
    # single digits first then go to multiple (same for read)
    # ascii from keyboard  figure how to turn it into an integer    
    # Print Integer code goes here
    jr $k0

#Read Integer
_syscall5:
    lw $t0, -240($0)
    # Read Integer code goes here
    jr $k0

#Heap allocation
_syscall9:
    # Heap allocation code goes here
    jr $k0

#"End" the program
_syscall10:
    j _syscall10

#read character
_syscall11:
    # read character code goes here
    elevenLoop:
        lw $v0, -240($0)
        beq $v0, $0, elevenLoop #loop until key is pressed
        lw $v0, -236($0)
        jr $k0

#print character
_syscall12:
    # print character code goes here $a0
    sw $a0, -256($0)
    jr $k0

##extra credit syscalls go here?

_syscallEnd_:
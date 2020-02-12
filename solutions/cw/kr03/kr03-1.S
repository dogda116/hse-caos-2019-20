        .data
A:      .int    0
B:      .int    0
C:      .int    0
X:      .int    0
        .text
        .global process
        .global A, B, C, X
process:   
        movl    %edx, X
        movl    A, %eax
        mull    X
        mull    X
        mov     %eax, %ecx
        movl    $5, %eax
        mull    B
        mull    X
        sub     %eax, %ecx
        movl    $2, %eax
        mull    C
        add     %eax, %ecx
        movl    %ecx, %edx
        ret

        .data
A:      .int    0
B:      .int    0
C:      .int    0
D:      .int    0
R:      .int    0
        .text
        .global process
        .global A, B, C, D, R
process:   
        movl    A, %eax
        imull   B       /* eax *= B (i - signed) */
        movl    %eax, R /* R = A * B */
        movl    C, %eax 
        imull   D       /* eax *= D (now eax = C * D) */
        subl    %eax, R /* R -= eax */
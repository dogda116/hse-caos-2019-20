        .text
        .global main
main:
        xorl    %ebx, %ebx
loop_read:
        call    readi32
        jc      loop_end
        addl    %eax, %ebx
        jno     loop_read
if_overflow:
        movl    $2147483646, %ebx
        adcl    $0, %ecx
        addl    %ecx, %ebx
loop_end:
        movl    %ebx, %eax
        call    writei32
        call    nl
        xorl    %eax, %eax
        ret

        .text
        .global main
main:
        xorl    %esi, %esi
        xorl    %edi, %edi
loop_read:
        call    readi32
        jnc     odd_or_even
        movl    %edi, %eax
        call    writei32
        call    nl
        movl    %esi, %eax
        call    writei32
        call    nl
        xorl    %eax, %eax
        ret
odd_or_even:
        testl   $1, %eax
        jz      even
odd:
        addl    %eax, %esi
        jmp     loop_read
even:
        addl    %eax, %edi
        jmp     loop_read
        .text
        .global main
seq_end:
        movl    %ebx, %eax
        call    writei32
        call    nl
        decl    %ebx            /* --ebx */
        cmpl    $0, %ebx        /* ebx - 0 */
        jge     seq_end
        xor     %eax, %eax
        ret
main:   
        call    readi32
        movl    %eax, %ebx
        cmpl    $0, %eax        /* eax - 0 */
        jge     seq_end         /* jump to seq_end if cmp result equals zero */
        xor     %eax, %eax
        ret

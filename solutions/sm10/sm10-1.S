	.text
print_format:
        .asciz  "%llu\n"        
	.globl  process

process:
        /* standard prologue */
        pushl   %ebp
        movl    %esp, %ebp
        
        /* save callee-saved registers */
        pushl   %edi
        pushl   %esi
        
        /* little-endian encoding, A - reference to first 4 least-significant bytes
        A+4 - reference to 4 most-significant bytes 
        ms      ls
        %edx    %eax
        */
        movl    A, %eax
        movl    A + 4, %edx
        
        /* multiply by 2 using bit-shifting left */
        shll    $1, %eax
        
        /* after previous operation we may have carry (CF = 1)
        use rcl (rotate through carry left) - shift all the bits toward more-significant bit positions,
        The RCL instruction shifts the CF flag into the least-significant bit and shifts the most-significant bit into the CF flag. 
        */
        rcl     $1, %edx

        /*
        ms      ls
        %edi    %esi
        */
        movl    B, %esi
        movl    B + 4, %edi
        
        /* divide by 2 using bit-shifting right */
        shrl    $1, %edi
        
        /* similarly using rcr (rotate through carry right) */
        rcr     $1, %esi
        
        /* subtract two results, least-significant parts first (eax - esi), 
        then most-significant parts (edx - edi) using sbb - subtract with borrow
        since CF could be set (edx - (edi + CF)) 
        */
        subl    %esi, %eax
        sbb     %edi, %edx
        
        /* prepare to call printf("%llu\n", X)
        align stack by 16-bytes */
        and     $-16, %esp
        
        /* first argument's address must end on 0 (multiple of 16)
        stack:
        hole    (16 - 4 - 8 = 4 bytes)
        result (8 bytes - 64 bit)
        print_format (4 bytes)
        */
        
        /* cover hole */
        subl    $4, %esp
        
        /* push arguments:
        ms bytes ] result
        ls bytes ]
        print_format
        */
        pushl   %edx
        pushl   %eax
        pushl   $print_format
        
        call    printf
        
        /* now we need to clear stack after ourselves
        -8 since there are 2 callee-saved registers
        and we return to them
        */
        leal    -8(%ebp), %esp
        
        /* restore initial callee-saved registers */
        popl    %esi
        popl    %edi
        
        /* standard epilogue */
        popl    %ebp
	ret

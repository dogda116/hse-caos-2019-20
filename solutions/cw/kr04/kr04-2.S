	.text      
	.globl  process

process:
        /* standard prologue */
        pushl   %ebp
        movl    %esp, %ebp
        
        /* save callee-saved  regs */
        pushl   %ebx
        pushl   %edi
        pushl   %esi
        
        /*
        struct S
        {
            struct S *next;     at %eax
            int z[2];           z[0] at 4(%eax),  z[1] at 8(%eax) 
            int y[2];           y[0] at 12(%eax),  y[1] at 16(%eax)
        };
        long long t1 = (long long) p->z[0];
        long long t2 = (long long) p->y[1];
        long long t3 = (long long) p->z[1];
        long long t4 = (long long) p->y[0];
        long long t5 = t1 * t2;
        long long t6 = t3 * t4;
        long long t = t5 + t6;
        */
        
        /* reserve memory on stack */
        /* subl    $72, %esp */
        
        movl    %eax, %ecx
        /* save t1 at
        -16(%ebp), -12(%ebp)
        ls               ms */
        
        movl    4(%ecx), %eax
        cdq
        movl    %eax, -16(%esp)
        movl    %edx, -12(%esp)
        
        
        
        /* save t2 at
        -24(%ebp), -20(%ebp)
        ls               ms */
        movl    16(%ecx), %eax
        cdq
        movl    %eax, -24(%esp)
        movl    %edx, -20(%esp)
        
        /* save t3 at
        -32(%ebp), -28(%ebp)
        ls               ms */
        movl    8(%ecx), %eax
        cdq
        movl    %eax, -32(%esp)
        movl    %edx, -28(%esp)
        
        /* save t4 at
        -40(%ebp), -36(%ebp)
        ls               ms */
        movl    12(%ecx), %eax
        cdq
        movl    %eax, -40(%esp)
        movl    %edx, -36(%esp)
        
        /* multiply t1 and t2, save as t5 at 
        -48(%ebp), -44(%ebp)
        ls               ms */
        movl    -12(%esp), %eax
        imull   -24(%esp), %eax
        movl    %eax, %edx
        movl    -20(%esp), %eax
        imull   -16(%esp), %eax
        leal    (%edx,%eax), %ecx
        movl    -24(%esp), %eax
        mull    -16(%esp)
        addl    %edx, %ecx
        movl    %ecx, %edx
        movl    %eax, -48(%esp)
        movl    %edx, -44(%esp)
        
        /* multiply t3 and t4, save as t6 at 
        -56(%ebp), -52(%ebp)
        ls               ms */
        movl    -28(%esp), %eax
        imull   -40(%esp), %eax
        movl    %eax, %edx
        movl    -36(%esp), %eax
        imull   -32(%esp), %eax
        leal    (%edx,%eax), %ecx
        movl    -40(%esp), %eax
        mull    -32(%esp)
        addl    %edx, %ecx
        movl    %ecx, %edx
        movl    %eax, -56(%esp)
        movl    %edx, -52(%esp)
        
        /* add t5 and t6, save as t at
        -64(%ebp), -60(%ebp)
        ls               ms */
        movl    -48(%esp), %ecx
        movl    -44(%esp), %ebx
        movl    -56(%esp), %eax
        movl    -52(%esp), %edx
        addl    %ecx, %eax
        adcl    %ebx, %edx
        movl    %eax, -64(%esp)
        movl    %edx, -60(%esp)
        
        /* if (t < 0) return -1 */
        cmpl    $0, -60(%esp)
        js      ret_minus1
        
        /* t /= 16 */
        movl    -64(%esp), %ecx
        movl    -60(%esp), %ebx
        movl    %ebx, %eax
        sarl    $31, %eax
        cltd
        andl    $15, %eax
        movl    $0, %edx
        addl    %ecx, %eax
        adcl    %ebx, %edx
        shrdl   $4, %edx, %eax
        sarl    $4, %edx
        movl    %eax, -64(%esp)
        movl    %edx, -60(%esp)
        
        /* if t can be presented in uint32_t return
        32 least-significant bits stored in -64(%ebp),
        otherwise return -1 */
        
        cmpl    $0, -60(%esp)
        jle     ret_t

ret_minus1:
        movl    $-1, %eax
        jmp     finish

ret_t:
        movl    -64(%esp), %eax

finish:
        /* free stack */
        /* addl    $72, %esp */
        
        /* movl    $69, %eax */

        /* restore callee-saved registers */
        popl    %esi
        popl    %edi
        popl    %ebx
        
        movl    %ebp, %esp
        /* standard epilogue */
        popl    %ebp
	ret
    

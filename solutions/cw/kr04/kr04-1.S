	.text      
	.globl  forward$args

forward$args:
        /* standard prologue */
        pushl   %ebp
        movl    %esp, %ebp
        
        /* save callee-saved  regs */
        pushl   %ebx
        pushl   %edi
        pushl   %esi
        
        /* 
        read int v2 and cast it long long 
        least significant bytes will be in %eax
        most  significant bytes will be in %edx
        */
        movl    8(%ebp), %eax
        cdq
        
        /* 
        read long long v3
        least significant bytes will be in %esi
        most  significant bytes will be in %edi
        */
        movl    12(%ebp), %esi
        movl    16(%ebp), %edi
        
        /* read float v4 */
        movl    20(%ebp), %ebx
        
        /* align stack */
        and     $-16, %esp
        
        /* cover hole to keep stack aligned after pushes */
        subl    $8, %esp
        
        /* push v3 on stack */
        pushl   %edi
        pushl   %esi
        
        /* push v4 on stack */
        pushl   %ebx
        
        /* push v2 on stack */
        pushl   %edx
        pushl   %eax
        
        /* push void* that */
        pushl   %ecx
        
        call    process
        
        /* clear stack */
        leal    -12(%ebp), %esp
        
        /* restore initial callee-saved registers */
        popl    %esi
        popl    %edi
        popl    %ebx
        
        /* return result with opposite sign as required */
        negl    %eax
        
        /* standard epilogue */
        popl    %ebp
	ret
        

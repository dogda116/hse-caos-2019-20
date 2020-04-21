	.text
	.globl  exchange

exchange:
        /* standard prologue */
        pushl   %ebp
        movl    %esp, %ebp
        
        /* save callee-saved registers */
        pushl   %ebx
        pushl   %edi
        pushl   %esi
        
        /* subl    $16, %esp */
        
        /* %esi = *a */
        movl    %eax, %esi
        xorl    %eax, %eax
        
        /* %edi = n */
        movl    %edx, %edi
        xorl    %edx, %edx
        movl    %edi, -4(%esp)
        
        /* %ecx = n / 2 (initialize k) */
        movl    %edi, %eax
        movl    $2, %edi
        xorl    %edx, %edx
        divl    %edi       
        movl    %eax, %ecx
        
        xorl    %eax, %eax
        xorl    %edx, %edx
        
        /* %ebx = 0 (initialize counter i) */
        xorl    %ebx, %ebx
        
        /* (initialize counter of swaps) */
        movl    $0, -16(%esp)

        jmp     loop_cond
        
while_loop:
        /* while (i < k) */      
        
        /* get a[i] */
        movl    (%esi, %ebx, 4), %eax   
        
        /* -4(%ebp) = n - i - 1 */
        movl    -4(%esp), %edi
        subl    %ebx, %edi
        subl    $1, %edi

        /* get a[n - i - 1] */
        movl    (%esi, %edi, 4), %edx     
        
        /* if a[i] > a[n - i - 1] */
        cmpl    %edx, %eax
        jbe     cont

        /* a[i] = a[n - i - 1] */
        movl    %edx, (%esi, %ebx, 4)
        
        /* a[n - i - 1] = a[i] (from saved in eax) */
        movl    %eax, (%esi, %edi, 4)
        
        /* ++swaps */
        incl    -16(%esp)
        
cont:     
        /* ++i */
        incl    %ebx
        
loop_cond:
        cmpl    %ebx, %ecx
        jne     while_loop
        
fin:
        /* save number of swaps in %ecx */
        movl    -16(%esp), %ecx
        
        /* addl    $16, %esp */
        
        /* restore initial callee-saved registers */
        popl    %esi
        popl    %edi
        popl    %ebx
        
        movl    %ebp, %esp
        /* standard epilogue */
        popl    %ebp
	ret
 

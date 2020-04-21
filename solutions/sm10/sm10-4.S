	.text     
	.globl  dot_product

dot_product:
        /* standard prologue */
        pushl   %ebp
        movl    %esp, %ebp
        
        /* save callee-saved registers */
        pushl   %edi
        pushl   %esi
        
        /* get parameters:
        first parameter (n) at 8(%ebp),
        second(*a) at 12(%ebp),
        third(*b) at 16(%ebp) */
        movl    8(%ebp), %ecx
        movl    12(%ebp), %esi
        movl    16(%ebp), %edi
        
        /* store result in %xmm7 */
        pxor    %xmm7, %xmm7
        
while_n_bgr_four:
        /* we cant use vector operation if there are less than four floats left in vectors */
        cmp     $4, %ecx
        jl      zero_n_four
        
        /* load 128 bits (in our case 4 floats) into sse registers */
        movups  (%esi), %xmm0
        movups  (%edi), %xmm1
        
        /* dot_product (a1, a2, a3, a4) * (b1, b2, b3, b4)
        %xmm1 now contains (a1b1, a2b2, a3b3, a4b4) */
        mulps   %xmm0, %xmm1
        
        /* %xmm7 is (0, 0, a1b1 + a2b2, a3b3 + a4b4) */
        haddps  %xmm1, %xmm7
        
        pxor    %xmm6, %xmm6
        
        /* %xmm7 is (0, a1b1 + a2b2 + a3b3 + a4b4, 0, 0) */
        haddps  %xmm6, %xmm7

        /* %xmm7 is (a1b1 + a2b2 + a3b3 + a4b4, 0, 0, 0) */
        haddps  %xmm6, %xmm7
        
        /* n -= 4 */
        subl    $4, %ecx
        
        /* skip 4 processed floats (4 * 4 bytes) */
        addl    $16, %esi
        addl    $16, %edi
        jmp     while_n_bgr_four
 
zero_n_four:
        cmp     $0, %ecx
        jle     n_zero
        
        /* load one float to each register */
        movss   (%esi), %xmm0
        movss   (%edi), %xmm1
        
        /* multiply them */
        mulss   %xmm0, %xmm1
        
        /* add to %xmm7 */
        addss   %xmm1, %xmm7
        
        /* n -= 1 */
        decl    %ecx
        
        /* skip to next pair of floats */
        addl    $4, %esi
        addl    $4, %edi
        jmp     zero_n_four

n_zero:
        /* return result with respect to standard calling convention, i.e
        load result into %st(0) using fld */
        
        /* reserve memory */
        subl    $4, %esp
        
        /* copy reslut float to stack */
        movss   %xmm7, (%esp)
        
        /* load from stack into %st(0) */
        fld     (%esp)
        
        /* clear stack */
        addl    $4, %esp
        
        /* restore initial callee-saved registers */
        popl    %esi
        popl    %edi
        
        /* standard epilogue */
        popl    %ebp
	ret
  

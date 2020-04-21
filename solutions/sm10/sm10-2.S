	.text      
	.globl  myhypot

myhypot:
        /* standard prologue */
        pushl   %ebp
        movl    %esp, %ebp
        
        /* get parameters:
        first parameter at 8(%ebp),
        second at 16(%ebp),
        third at 24(%ebp) */
        movsd   8(%ebp), %xmm0
        movsd   16(%ebp), %xmm1
        movl    24(%ebp), %eax
        
        /* calculate sqrt(x^2 + y^2) */
        mulsd   %xmm0, %xmm0
        mulsd   %xmm1, %xmm1
        addsd   %xmm1, %xmm0
        sqrtsd  %xmm0, %xmm4
        
        /* save result in address stored in %eax */
        movsd   %xmm4, (%eax)
        
        /* standard epilogue */
        popl    %ebp
	ret
  

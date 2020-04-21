	.text
step:   .double 2.0
pos1:   .double 1.0
neg1:   .double -1.0        
	.globl  mysin

mysin:
        /* standard prologue */
        pushl   %ebp
        movl    %esp, %ebp
        
        /* input, current sum, output -- stored in %xmm7 */
        
        /* current term in %xmm6 */
        movsd   %xmm7, %xmm6
        
        /* numerator coefficient -(x * x) in %xmm5 */
        movsd   %xmm7, %xmm5
        mulsd   %xmm7, %xmm5
        mulsd   neg1, %xmm5
        
        /* initialize counter k in %xmm4 */
        movsd   pos1, %xmm4
        
while_loop:
        addsd   step, %xmm4
        movsd   %xmm4, %xmm3
        addsd   neg1, %xmm3
        
        /* %xmm2 sum on previous step */
        movsd   %xmm7, %xmm2
        
        /* S_i = -(x^2)/(k(k-1)) * S_{i-1} 
        where %xmm5 = -(x^2) , %xmm4 = k, %xmm3 = k-1
        */
        mulsd   %xmm5, %xmm6
        divsd   %xmm4, %xmm6
        divsd   %xmm3, %xmm6
        
        /* add term to the sum */
        addsd   %xmm6, %xmm7
        
        /* check whether the sum has increased */
        comisd  %xmm2, %xmm7
        jnz     while_loop
        
        
        /* standard epilogue */
        popl    %ebp
	ret
        

	.text      
	.globl  процесс

процесс:
        /* standard prologue */
        pushl   %ebp
        movl    %esp, %ebp
        
        /* save callee-saved registers */
        pushl   %edi
        pushl   %esi
        
        
        /* get parameters:
        first parameter (*a) at 8(%ebp),
        second(b) at 12(%ebp),
        third(*c) at 16(%ebp) */
        movl    8(%ebp), %ecx
        movl    12(%ebp), %eax
        movl    16(%ebp), %esi
        
        movl    $3, %edi
        
        /* %eax *= 3 */
        imull   %edi
        
        /* if b * 3 cant be presented in int32 return 1 */
        jo      ret_1
        
        /* dereference *a and multiply it by 2 (add to itself) */
        movsbl  (%ecx), %ecx

        addb    %cl, %cl
        
        /* if *a * 2 cant be presented in int8 return 2 */
        jo      ret_2
        
        /* calculate b * 3 - *a * 2 */
        subl    %ecx, %eax
        
        /* if b * 3 - *a * 2 cant be presented in int8 return 3 */
        cmpl    $127, %eax
        jg      ret_3
        cmpl    $-128, %eax
        jl      ret_3
        
        /* save result in address stored in %edx, i.e in *c */
        movb    %al, (%esi)
        movl    $0, %eax
        jmp     fin
ret_1:
        movl    $1, %eax
        jmp     fin
ret_2:
        movl    $2, %eax
        jmp     fin
ret_3:
        movl    $3, %eax

fin:
        
        /* restore initial callee-saved registers */
        popl    %esi
        popl    %edi
        
        /* standard epilogue */
        popl    %ebp
	ret
  

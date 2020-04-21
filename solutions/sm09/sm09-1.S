	.text
format: .asciz  "%d %d %d\n"   
	.globl  print_fib

print_fib:
        /* standard prologue */
        pushl   %ebp
        movl    %esp, %ebp
        
        /* save initial %ebx, since %ebx is callee-saved */
        pushl   %ebx
        
        /* first fib_num to %ebx */
        movl    A, %ebx
        addl    B, %ebx
        
        /* second fib_num to %edx 
        second fib_num is A + B + B, i.e. %ebx + B */
        movl    %ebx, %edx
        addl    B, %edx
        
        /* third fib_num to %eax
        third fib_num is %edx + %ebx */
        movl    %ebx, %eax
        addl    %edx, %eax

        /* now we need to call printf("%d %d %d\n", x1, x2, x3)
        where x1 = %ebx, x2 = %edx, x3 = %eax 
        arguments are pushed in reversed order 
        e.g x3 = %eax is pushed first*/
        
        pushl   %eax
        pushl   %edx
        pushl   %ebx
        pushl   $format
        call    printf
        
        /* free previously pushed parameters from stack  
        addl    $[4 * num_of_pushes], %esp */
        addl    $16, %esp
        
        /* restore initial %ebx */
        popl    %ebx
        
        /* free stack 
        p.s not actually needed here since we already have done this manually */
        movl    %ebp, %esp
        
        /* standard epilogue */
        popl    %ebp
	ret

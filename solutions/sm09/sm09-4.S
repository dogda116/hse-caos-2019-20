	.text
scan_format:
        .asciz  "%d %d %d %d"
print_format:
        .asciz  "%d\n"        
	.globl  process

process:
        /* standard prologue */
        pushl   %ebp
        movl    %esp, %ebp
        
        /* 
           allocate memory on stack for local variables
           a1 at -4(%esp), b1 at -8(%esp), 
           a2 at -12(%esp), b2 at -16(%esp), 
           ans at -20(%esp)
        */
        subl    $20, %esp
        
        /* initialize ans with 0 */
        movl    $0, -20(%ebp)
        jmp     seq_scan
intersection:
        /* max(0, min(b1, b2) - max(a1, a2)) */
        movl    -8(%ebp), %eax
        cmpl    %eax, -16(%ebp)
        jge     b2_bigger
        movl    -16(%ebp), %ecx
        jmp     check_a
b2_bigger:
        movl    -8(%ebp), %ecx
check_a:
        movl    -4(%ebp), %eax
        cmpl    %eax, -12(%ebp)
        jge     a2_bigger
        movl    -4(%ebp), %edx
        jmp     zero_or_add
a2_bigger:
        movl    -12(%ebp), %edx
zero_or_add:
        subl    %edx, %ecx
        cmpl    $0, %ecx
     
        jle     seq_scan
        addl    %ecx, -20(%ebp)
seq_scan:
        /* call scanf */
        leal    -16(%ebp), %ecx /* b2 */
        pushl   %ecx
        leal    -12(%ebp), %ecx /* a2 */
        pushl   %ecx
        leal    -8(%ebp), %ecx  /* b1 */
        pushl   %ecx
        leal    -4(%ebp), %ecx  /* a1 */
        pushl   %ecx
        pushl   $scan_format
        call    scanf
        
        /* after calling scanf %eax equals the number of successfully scanned arguments */
        cmpl    $4, %eax
        jz      intersection
        
        pushl   -20(%ebp)
        pushl   $print_format
        
        call    printf
        
        movl    %ebp, %esp
        
        /* standard epilogue */
        popl    %ebp
	ret
  

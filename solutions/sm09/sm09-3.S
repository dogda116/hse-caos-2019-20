	.text  
	.globl  mystrcmp

mystrcmp:
        /* standard prologue */
        pushl   %ebp
        movl    %esp, %ebp
        
        /* save initial %ebx, since %ebx is callee-saved */
        pushl   %ebx
        
        /* to access sub-program's parameters use postive offset over %ebp
        e.g 8(%ebp) to access first parameter
        12(%ebp) to access second parameter and so on */
        movl    8(%ebp), %ebx
        movl    12(%ebp), %edx
        /* now %ebx and %edx are pointers to the beginings of str1 and str2 respectively */
while:
        /* save and derefernce pointers to compare with zero byte (end of string) */
        movl    %ebx, %eax
        movl    %edx, %ecx
        movzbl  (%eax), %eax
        movzbl  (%ecx), %ecx
        cmpl    $0, %eax
        jz      zero_or_not_equal
        cmpl    $0, %ecx
        jz      zero_or_not_equal
        
        /* if both values are not zero compare them with each other */
        cmpl    %eax, %ecx
        jnz     zero_or_not_equal
        
        /* continue cycle when equal by incrementing pointers */
        incl    %ebx
        incl    %edx
        jmp     while
zero_or_not_equal:
        subl    %ecx, %eax
        /* 
           %eax > 0 if str1[i] > str2[i]
           %eax < 0 if str1[i] < str2[i] 
           %eax = 0 if str1[i] == str2[i] 
        */
        
        /* restore initial %ebx */
        popl    %ebx
        
        /* free stack */
        movl    %ebp, %esp
        
        /* standard epilogue */
        popl    %ebp
	ret

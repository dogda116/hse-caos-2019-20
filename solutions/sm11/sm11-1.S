#include <asm/unistd_32.h>
	.text      
	.globl  _start

_start:
        /* reserve on stack for char c */
        subl    $4, %esp
 
while_read: 
        /*
        char c;
        int val = read(0, &c, sizeof(c));
        */
        
        /* system call's number in %eax */
        movl    $__NR_read, %eax
        
        /* syscall's parameters in %ebx, %ecx, %edx (... %esi, %edi) */
        movl    $0, %ebx        /* first parameter (0 - stdin) */
        movl    %esp, %ecx      /* second parameter - address of variable c */
        movl    $1, %edx        /* third parameter - size of variable c */
        
        /* int (short of interrupt), int $0x80 passes control to interrupt vector 0x80 */ 
        int     $0x80
        
        /* the return value of read is in %eax */
        
        /* if %eax <= 0 then reached end of file or an error occurred */
        test    %eax, %eax
        jle     exit_c
        
        /* extend with zeroes one-byte char to int (long) */
        movzbl  (%esp), %eax
        
        /* if (c <= '0') jump to print */
        cmp     $'0', %eax
        jbe     print_w
        
        /* if (c > '9) jump to print */
        cmp     $'9', %eax
        ja      print_w
        
        /* else ('1' <= c <= '9') */
        movl    $'0', %eax
print_w:
        movl    %eax,  (%esp)
        
        /* system call's number in %eax */
        movl    $__NR_write, %eax
        
        /* syscall's parameters in %ebx, %ecx, %edx (... %esi, %edi) */
        movl    $1, %ebx        /* first parameter (0 - stdout) */
        movl    %esp, %ecx      /* second parameter - address of variable c */
        movl    $1, %edx        /* third parameter - size of variable c */
        
        /* int (short of interrupt), int $0x80 passes control to interrupt vector 0x80 */ 
        int     $0x80
        
        jmp     while_read

exit_c:
        /* syscall exit(0); */
        movl    $__NR_exit, %eax
        xorl    %ebx, %ebx
        int     $0x80

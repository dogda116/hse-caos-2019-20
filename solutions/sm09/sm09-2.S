	.text  
	.globl  satsum

satsum:
        /* standard prologue */
        pushl   %ebp
        movl    %esp, %ebp
        
        /* to access sub-program's parameters use postive offset over %ebp
        e.g 8(%ebp) to access first parameter
        12(%ebp) to access second parameter and so on */
        movl    8(%ebp), %eax
        addl    12(%ebp), %eax
        /* check carry flag (CF) for unsigned overflow */
        jnc     end
        /* if overflow then return max uint32_t = 2^32 - 1 = 4294967295*/
        movl    $4294967295, %eax
        /* %eax is used to return result */
end:
        /* standard epilogue */
        popl    %ebp
        ret

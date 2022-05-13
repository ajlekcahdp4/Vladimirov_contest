function:
.LFB0:
        .cfi_startproc
        push    ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        mov     ebp, esp
        .cfi_def_cfa_register 5
        mov     eax, DWORD PTR [ebp+8]
        sal     eax, 5
        sub     eax, DWORD PTR [ebp+8]
        mov     esp, ebp
        pop     ebp
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc
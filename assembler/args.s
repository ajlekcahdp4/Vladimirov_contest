	.file	"args.c"
	.intel_syntax noprefix
	.text
	.globl	foo
	.type	foo, @function
foo:
.LFB0:
	.cfi_startproc
	add	r9d, DWORD PTR 8[rsp]
	add	r9d, DWORD PTR 16[rsp]
	add	r9d, r8d
	add	r9d, ecx
	movsx	edi, dil
	movsx	esi, si
	add	edi, esi
	add	edi, edx
	lea	eax, [r9+rdi]
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
	.ident	"GCC: (GNU) 11.2.0"
	.section	.note.GNU-stack,"",@progbits

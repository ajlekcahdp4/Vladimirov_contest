	.file	"optimize.c"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	foo
	.type	foo, @function
foo:
.LFB0:
	.cfi_startproc
	mov	ecx, edi
	imul	ecx, edi
	mov	eax, ecx
	lea	edx, 0[0+rcx*8]
	imul	eax, edi
	sub	edx, ecx
	lea	eax, [rax+rax*2]
	add	eax, edx
	lea	eax, 1[rax+rdi*2]
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
	.ident	"GCC: (GNU) 11.2.0"
	.section	.note.GNU-stack,"",@progbits

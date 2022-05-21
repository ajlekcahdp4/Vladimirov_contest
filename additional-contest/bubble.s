	.file	"bubble.c"
	.intel_syntax noprefix
	.text
	.globl	bsort
	.type	bsort, @function
bsort:
.LFB0:
	.cfi_startproc
	test	esi, esi
	jle	.L1
	movsx	rax, esi
	lea	rcx, [rdi+rax*4]
	jmp	.L6
.L9:
	mov	DWORD PTR [rax], edx
.L4:
	add	rax, 4
	cmp	rax, rcx
	je	.L3
.L5:
	mov	edx, DWORD PTR 4[rax]
	cmp	DWORD PTR [rax], edx
	jle	.L4
	jmp	.L9
.L3:
	sub	rcx, 4
	sub	esi, 1
	je	.L1
.L6:
	test	esi, esi
	jle	.L3
	mov	rax, rdi
	jmp	.L5
.L1:
	ret
	.cfi_endproc
.LFE0:
	.size	bsort, .-bsort
	.ident	"GCC: (GNU) 11.2.0"
	.section	.note.GNU-stack,"",@progbits

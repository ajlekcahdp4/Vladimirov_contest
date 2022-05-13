
	.intel_syntax noprefix
	.text
	.p2align 4,,15
	.globl	calc
	.type	calc, @function
calc:
.LFB0:
	.cfi_startproc
	sub	rsp, 24
	.cfi_def_cfa_offset 32
	cmp	edi, 3
	je	.L3
	cmp	edi, 4
	je	.L4
	cvtss2sd	xmm0, xmm0
	call	log@PLT
	pxor	xmm1, xmm1
	cvtsd2ss	xmm1, xmm0
.L1:
	add	rsp, 24
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	movaps	xmm0, xmm1
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	.cfi_restore_state
	pxor	xmm2, xmm2
	sqrtss	xmm1, xmm0
	ucomiss	xmm2, xmm0
	jbe	.L1
	movss	DWORD PTR 12[rsp], xmm1
	call	sqrtf@PLT
	movss	xmm1, DWORD PTR 12[rsp]
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L3:
	cvtss2sd	xmm0, xmm0
	call	cos@PLT
	pxor	xmm1, xmm1
	add	rsp, 24
	.cfi_def_cfa_offset 8
	cvtsd2ss	xmm1, xmm0
	movaps	xmm0, xmm1
	ret
	.cfi_endproc
.LFE0:
	.size	calc, .-calc
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits

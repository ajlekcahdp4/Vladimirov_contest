
	.text
	.p2align 4,,15
	.globl	calc
	.type	calc, @function
calc:
.LFB0:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	cmpl	$3, %edi
	je	.L3
	cmpl	$4, %edi
	je	.L4
	cvtss2sd	%xmm0, %xmm0
	call	log@PLT
	pxor	%xmm1, %xmm1
	cvtsd2ss	%xmm0, %xmm1
.L1:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	movaps	%xmm1, %xmm0
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	.cfi_restore_state
	pxor	%xmm2, %xmm2
	sqrtss	%xmm0, %xmm1
	ucomiss	%xmm0, %xmm2
	jbe	.L1
	movss	%xmm1, 12(%rsp)
	call	sqrtf@PLT
	movss	12(%rsp), %xmm1
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L3:
	cvtss2sd	%xmm0, %xmm0
	call	cos@PLT
	pxor	%xmm1, %xmm1
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	cvtsd2ss	%xmm0, %xmm1
	movaps	%xmm1, %xmm0
	ret
	.cfi_endproc
.LFE0:
	.size	calc, .-calc
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits

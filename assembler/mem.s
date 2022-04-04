	.file	"mem.c"
	.intel_syntax noprefix
	.text
	.globl	foo
	.type	foo, @function
foo:
.LFB0:
	.cfi_startproc
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	add	rsp, -128
	.cfi_def_cfa_offset 144
	mov	ebx, edi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR 120[rsp], rax
	xor	eax, eax
	lea	rdi, 32[rsp]
	call	fill@PLT
	mov	rdi, rsp
	mov	eax, 0
	call	fill@PLT
	lea	rdi, 80[rsp]
	mov	eax, 0
	call	fill@PLT
	movsx	rdi, ebx
	mov	eax, DWORD PTR 32[rsp+rdi*4]
	add	eax, DWORD PTR [rsp+rdi*4]
	add	eax, DWORD PTR 80[rsp]
	mov	rdx, QWORD PTR 120[rsp]
	sub	rdx, QWORD PTR fs:40
	jne	.L4
	sub	rsp, -128
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
.L4:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
	.globl	bar
	.type	bar, @function
bar:
.LFB1:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	push	rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	sub	rsp, 40
	.cfi_def_cfa_offset 64
	mov	rbp, rdi
	mov	ebx, esi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR 24[rsp], rax
	xor	eax, eax
	mov	rdi, rsp
	call	fill@PLT
	movsx	rsi, ebx
	mov	eax, DWORD PTR [rsp+rsi*4]
	add	eax, DWORD PTR 0[rbp+rsi*4]
	mov	rdx, QWORD PTR 24[rsp]
	sub	rdx, QWORD PTR fs:40
	jne	.L8
	add	rsp, 40
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	pop	rbx
	.cfi_def_cfa_offset 16
	pop	rbp
	.cfi_def_cfa_offset 8
	ret
.L8:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE1:
	.size	bar, .-bar
	.globl	buz
	.type	buz, @function
buz:
.LFB2:
	.cfi_startproc
	movsx	rdi, edi
	lea	rdx, garr[rip]
	mov	eax, DWORD PTR a[rip]
	add	eax, DWORD PTR [rdx+rdi*4]
	mov	rdx, QWORD PTR gp[rip]
	add	eax, DWORD PTR [rdx+rdi*4]
	ret
	.cfi_endproc
.LFE2:
	.size	buz, .-buz
	.globl	a
	.bss
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.zero	4
	.globl	gp
	.align 8
	.type	gp, @object
	.size	gp, 8
gp:
	.zero	8
	.globl	garr
	.align 16
	.type	garr, @object
	.size	garr, 20
garr:
	.zero	20
	.ident	"GCC: (GNU) 11.2.0"
	.section	.note.GNU-stack,"",@progbits

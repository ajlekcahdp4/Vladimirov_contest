    .intel_syntax noprefix
	.text
	.globl	foo
	.type	foo, @function

foo:
	mov	DWORD PTR -16[rsp], 2
	mov	DWORD PTR -12[rsp], 0
	mov	DWORD PTR -8[rsp], 6
	mov	DWORD PTR -4[rsp], 4
	mov	r9d, DWORD PTR 8[rdi]
	lea	rax, -16[rsp]
	lea	r8, -4[rsp]
.L2:
	movsx	rdx, DWORD PTR 4[rax]
	mov	ecx, DWORD PTR [rdi+rdx*4]
	movsx	rdx, DWORD PTR [rax]
	mov	DWORD PTR [rdi+rdx*4], ecx
	add	rax, 4
	cmp	rax, r8
	jne	.L2
	mov	DWORD PTR 16[rdi], r9d
	cmp	esi, 1
	jle	.L1
	lea	rax, 4[rdi]
	lea	edx, -2[rsi]
	lea	rcx, 8[rdi+rdx*4]
.L4:
	mov	edx, DWORD PTR -4[rax]
	add	DWORD PTR [rax], edx
	add	rax, 4
	cmp	rax, rcx
	jne	.L4
.L1:
	ret

	.intel_syntax noprefix
	.text
	.globl	sortfn
	.type	sortfn, @function
sortfn:
	endbr64
	lea	r8d, -1[rsi]
	test	r8d, r8d
	jle	.L1
	lea	r9, 4[rdi]
	jmp	.L3
.L4:
	add	rax, 4
	cmp	rax, rsi
	je	.L7
.L5:
// ---------
    mov	r10d, DWORD PTR 4[rax]
	cmp	DWORD PTR [rax], r10d
	jle	.L4
    mov	r11d, DWORD PTR [rax]
    mov DWORD PTR [rax], r10d
    mov DWORD PTR 4[rax], r11d
// ---------
    jmp	.L4
.L7:
	sub	r8d, 1
	je	.L1
.L3:
	test	r8d, r8d
	jle	.L7
	mov	rax, rdi
	lea	edx, -1[r8]
	lea	rsi, [r9+rdx*4]
	jmp	.L5
.L1:
	ret
  .intel_syntax noprefix
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LMC0:
	.string	"%d"
.LMC1:
	.string	"%d "
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
	endbr64
	push	r12
	xor	eax, eax
	lea	rdi, .LMC0[rip]
	push	rbp
	push	rbx
	sub	rsp, 16
	lea	rsi, 12[rsp]
	call	__isoc99_scanf@PLT
	dec	eax
	je	.LM2
.LM3:
	call	abort@PLT
.LM2:
	movsx	rdi, DWORD PTR 12[rsp]
	xor	ebp, ebp
	lea	r12, .LMC0[rip]
	sal	rdi, 2
	call	malloc@PLT
	mov	rbx, rax
	test	rax, rax
	je	.LM3
.LM4:
	mov	esi, DWORD PTR 12[rsp]
	cmp	esi, ebp
	jle	.LM13
	lea	rsi, [rbx+rbp*4]
	xor	eax, eax
	mov	rdi, r12
	inc	rbp
	call	__isoc99_scanf@PLT
	dec	eax
	je	.LM4
	jmp	.LM3
.LM13:
	mov	rdi, rbx
	xor	ebp, ebp
	lea	r12, .LMC1[rip]
	call	sortfn@PLT
.LM6:
	cmp	DWORD PTR 12[rsp], ebp
	jle	.LM14
	mov	edx, DWORD PTR [rbx+rbp*4]
	mov	rsi, r12
	mov	edi, 1
	xor	eax, eax
	inc	rbp
	call	__printf_chk@PLT
	jmp	.LM6
.LM14:
	mov	edi, 10
	call	putchar@PLT
	add	rsp, 16
	xor	eax, eax
	pop	rbx
	pop	rbp
	pop	r12
	ret
	.size	main, .-main

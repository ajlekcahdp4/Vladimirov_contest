	.file	"crackme.c"
	.intel_syntax noprefix
	.text
	.globl	foo
	.type	foo, @function
foo:
	endbr64
	mov	rax, QWORD PTR [rsp]
	ret
	.size	foo, .-foo
	.globl	buz
	.type	buz, @function
buz:
	endbr64
	cmp	edi, esi
	jne	.L7
	ret
.L7:
	sub	rsp, 8
	mov	edi, -1
	call	exit@PLT
	.size	buz, .-buz
	.globl	bar
	.type	bar, @function
bar:
	endbr64
	push	r12
	push	rbp
	push	rbx
	mov	r12d, edi
	mov	eax, 0
	call	foo
	mov	ebx, 0
	mov	ebp, 0
	mov	esi, 0
	mov	r9d, 0
	mov	r8d, 0
.L11:
	movzx	ecx, BYTE PTR [rax]
	movzx	edi, cl
	mov	edx, edi
	sal	edx, 4
	add	edx, edi
	add	r8d, edx
	cmp	cl, -24
	sete	dl
	movzx	edx, dl
	add	esi, edx
	add	rax, 1
	cmp	esi, 2
	je	.L10
	lea	ebp, 17[rbx]
	lea	ebx, -17[r9]
	mov	r9d, ecx
	jmp	.L11
.L10:
	mov	esi, r12d
	mov	edi, r8d
	call	buz
	movzx	ebp, bpl
	movzx	eax, bl
	sal	eax, 8
	lea	eax, [rax+rbp]
	pop	rbx
	pop	rbp
	pop	r12
	ret
	.size	bar, .-bar
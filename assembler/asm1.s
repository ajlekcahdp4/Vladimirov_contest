; // --- on entry edi = x (unsigned) ---
; // --- returns 1 if prime, 0 if composite ---
start:
	mov	eax, 0
	cmp	edi, 1
	jbe	composite
	cmp	edi, 3
	jbe	prime
	test	dil, 1
	je	composite
	mov	ecx, 2

loop:

;// --- Here something missing ---

  jne     loop

composite:
  mov     eax, 0
  ret
prime:
  mov     eax, 1
  ret
GLOBAL cpuVendor
GLOBAL getRTC
GLOBAL canReadKeyboard
GLOBAL readFromKeyboard
GLOBAL test

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

getRTC:
	push rbp
	mov rbp, rsp

	mov al, dil		;uso la parte baja
	out 70h, al
	in al, 71h

	movzx rax, al	;lleno con ceros

	mov rsp, rbp
	pop rbp
	ret

canReadKeyboard:
	push rbp
	mov rbp, rsp

	xor rax, rax
	in al, 64h		;veo si el teclado se presiono

	and al, 1 		;mascara para el 1er bit
	
	movzx rax, al	;lleno rax con ceros

	mov rsp, rbp
	pop rbp
	ret

readFromKeyboard:
	push rbp
	mov rbp, rsp

	xor rax, rax

	in al, 60h
	;test al, 80h
	;jnz .nodata
	movzx rax, al
	jmp .fin

.nodata:
	xor rax, rax

.fin:
	mov rsp, rbp
	pop rbp
	ret


test:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, rdi
	mov rbx, rsi
	xchg rdx, rcx  
	int 80h

	pop rbx
	leave
	ret
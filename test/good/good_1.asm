struc mystruct
	.max resb 4
	.min resb 4
endstruc

section .data
	format_int db '%d', 0
	format_char db '%c', 0

section .bss
	max resb 4
	r2 resb 4
	r1 resb 4

section .text
global valeur
global trinome
global main
global print
global reade
global readc
extern printf
extern scanf

print :
	push rbp
	mov rbp, rsp
	mov rax, rsi
	mov rsi, rdi
	cmp rax, 4
	jne L0
	mov rdi, format_int
	jmp L1
L0:
	mov rdi, format_char
L1:
	mov rax, 0
	mov r14, rsp
	and rsp, -16
	call printf
	mov rsp, r14
	pop rbp
	ret

reade :
	push rbp
	mov rbp, rsp
	mov rsi, rdi
	mov rdi, format_int
	mov rax, 0
	mov r14, rsp
	and rsp, -16
	call scanf
	mov rsp, r14
	pop rbp
	ret

readc :
	push rbp
	mov rbp, rsp
	mov rsi, rdi
	mov rdi, format_char
	mov rax, 0
	mov r14, rsp
	and rsp, -16
	call scanf
	mov rsp, r14
	pop rbp
	ret

main :
	push rbp
	mov rbp, rsp
	sub rsp, 24

	xor rax, rax
	mov eax, 1
	push rax
	push rax
	pop rbx
	pop rax
	sub eax, ebx

	mov dword [rbp - 16 - 4], eax
	xor rax, rax
	mov eax, 3
	mov qword [rbp - 0 - 8 + mystruct.max], rax
	xor rax, rax
	mov eax, dword [rbp - 20 - 4]

	push rax
	xor rax, rax
	mov eax, dword [rbp - 16 - 4]

	push rax
	pop rbx
	pop rax
	add eax, ebx

L2:
	xor rax, rax
	mov eax, dword [rbp - 16 - 4]

	push rax
	xor rax, rax
	mov eax, 1
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jle L3
L4:
	mov rax, 0
	jmp L5
L3:
	mov rax, 1
	jmp L5
L5:
	cmp rax, 0
	je L6
	xor rax, rax
	mov eax, 1
	push rax
	push rax
	pop rbx
	pop rax
	sub eax, ebx

	mov dword [rbp - 20 - 4], eax
L7:
	xor rax, rax
	mov eax, dword [rbp - 20 - 4]

	push rax
	xor rax, rax
	mov eax, 1
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jle L8
L9:
	mov rax, 0
	jmp L10
L8:
	mov rax, 1
	jmp L10
L10:
	cmp rax, 0
	je L11
	xor rax, rax
	mov eax, dword [rbp - 16 - 4]

	mov rdi, rax
	mov rsi, 4
	call print
	xor rax, rax
	mov eax, 1
	mov rdi, rax
	xor rax, rax
	mov eax, dword [rbp - 16 - 4]

	mov rsi, rax
	xor rax, rax
	mov eax, dword [rbp - 20 - 4]

	mov rdx, rax
	call trinome
	cmp rax, 0
	je L12
	xor rax, rax
	mov eax, dword [r1]

	mov rdi, rax
	mov rsi, 4
	call print
	xor rax, rax
	mov eax, dword [r2]

	mov rdi, rax
	mov rsi, 4
	call print
	xor rax, rax
	mov eax, 0
	push rax
	xor rax, rax
	mov eax, dword [r1]

	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jle L13
L14:
	mov rax, 0
	jmp L15
L13:
	mov rax, 1
	jmp L15
L15:
	cmp rax, 0
	je L16
	xor rax, rax
	mov eax, dword [r1]

	push rax
	xor rax, rax
	mov eax, dword [max]

	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jle L17
L18:
	mov rax, 0
	jmp L19
L17:
	mov rax, 1
	jmp L19
L19:
L16:
	cmp rax, 0
	je L20
	xor rax, rax
	mov eax, 0
	push rax
	xor rax, rax
	mov eax, dword [r2]

	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jge L21
L22:
	mov rax, 0
	jmp L23
L21:
	mov rax, 1
	jmp L23
L23:
L20:
	cmp rax, 0
	je L24
	xor rax, rax
	mov eax, dword [r2]

	push rax
	xor rax, rax
	mov eax, dword [max]

	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jge L25
L26:
	mov rax, 0
	jmp L27
L25:
	mov rax, 1
	jmp L27
L27:
L24:
	cmp rax, 0
	je L28
	xor rax, rax
	mov eax, 0
	add rsp, 24 + 0

	pop rbp

	mov rdi, rax
	mov rax, 60
	syscall
	jmp L29
L28:
L29:
	jmp L30
L12:
L30:
	xor rax, rax
	mov eax, dword [rbp - 20 - 4]

	push rax
	xor rax, rax
	mov eax, 1
	push rax
	pop rbx
	pop rax
	add eax, ebx

	mov dword [rbp - 20 - 4], eax
	jmp L7
L11:
	xor rax, rax
	mov eax, dword [rbp - 16 - 4]

	push rax
	xor rax, rax
	mov eax, 1
	push rax
	pop rbx
	pop rax
	add eax, ebx

	mov dword [rbp - 16 - 4], eax
	jmp L2
L6:
	xor rax, rax
	mov eax, 0
	add rsp, 24 + 0

	pop rbp

	mov rdi, rax
	mov rax, 60
	syscall

trinome :
	push rbp
	mov rbp, rsp
	sub rsp, 8

	xor rax, rax
	mov rax, rsi

	push rax
	xor rax, rax
	mov rax, rsi

	push rax
	pop rbx
	pop rax
	imul eax, ebx

	push rax
	xor rax, rax
	mov eax, 4
	push rax
	xor rax, rax
	mov rax, rdi

	push rax
	pop rbx
	pop rax
	imul eax, ebx

	push rax
	xor rax, rax
	mov rax, rdx

	push rax
	pop rbx
	pop rax
	imul eax, ebx

	push rax
	pop rbx
	pop rax
	sub eax, ebx

	mov dword [rbp - 0 - 4], eax
	xor rax, rax
	mov eax, dword [rbp - 0 - 4]

	push rax
	xor rax, rax
	mov eax, 0
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	jge L31
L32:
	mov rax, 0
	jmp L33
L31:
	mov rax, 1
	jmp L33
L33:
	cmp rax, 0
	je L34
	xor rax, rax
	mov rax, rsi

	push rax
	push rax
	pop rbx
	pop rax
	sub eax, ebx

	push rax
	xor rax, rax
	mov eax, dword [rbp - 4 - 4]

	push rax
	pop rbx
	pop rax
	add eax, ebx

	push rax
	xor rax, rax
	mov eax, 2
	push rax
	xor rax, rax
	mov rax, rdi

	push rax
	pop rbx
	pop rax
	imul eax, ebx

	push rax
	pop rbx
	pop rax
	xor rdx, rdx
	idiv ebx

	mov dword [r1], eax
	xor rax, rax
	mov rax, rsi

	push rax
	push rax
	pop rbx
	pop rax
	sub eax, ebx

	push rax
	xor rax, rax
	mov eax, dword [rbp - 4 - 4]

	push rax
	pop rbx
	pop rax
	sub eax, ebx

	push rax
	xor rax, rax
	mov eax, 2
	push rax
	xor rax, rax
	mov rax, rdi

	push rax
	pop rbx
	pop rax
	imul eax, ebx

	push rax
	pop rbx
	pop rax
	xor rdx, rdx
	idiv ebx

	mov dword [r2], eax
	xor rax, rax
	mov eax, 1
	add rsp, 8 + 0

	pop rbp

	ret
	jmp L35
L34:
L35:
	xor rax, rax
	mov eax, 0
	add rsp, 8 + 0

	pop rbp

	ret

valeur :
	push rbp
	mov rbp, rsp
	sub rsp, 0

	xor rax, rax
	mov rax, rdi

	push rax
	xor rax, rax
	mov rax, rcx

	push rax
	pop rbx
	pop rax
	imul eax, ebx

	push rax
	xor rax, rax
	mov rax, rcx

	push rax
	pop rbx
	pop rax
	imul eax, ebx

	push rax
	xor rax, rax
	mov rax, rsi

	push rax
	xor rax, rax
	mov rax, rcx

	push rax
	pop rbx
	pop rax
	imul eax, ebx

	push rax
	pop rbx
	pop rax
	add eax, ebx

	push rax
	xor rax, rax
	mov rax, rdx

	push rax
	pop rbx
	pop rax
	add eax, ebx

	add rsp, 0 + 0

	pop rbp

	ret

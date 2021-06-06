struc my_struct
	.a resb 4
	.b resb 1
endstruc

section .data
	format_int db '%d', 0
	format_char db '%c', 0

section .bss

section .text
global main
global fast
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

fast :
	push rbp
	mov rbp, rsp
	sub rsp, 16

	xor rax, rax
	mov eax, 8
	mov qword [rbp - 8 - 8 + my_struct.b], rax
	xor rax, rax
	mov rax, qword [rbp - 0 - 8 + my_struct.a]

	add rsp, 16 + 0

	pop rbp

	ret

main :
	push rbp
	mov rbp, rsp
	sub rsp, 4

	xor rax, rax
	mov eax, dword [rbp - 0 - 4]

	mov rdi, rax
	call fast
	xor rax, rax
	mov eax, 0
	add rsp, 4 + 0

	pop rbp

	mov rdi, rax
	mov rax, 60
	syscall

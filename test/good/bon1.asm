struc my_struct
	.a resb 4
	.b resb 1
endstruc

section .data
	format_int db '%d', 0
	format_char db '%c', 0

section .bss
	li resb 8
	la resb 8
	h resb 4

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
	sub rsp, 20

	xor rax, rax
	mov rax, qword [rbp - 0 - 8 + my_struct.a]

	mov dword [rbp - 16 - 4], eax
	xor rax, rax
	mov rax, qword [rbp - 0 - 8 + my_struct.b]

	mov qword [rbp - 0 - 8 + my_struct.b], rax
	xor rax, rax
	mov eax, 3
	mov qword [rbp - 8 - 8 + my_struct.a], rax
	xor rax, rax
	mov rax, qword [rbp - 0 - 8 + my_struct.a]

	mov rdi, rax
	mov rsi, 4
	call print
	mov rbx, rsp
	sub rsp, 8
	mov eax, dword [rbp - 8 - 8 + my_struct.a]
	mov dword [rsp + my_struct.a], eax
	mov al, byte [rbp - 8 - 8 + my_struct.b]
	mov byte [rsp + my_struct.b], al
	mov rax, rbx
	mov rbx, rax
	mov eax, dword [rbx + my_struct.a]
	mov dword [rbp - 0 - 8 + my_struct.a], eax
	mov al, byte [rbx + my_struct.b]
	mov byte [rbp - 0 - 8 + my_struct.b], al
	add rsp, 8
	xor rax, rax
	mov eax, dword [rbp - 16 - 4]

	push rax
	xor rax, rax
	mov ax, 'a'
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	je L2
L3:
	mov rax, 0
	jmp L4
L2:
	mov rax, 1
	jmp L4
L4:
	cmp rax, 0
	je L5
	xor rax, rax
	mov eax, dword [h]

	mov rsi, rax
	jmp L6
L5:
	xor rax, rax
	mov eax, dword [h]

	mov rsi, rax
L6:
	mov rax, rsi
	mov rdi, rax
	call reade
	xor rax, rax
	mov eax, 0
	add rsp, 20 + 0

	pop rbp

	ret
	xor rax, rax
	mov eax, 1
	xor rax, rax
	mov ax, 'a'
	mov rbx, rsp
	sub rsp, 8
	mov eax, dword [rbp - 0 - 8 + my_struct.a]
	mov dword [rsp + my_struct.a], eax
	mov al, byte [rbp - 0 - 8 + my_struct.b]
	mov byte [rsp + my_struct.b], al
	mov rax, rbx

main :
	push rbp
	mov rbp, rsp
	sub rsp, 13

	xor rax, rax
	mov ax, 'a'
	mov byte [rbp - 12 - 1], al
	xor rax, rax
	mov eax, 5
	mov dword [rbp - 0 - 4], eax
	xor rax, rax
	mov eax, dword [rbp - 0 - 4]

	mov rdi, rax
	xor rax, rax
	mov eax, dword [rbp - 4 - 4]

	mov rsi, rax
	xor rax, rax
	mov eax, dword [rbp - 8 - 4]

	mov rdx, rax
	call fast
	xor rax, rax
	mov ax, 'g'
	mov qword [la + my_struct.b], rax
	xor rax, rax
	mov eax, dword [rbp - 0 - 4]

	push rax
	xor rax, rax
	mov eax, dword [rbp - 0 - 4]

	push rax
	pop rbx
	pop rax
	imul eax, ebx

	push rax
	xor rax, rax
	mov ax, 'a'
	push rax
	pop rbx
	pop rax
	cmp rax, rbx
	je L7
L8:
	mov rax, 0
	jmp L9
L7:
	mov rax, 1
	jmp L9
L9:
	cmp rax, 0
	je L10
	xor rax, rax
	mov ax, 'n'
	mov byte [rbp - 12 - 1], al
	jmp L11
L10:
L11:
	xor rax, rax
	mov eax, 0
	add rsp, 13 + 8

	pop rbp

	mov rdi, rax
	mov rax, 60
	syscall

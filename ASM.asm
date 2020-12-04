.486
.MODEL FLAT, STDCALL
includelib kernel32.lib
includelib libucrt.lib
includelib C:\Users\User\Desktop\LP\Lab\LPLab14\Debug\userLib.lib

ExitProcess PROTO, :DWORD
EXTRN copyStr: proc
EXTRN outint: proc
EXTRN outstr: proc
EXTRN concatStr: proc

.STACK 4096
.DATA
	main_n		SDWORD	0
	main_a		SDWORD	0
.CONST
	main_Lex4	SDWORD	4
	main_Lex5	SDWORD	2
	main_Lex6	SDWORD	0
.CODE
START:
	push main_Lex4
	pop eax
	mov main_a, eax
	inc main_a
	push main_a
	call outint
	dec main_a
	push main_a
	call outint
	push main_a
	pop eax
	inc eax
	push eax
	push main_Lex5
	pop ebx
	pop eax
	mul ebx
	push eax
	push main_a
	pop eax
	dec eax
	push eax
	pop ebx
	pop eax
	sub eax, ebx
	 push eax
	pop eax
	mov main_n, eax
	push main_n
	call outint
	push main_Lex6
	call ExitProcess
END START

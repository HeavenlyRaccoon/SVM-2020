.486
.MODEL FLAT, STDCALL
includelib kernel32.lib
includelib libucrt.lib
includelib C:\Users\User\Desktop\LP\Lab\LPLab14\Debug\userLib.lib

ExitProcess PROTO, :DWORD
EXTRN copyStr: proc
EXTRN outint: proc
EXTRN outlineint: proc
EXTRN outstr: proc
EXTRN outlinestr: proc
EXTRN concatStr: proc
EXTRN len: proc
EXTRN ctoi: proc

.STACK 4096
.DATA
	main_a		SDWORD	0
	main_b		SDWORD	0
.CONST
	main_Lex3	SDWORD	60
	main_Lex5	SDWORD	6
	main_Lex6	SDWORD	0
.CODE
START:
	push main_Lex3
	pop eax
	mov main_a, eax
	push main_a
	push main_Lex5
	pop eax
	pop ebx
	add eax, ebx
	 push eax
	pop eax
	mov main_b, eax
	push main_b
	mov ebx, ecx
	call outint
	mov ecx, ebx
	push main_Lex6
	call ExitProcess
END START

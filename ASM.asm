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
	Show_snum	BYTE 255 DUP(0)
	Show_sums	BYTE 255 DUP(0)
	main_s	BYTE 255 DUP(0)
.CONST
	Show_Lex5	BYTE	"10",0
	main_Lex9	BYTE	"Number is ",0
	main_Lex10	SDWORD	10
	main_Lex11	SDWORD	0
.CODE
Show PROC Show_str: DWORD, Show_num: SDWORD
	push offset Show_Lex5
	push offset Show_snum
	call copyStr
	push [Show_str]
	push offset Show_snum
	call concatStr
	push eax
	push offset Show_sums
	call copyStr
	mov eax, offset Show_sums
	ret
Show ENDP
START:
	push main_Lex10
	push offset main_Lex9
	call Show
	push eax
	push offset main_s
	call copyStr
	push offset main_s
	call outstr
	push main_Lex11
	call ExitProcess
END START

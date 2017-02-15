
	TITLE	D:\study\system\assembly\src\helloc.c
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

_DATA	SEGMENT
$SG4505	DB	'a=%d, b=%d', 0aH, 00H
_DATA	ENDS
PUBLIC	___local_stdio_printf_options
PUBLIC	__vfprintf_l
PUBLIC	_printf
PUBLIC	@print_int@8
PUBLIC	_main
EXTRN	___acrt_iob_func:PROC
EXTRN	___stdio_common_vfprintf:PROC
_DATA	SEGMENT
COMM	?_OptionsStorage@?1??__local_stdio_printf_options@@9@9:QWORD							; `__local_stdio_printf_options'::`2'::_OptionsStorage
_DATA	ENDS
_TEXT	SEGMENT
_main	PROC
	push	ebp
	mov	ebp, esp
	mov	edx, 2
	mov	ecx, 1
	call	@print_int@8
	xor	eax, eax
	pop	ebp
	ret	0
_main	ENDP
_TEXT	ENDS
_TEXT	SEGMENT
_b$ = -8						; size = 4
_a$ = -4						; size = 4
@print_int@8 PROC
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	mov	DWORD PTR _b$[ebp], edx
	mov	DWORD PTR _a$[ebp], ecx
	mov	eax, DWORD PTR _b$[ebp]
	push	eax
	mov	ecx, DWORD PTR _a$[ebp]
	push	ecx
	push	OFFSET $SG4505
	call	_printf
	add	esp, 12					; 0000000cH
	mov	eax, DWORD PTR _a$[ebp]
	add	eax, DWORD PTR _b$[ebp]
	mov	esp, ebp
	pop	ebp
	ret	0
@print_int@8 ENDP
_TEXT	ENDS
_TEXT	SEGMENT
__Result$ = -8						; size = 4
__ArgList$ = -4						; size = 4
__Format$ = 8						; size = 4
_printf	PROC						; COMDAT
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	lea	eax, DWORD PTR __Format$[ebp+4]
	mov	DWORD PTR __ArgList$[ebp], eax
	mov	ecx, DWORD PTR __ArgList$[ebp]
	push	ecx
	push	0
	mov	edx, DWORD PTR __Format$[ebp]
	push	edx
	push	1
	call	___acrt_iob_func
	add	esp, 4
	push	eax
	call	__vfprintf_l
	add	esp, 16					; 00000010H
	mov	DWORD PTR __Result$[ebp], eax
	mov	DWORD PTR __ArgList$[ebp], 0
	mov	eax, DWORD PTR __Result$[ebp]
	mov	esp, ebp
	pop	ebp
	ret	0
_printf	ENDP
_TEXT	ENDS
_TEXT	SEGMENT
__Stream$ = 8						; size = 4
__Format$ = 12						; size = 4
__Locale$ = 16						; size = 4
__ArgList$ = 20						; size = 4
__vfprintf_l PROC					; COMDAT
	push	ebp
	mov	ebp, esp
	mov	eax, DWORD PTR __ArgList$[ebp]
	push	eax
	mov	ecx, DWORD PTR __Locale$[ebp]
	push	ecx
	mov	edx, DWORD PTR __Format$[ebp]
	push	edx
	mov	eax, DWORD PTR __Stream$[ebp]
	push	eax
	call	___local_stdio_printf_options
	mov	ecx, DWORD PTR [eax+4]
	push	ecx
	mov	edx, DWORD PTR [eax]
	push	edx
	call	___stdio_common_vfprintf
	add	esp, 24					; 00000018H
	pop	ebp
	ret	0
__vfprintf_l ENDP
_TEXT	ENDS
_TEXT	SEGMENT
___local_stdio_printf_options PROC			; COMDAT
	push	ebp
	mov	ebp, esp
	mov	eax, OFFSET ?_OptionsStorage@?1??__local_stdio_printf_options@@9@9 ; `__local_stdio_printf_options'::`2'::_OptionsStorage
	pop	ebp
	ret	0
___local_stdio_printf_options ENDP
_TEXT	ENDS
END

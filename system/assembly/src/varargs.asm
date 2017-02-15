
	TITLE	D:\study\system\assembly\src\varargs.c
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

_DATA	SEGMENT
$SG6934	DB	'Helloc', 00H
	ORG $+1
$SG6935	DB	'this a test:%d %s', 0aH, 00H
_DATA	ENDS
PUBLIC	___local_stdio_printf_options
PUBLIC	__vfprintf_l
PUBLIC	_fprintf
PUBLIC	_vsnprintf
PUBLIC	_my_print
PUBLIC	_main
EXTRN	___acrt_iob_func:PROC
EXTRN	___stdio_common_vfprintf:PROC
EXTRN	___stdio_common_vsprintf:PROC
EXTRN	_free:PROC
EXTRN	_malloc:PROC
_DATA	SEGMENT
COMM	?_OptionsStorage@?1??__local_stdio_printf_options@@9@9:QWORD							; `__local_stdio_printf_options'::`2'::_OptionsStorage
_DATA	ENDS
_TEXT	SEGMENT
_main	PROC
	push	ebp
	mov	ebp, esp
	push	OFFSET $SG6934
	push	8888					; 000022b8H
	push	OFFSET $SG6935
	push	1
	call	_my_print
	add	esp, 16					; 00000010H
	xor	eax, eax
	pop	ebp
	ret	0
_main	ENDP
_TEXT	ENDS
_TEXT	SEGMENT
_ap$ = -12						; size = 4
_p$ = -8						; size = 4
_size$ = -4						; size = 4
_code$ = 8						; size = 4
_fmt$ = 12						; size = 4
_my_print PROC
	push	ebp
	mov	ebp, esp
	sub	esp, 12					; 0000000cH
	mov	DWORD PTR _p$[ebp], 0
	mov	DWORD PTR _size$[ebp], 0
	lea	eax, DWORD PTR _fmt$[ebp+4]
	mov	DWORD PTR _ap$[ebp], eax
	mov	ecx, DWORD PTR _ap$[ebp]
	push	ecx
	mov	edx, DWORD PTR _fmt$[ebp]
	push	edx
	mov	eax, DWORD PTR _size$[ebp]
	push	eax
	mov	ecx, DWORD PTR _p$[ebp]
	push	ecx
	call	_vsnprintf
	add	esp, 16					; 00000010H
	mov	DWORD PTR _size$[ebp], eax
	cmp	DWORD PTR _size$[ebp], 0
	jle	SHORT $LN2@my_print
	mov	edx, DWORD PTR _size$[ebp]
	push	edx
	call	_malloc
	add	esp, 4
	mov	DWORD PTR _p$[ebp], eax
	jmp	SHORT $LN3@my_print
$LN2@my_print:
	or	eax, -1
	jmp	SHORT $LN1@my_print
$LN3@my_print:
	mov	eax, DWORD PTR _ap$[ebp]
	push	eax
	mov	ecx, DWORD PTR _fmt$[ebp]
	push	ecx
	mov	edx, DWORD PTR _size$[ebp]
	push	edx
	mov	eax, DWORD PTR _p$[ebp]
	push	eax
	call	_vsnprintf
	add	esp, 16					; 00000010H
	mov	ecx, DWORD PTR _p$[ebp]
	push	ecx
	push	1
	call	___acrt_iob_func
	add	esp, 4
	push	eax
	call	_fprintf
	add	esp, 8
	mov	edx, DWORD PTR _p$[ebp]
	push	edx
	call	_free
	add	esp, 4
	mov	DWORD PTR _ap$[ebp], 0
	mov	eax, DWORD PTR _code$[ebp]
$LN1@my_print:
	mov	esp, ebp
	pop	ebp
	ret	0
_my_print ENDP
_TEXT	ENDS
_TEXT	SEGMENT
tv74 = -8						; size = 4
__Result$ = -4						; size = 4
__Buffer$ = 8						; size = 4
__BufferCount$ = 12					; size = 4
__Format$ = 16						; size = 4
__ArgList$ = 20						; size = 4
_vsnprintf PROC						; COMDAT
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	mov	eax, DWORD PTR __ArgList$[ebp]
	push	eax
	push	0
	mov	ecx, DWORD PTR __Format$[ebp]
	push	ecx
	mov	edx, DWORD PTR __BufferCount$[ebp]
	push	edx
	mov	eax, DWORD PTR __Buffer$[ebp]
	push	eax
	call	___local_stdio_printf_options
	mov	ecx, DWORD PTR [eax]
	or	ecx, 2
	mov	edx, DWORD PTR [eax+4]
	push	edx
	push	ecx
	call	___stdio_common_vsprintf
	add	esp, 28					; 0000001cH
	mov	DWORD PTR __Result$[ebp], eax
	cmp	DWORD PTR __Result$[ebp], 0
	jge	SHORT $LN3@vsnprintf
	mov	DWORD PTR tv74[ebp], -1
	jmp	SHORT $LN4@vsnprintf
$LN3@vsnprintf:
	mov	eax, DWORD PTR __Result$[ebp]
	mov	DWORD PTR tv74[ebp], eax
$LN4@vsnprintf:
	mov	eax, DWORD PTR tv74[ebp]
	mov	esp, ebp
	pop	ebp
	ret	0
_vsnprintf ENDP
_TEXT	ENDS
_TEXT	SEGMENT
__Result$ = -8						; size = 4
__ArgList$ = -4						; size = 4
__Stream$ = 8						; size = 4
__Format$ = 12						; size = 4
_fprintf PROC						; COMDAT
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
	mov	eax, DWORD PTR __Stream$[ebp]
	push	eax
	call	__vfprintf_l
	add	esp, 16					; 00000010H
	mov	DWORD PTR __Result$[ebp], eax
	mov	DWORD PTR __ArgList$[ebp], 0
	mov	eax, DWORD PTR __Result$[ebp]
	mov	esp, ebp
	pop	ebp
	ret	0
_fprintf ENDP
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

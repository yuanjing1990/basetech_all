	TITLE	ArgumentAccess.cpp
	.386P
include listing.inc
if @Version gt 510
.model FLAT
else
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
_BSS	SEGMENT DWORD USE32 PUBLIC 'BSS'
_BSS	ENDS
_TLS	SEGMENT DWORD USE32 PUBLIC 'TLS'
_TLS	ENDS
FLAT	GROUP _DATA, CONST, _BSS
	ASSUME	CS: FLAT, DS: FLAT, SS: FLAT
endif
PUBLIC	?arg_test@@YAXPADZZ				; arg_test
EXTRN	_printf:NEAR
_DATA	SEGMENT
$SG541	DB	'%d', 00H
_DATA	ENDS
_TEXT	SEGMENT
_fmat$ = 8
_vl$ = -4
?arg_test@@YAXPADZZ PROC NEAR				; arg_test
; File ArgumentAccess.cpp
; Line 4
	push	ebp
	mov	ebp, esp
	push	ecx
; Line 6
	lea	eax, DWORD PTR _fmat$[ebp+4]
	mov	DWORD PTR _vl$[ebp], eax
; Line 7
	mov	ecx, DWORD PTR _vl$[ebp]
	add	ecx, 4
	mov	DWORD PTR _vl$[ebp], ecx
	mov	edx, DWORD PTR _vl$[ebp]
	cmp	DWORD PTR [edx-4], -1
	je	SHORT $L539
; Line 9
	mov	eax, DWORD PTR _vl$[ebp]
	push	eax
	push	OFFSET FLAT:$SG541
	call	_printf
	add	esp, 8
$L539:
; Line 11
	mov	DWORD PTR _vl$[ebp], 0
; Line 12
	mov	esp, ebp
	pop	ebp
	ret	0
?arg_test@@YAXPADZZ ENDP				; arg_test
_TEXT	ENDS
PUBLIC	_main
_DATA	SEGMENT
	ORG $+1
$SG547	DB	'hello', 00H
_DATA	ENDS
_TEXT	SEGMENT
_main	PROC NEAR
; Line 15
	push	ebp
	mov	ebp, esp
; Line 16
	push	4
	push	3
	push	2
	push	1
	push	OFFSET FLAT:$SG547
	call	?arg_test@@YAXPADZZ			; arg_test
	add	esp, 20					; 00000014H
; Line 17
	xor	eax, eax
; Line 18
	pop	ebp
	ret	0
_main	ENDP
_TEXT	ENDS
END

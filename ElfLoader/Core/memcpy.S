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
                EXPORT memcpy
                
memcpy					; CODE XREF: __assert_fail+84p
					; __assert_fail+C0p ...
		STMFD	SP!, {R0,R4,LR}
		SUB	SP, SP,	#0x1C
		CMP	R2, #4
		BCC	loc_7D60
		RSB	R3, R1,	#0
		ANDS	R3, R3,	#3
		BEQ	loc_7ABC
		MOVS	R12, R3,LSL#31
		SUB	R2, R2,	R3
		LDRMIB	R3, [R1],#1
		LDRCSB	R4, [R1],#1
		LDRCSB	R12, [R1],#1
		STRMIB	R3, [R0],#1
		STRCSB	R4, [R0],#1
		STRCSB	R12, [R0],#1

loc_7ABC				; CODE XREF: memcpy+18j
		EOR	R12, R0, R1
		TST	R12, #3
		BNE	loc_7B74
		STMEA	SP, {R5-R11}
		RSB	R3, R0,	#0
		ANDS	R3, R3,	#0x1C
		BEQ	loc_7B04
		CMP	R3, R2
		ANDHI	R3, R2,	#0x1C
		MOVS	R12, R3,LSL#28
		LDMCSIA	R1!, {R4-R7}
		LDMMIIA	R1!, {R8,R9}
		STMCSIA	R0!, {R4-R7}
		STMMIIA	R0!, {R8,R9}
		TST	R3, #4
		LDRNE	R10, [R1],#4
		STRNE	R10, [R0],#4
		SUB	R2, R2,	R3

loc_7B04				; CODE XREF: memcpy+54j
		SUBS	R2, R2,	#0x20
		BCC	loc_7B2C
		BIC	R12, R1, #0x1F
		ADD	R12, R12, #0x40

loc_7B14				; CODE XREF: memcpy+A4j
		LDMIA	R1!, {R4-R11}
		SUBS	R2, R2,	#0x20
		LDRHI	R3, [R12],#0x20
		STMIA	R0!, {R4-R11}
		BCS	loc_7B14
		ADD	R2, R2,	#0x20

loc_7B2C				; CODE XREF: memcpy+88j
		TST	R2, #0x1F
		BEQ	loc_7B68
		MOVS	R12, R2,LSL#28
		LDMCSIA	R1!, {R4-R7}
		LDMMIIA	R1!, {R8,R9}
		STMCSIA	R0!, {R4-R7}
		STMMIIA	R0!, {R8,R9}
		MOVS	R12, R2,LSL#30
		LDRCS	R3, [R1],#4
		LDRMIH	R4, [R1],#2
		STRCS	R3, [R0],#4
		STRMIH	R4, [R0],#2
		TST	R2, #1
		LDRNEB	R3, [R1]
		STRNEB	R3, [R0]

loc_7B68				; CODE XREF: memcpy+B0j
		LDMFD	SP!, {R5-R11}
		LDMFD	SP!, {R0,R4,LR}
		BX	LR
; ---------------------------------------------------------------------------

loc_7B74				; CODE XREF: memcpy+44j
		CMP	R2, #4
		BCC	loc_7D60
		STMEA	SP, {R5-R11}
		RSB	R5, R0,	#0
		AND	R5, R5,	#3
		MOV	R12, R5,LSL#3
		RSB	LR, R12, #0x20
		LDR	R3, [R1],#4
		SUB	R2, R2,	#4
		MOVS	R5, R5,LSL#31
		STRMIB	R3, [R0],#1
		MOVMI	R3, R3,LSR#8
		STRCSB	R3, [R0],#1
		MOVCS	R3, R3,LSR#8
		STRCSB	R3, [R0],#1
		MOVCS	R3, R3,LSR#8
		CMP	R2, #4
		BCC	loc_7D44

loc_7BBC				; CODE XREF: memcpy+15Cj
		TST	R0, #0x1C
		BEQ	loc_7BE4
		LDR	R5, [R1],#4
		SUB	R2, R2,	#4
		ORR	R4, R3,	R5,LSL LR
		MOV	R3, R5,LSR R12
		STR	R4, [R0],#4
		CMP	R2, #4
		BCS	loc_7BBC
		BCC	loc_7D44

loc_7BE4				; CODE XREF: memcpy+140j
		SUBS	R2, R2,	#0x20
		BCC	loc_7D18
		CMP	R12, #0x18
		BEQ	loc_7CBC
		CMP	R12, #8
		BEQ	loc_7C5C
		LDR	R12, [R1],#4

loc_7C00				; CODE XREF: memcpy+1D4j
		MOV	R4, R12
		LDMIA	R1!, {R5-R11}
		SUBS	R2, R2,	#0x20
		LDRCS	R12, [R1],#4
		ORR	R3, R3,	R4,LSL#16
		MOV	R4, R4,LSR#16
		ORR	R4, R4,	R5,LSL#16
		MOV	R5, R5,LSR#16
		ORR	R5, R5,	R6,LSL#16
		MOV	R6, R6,LSR#16
		ORR	R6, R6,	R7,LSL#16
		MOV	R7, R7,LSR#16
		ORR	R7, R7,	R8,LSL#16
		MOV	R8, R8,LSR#16
		ORR	R8, R8,	R9,LSL#16
		MOV	R9, R9,LSR#16
		ORR	R9, R9,	R10,LSL#16
		MOV	R10, R10,LSR#16
		ORR	R10, R10, R11,LSL#16
		STMIA	R0!, {R3-R10}
		MOV	R3, R11,LSR#16
		BCS	loc_7C00
		B	loc_7D18
; ---------------------------------------------------------------------------

loc_7C5C				; CODE XREF: memcpy+178j
		LDR	R12, [R1],#4

loc_7C60				; CODE XREF: memcpy+234j
		MOV	R4, R12
		LDMIA	R1!, {R5-R11}
		SUBS	R2, R2,	#0x20
		LDRCS	R12, [R1],#4
		ORR	R3, R3,	R4,LSL#24
		MOV	R4, R4,LSR#8
		ORR	R4, R4,	R5,LSL#24
		MOV	R5, R5,LSR#8
		ORR	R5, R5,	R6,LSL#24
		MOV	R6, R6,LSR#8
		ORR	R6, R6,	R7,LSL#24
		MOV	R7, R7,LSR#8
		ORR	R7, R7,	R8,LSL#24
		MOV	R8, R8,LSR#8
		ORR	R8, R8,	R9,LSL#24
		MOV	R9, R9,LSR#8
		ORR	R9, R9,	R10,LSL#24
		MOV	R10, R10,LSR#8
		ORR	R10, R10, R11,LSL#24
		STMIA	R0!, {R3-R10}
		MOV	R3, R11,LSR#8
		BCS	loc_7C60
		B	loc_7D18
; ---------------------------------------------------------------------------

loc_7CBC				; CODE XREF: memcpy+170j
		LDR	R12, [R1],#4

loc_7CC0				; CODE XREF: memcpy+294j
		MOV	R4, R12
		LDMIA	R1!, {R5-R11}
		SUBS	R2, R2,	#0x20
		LDRCS	R12, [R1],#4
		ORR	R3, R3,	R4,LSL#8
		MOV	R4, R4,LSR#24
		ORR	R4, R4,	R5,LSL#8
		MOV	R5, R5,LSR#24
		ORR	R5, R5,	R6,LSL#8
		MOV	R6, R6,LSR#24
		ORR	R6, R6,	R7,LSL#8
		MOV	R7, R7,LSR#24
		ORR	R7, R7,	R8,LSL#8
		MOV	R8, R8,LSR#24
		ORR	R8, R8,	R9,LSL#8
		MOV	R9, R9,LSR#24
		ORR	R9, R9,	R10,LSL#8
		MOV	R10, R10,LSR#24
		ORR	R10, R10, R11,LSL#8
		STMIA	R0!, {R3-R10}
		MOV	R3, R11,LSR#24
		BCS	loc_7CC0

loc_7D18				; CODE XREF: memcpy+168j memcpy+1D8j ...
		RSB	R12, LR, #0x20
		ADD	R2, R2,	#0x20
		CMP	R2, #4
		BCC	loc_7D44

loc_7D28				; CODE XREF: memcpy+2C0j
		LDR	R5, [R1],#4
		SUB	R2, R2,	#4
		ORR	R4, R3,	R5,LSL LR
		MOV	R3, R5,LSR R12
		STR	R4, [R0],#4
		CMP	R2, #4
		BCS	loc_7D28

loc_7D44				; CODE XREF: memcpy+138j memcpy+160j ...
		MOVS	R5, LR,LSL#28
		STRMIB	R3, [R0],#1
		MOVMI	R3, R3,LSR#8
		STRCSB	R3, [R0],#1
		MOVCS	R3, R3,LSR#8
		STRCSB	R3, [R0],#1
		LDMFD	SP, {R5-R11}

loc_7D60				; CODE XREF: memcpy+Cj	memcpy+F8j
		MOVS	R2, R2,LSL#31
		LDRMIB	R2, [R1],#1
		LDRCSB	R3, [R1],#1
		LDRCSB	R12, [R1]
		STRMIB	R2, [R0],#1
		STRCSB	R3, [R0],#1
		STRCSB	R12, [R0]
		ADD	SP, SP,	#0x1C
		LDMFD	SP!, {R0,R4,LR}
		BX	LR
; End of function memcpy
        
        END


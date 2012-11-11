        
        
        
        RSEG	CODE:CODE(2)

	PUBLIC	ExecuteIMB

ExecuteIMB:
	STR	LR,[SP, #-4]!
	MRS	R2,CPSR
        //SWI     0                       ; 
	MRS	R1,CPSR		        ; Запрещаем прерывания
	ORR	R1,R1,#0xC0
	MSR	CPSR_c,R1
                                        ;Выполняем необходимую требуху с кешем
clean_loop:
	MRC 	p15, 0, r15, c7, c10, 3 ; clean entire dcache using test and clean
	BNE	clean_loop
	MOV	R0,#0
	MCR	p15, 0, r0, c7, c10, 4  ; drain write buffer
	MCR	p15, 0, r0, c7, c5, 0   ; invalidate icache

;Выходим
	MSR	CPSR_c,R2	; Восстанавливаем старый режим
	LDR	PC,[SP], #+0x4
	
	END



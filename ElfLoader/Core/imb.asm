            RSEG   CODE:CODE(2)

	    PUBLIC ExecuteIMB

 ExecuteIMB:
 
	    STR	  LR, [SP, #-0x04]!
	    MRS	  R2,  CPSR
            
            // Запрещаем прерывания
	    MRS	  R1, CPSR
	    ORR   R1, R1,#0xC0
	    MSR   CPSR_c, R1
            
	    NOP
	    NOP
	    NOP
            
            // Выполняем необходимые требования с кешем
 clean_loop:
 
            // clean entire dcache using test and clean
	    MRC   p15, 0, r15, c7, c10, 3
            
	    NOP
	    NOP
	    NOP
            
	    BNE   clean_loop
	    MOV   R0, #0x00
            
            // drain write buffer
	    MCR   p15, 0, r0, c7, c10, 4
            
	    NOP
	    NOP
	    NOP
	    NOP
            
            // invalidate icache
	    MCR	  p15, 0, r0, c7, c5, 0
            
	    NOP
	    NOP
	    NOP
	    NOP
            
            // Выходим
            // Восстанавливаем старый режим
	    MSR	  CPSR_c,R2
	    LDR	  PC,[SP], #+0x04
	
	    END



//SWI dispatcher v1.1 (C)2006 by Rst7/CBSIE


                   EXTERN  __swihook_lib
	           EXTERN  __swihook_abort
                   
	           RSEG	   CODE:CODE
                   
	           CODE32
                   
                   PUBLIC   __swihandler_start
                   
                   
 __swihandler_start: 
 
                   STMFD   SP!, {R0-R3, LR}
                  
                   MRS     R0, SPSR
                   STMFD   SP!, {R0}
                   TST     R0, #0x20
                   LDRNEH  R0, [LR,#-2]
                   BICNE   R0, R0, #0xFF00
                   LDREQ   R0, [LR,#-4]
                   BICEQ   R0, R0, #0xFF000000

                   PUBLIC   __swihook_start
                   
 __swihook_start:
 
	           LDR	   R1, [SP, #0x00]      // Берем CPSR
	           TST     R1, #0x20	        // Проверяем на THUMB (установку T - бита)
	           ADREQ   R2, arm_jumper       // Берем адрес джампера
	           BEQ	   arm_mode
                   
	           CMP	   R0, #199	        // Служебный SWI для длинной библиотеки
	           LDREQH  R0, [LR], #2	        // Зацепляем второе слово (длинный номер) c пропуском DW
                   STREQ   LR, [SP, #0x14]      // Сохраняем временно адрес возврата (если захочем данные)
	           ADD	   LR, LR, #0x01        // Устанавливаем бит 0, если THUMB
	           ADR	   R2, thumb_jumper     // Берем адрес джампера
                   
          arm_mode:
          
	           LDR	   R1, =__swihook_lib   // Указатель на таблицу адресов
	           LDR	   R1, [R1]
	           CMP	   R1, #0x00
                   BEQ	   __swihook_exit
	           BIC	   R3, R0, #0x8000
                   CMP	   R3, #4096
                   BHI	   __swihook_exit
                   
	           TST	   R0,  #0x8000		// А не адрес нам надо получить?
	           STMEQFD SP!, {LR}		// Копируем адрес возврата из LR_svc только если вызов функции
	           LDMEQFD SP!, {LR}^		// в LR_usr, он будет использован вызываемой функцией
	           LDR     R12, [R1, R3, LSL#2]	// Берем адрес функции
	           STRNE   R12, [SP, #4]	// пишем адрес в R0(стек)
    /* ADD */      MOV     R1,   LR
	           
                   BNE	  __swihook_exit
	           CMP	  R12, #0xFFFFFFFF
	           LDREQ  R2, =__swihook_abort
	           STREQ  R0, [SP, #4]
	           STR	  R2, [SP, #0x14]	// Пишем адрес джампера для возврата в стеке (PC)
                   
                   
             
 __swihook_exit:
             
	           LDMFD  SP!, {R0}
	           MSR	  SPSR_cf, R0
	           LDMFD  SP!, {R0-R3, PC}^
      
        arm_jumper:
        
	           BX	  R12
                   
	           CODE16
                   
      thumb_jumper:
      
	           BX	  R12
                   
           nullsub:
           
	           BX	   LR
                   
	           END

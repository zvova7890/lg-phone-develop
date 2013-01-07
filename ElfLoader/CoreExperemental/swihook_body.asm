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
 
	           LDR	   R1, [SP, #0x00]      // ����� CPSR
	           TST     R1, #0x20	        // ��������� �� THUMB (��������� T - ����)
	           ADREQ   R2, arm_jumper       // ����� ����� ��������
	           BEQ	   arm_mode
                   
	           CMP	   R0, #199	        // ��������� SWI ��� ������� ����������
	           LDREQH  R0, [LR], #2	        // ��������� ������ ����� (������� �����) c ��������� DW
                   STREQ   LR, [SP, #0x14]      // ��������� �������� ����� �������� (���� ������� ������)
	           ADD	   LR, LR, #0x01        // ������������� ��� 0, ���� THUMB
	           ADR	   R2, thumb_jumper     // ����� ����� ��������
                   
          arm_mode:
          
	           LDR	   R1, =__swihook_lib   // ��������� �� ������� �������
	           LDR	   R1, [R1]
	           CMP	   R1, #0x00
                   BEQ	   __swihook_exit
	           BIC	   R3, R0, #0x8000
                   CMP	   R3, #4096
                   BHI	   __swihook_exit
                   
	           TST	   R0,  #0x8000		// � �� ����� ��� ���� ��������?
	           STMEQFD SP!, {LR}		// �������� ����� �������� �� LR_svc ������ ���� ����� �������
	           LDMEQFD SP!, {LR}^		// � LR_usr, �� ����� ����������� ���������� ��������
	           LDR     R12, [R1, R3, LSL#2]	// ����� ����� �������
	           STRNE   R12, [SP, #4]	// ����� ����� � R0(����)
    /* ADD */      MOV     R1,   LR
	           
                   BNE	  __swihook_exit
	           CMP	  R12, #0xFFFFFFFF
	           LDREQ  R2, =__swihook_abort
	           STREQ  R0, [SP, #4]
	           STR	  R2, [SP, #0x14]	// ����� ����� �������� ��� �������� � ����� (PC)
                   
                   
             
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

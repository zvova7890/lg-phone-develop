

            EXTERN  __mirfs_changer

    
            CODE32
             

            RSEG    CODE:CODE
            
            PUBLIC  __mirfs_j32
            
 __mirfs_j32:
 
            LDR     PC, [PC, #-4]
    
            DATA
            
            DC32    __mirfs_hook

             
            RSEG   CODE:CODE
             
 __mirfs_hook:


            LDR      R3, =0x800
            ADD      R3, R3, SP
            LDR      R1, [R3, #0x00]
            
            PUSH    {R0-R12, LR}
            
            CMP      R0, #0x01
            MOVEQ    R0, R1
            MOVEQ    R1, R5
            BLEQ     __mirfs_changer
            
            POP     {R0-R12, LR}
            
            LDR     R3, =0x804
            ADD     SP, SP, R3
            BX      LR
            
            
            END
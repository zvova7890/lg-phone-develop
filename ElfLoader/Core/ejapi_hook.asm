

            EXTERN  __ejapi_handler

    
            CODE16
             

            RSEG    CODE:CODE
            
            PUBLIC  __ejapi_patch
            
 __ejapi_patch:
 
            
             
            LDR     R1, [PC, #0x00]
            BLX     R1
            
            DATA
            
            DC32    __ejapi_hook
             

             
            CODE32
             
             
             
            RSEG   CODE:CODE
             
            PUBLIC  __ejapi_hook
            
 __ejapi_hook:
 
            ADD     LR, LR, #8
            SUB     SP, SP, #0x120
            
            
            PUSH    {R1-R12, LR}
            
            BL      __ejapi_handler
            
            CMP     R0, #0x00
            BNE     ejapi_hook_ok

            POP     {R1-R12, PC}
            
 ejapi_hook_ok:
 
            POP     {R1-R12, LR}
            
            ADD     SP, SP, #0x120
            POP     {R4-R6,PC}
            

            END
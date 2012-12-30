             EXTERN  init_main

             
             CODE16
             
             
             RSEG    PATCH_INITHOOK:CODE
             
             LDR     R0, =init_hook
             BLX     R0
             
             
             CODE32
             
             
             
             RSEG   CODE:CODE
 init_hook:
 
             ADD     LR, LR, #4

             PUSH    {R4-R12, LR}
            
             BLX     init_main
            

             POP     {R4-R12, PC}
            
             END
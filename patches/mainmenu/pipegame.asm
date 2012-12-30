
                         CODE16

                         RSEG    PXO_CODE:CODE

                         PUBLIC  start
                         
                start:
                         
                         DATA
                         
                         DC16    0xD10C 
                         
                         CODE16
                         
                         ADR      R0,  apps_path
                         MOV      R1,  #0x01
                         MOV      R3,  #0x00
                         SUB      SP, #8
                         STR      R3, [SP, #0x00]
                         STR      R0, [SP, #0x04]
                         ADD      R2,  SP, #0x04
                         SWI      0x0B
                         ADD      SP, #8
                  
                         POP     {R3-R7, PC}

                         RSEG    PXO_DATA:CODE
                         
                         DATA
                         
              apps_path:
                 
                         DC8     "/usr/Zbin/core/apps.elf", 0
                         
                         END

                         EXTERN  pxe_event_handler
 
                         RSEG    PXO_BOOT:CODE
                         
                         CODE16
                         
                         //������� �� ���������� �������
                         

                         ADR     R3, elf_parasite
                         B       pxe_event_handler
                         
                         DATA
          elf_parasite:
          
                         DC32    0x000000
                         DC32    0x000000
                         DC32    0x000000
                         DC32    0x000000
                         DC32    0x000000
                         DC32    0x000000
                         DC32    0x000000
                         DC32    0x000000
                         DC32    0x000000
                         DC32    0x000000
                         DC32    0x000000
                         DC32    0x000000
                         DC32    0x000000
                         DC32    0x000000
                         DC32    0x000000
                         DC32    0x000000
                         
                         END
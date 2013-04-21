




    .extern myhook

    .global hook_data
    .global hook_helper_func
    .thumb
hook_nop:
    nop

hook_data:

    LDR R4, [PC, #0x04]
    BLX R4
    NOP

hook_helper_func:
    nop
    nop
    nop
    nop


    .arm
    .global fhook
fhook:

    ADD LR, LR, #4
    SUB SP, SP, #0x10
    PUSH {LR}
    BL myhook

    MOVS R1, #1
    MOVS R0, #0
    mov lr, pc
    ldr pc, lol_call
    POP {PC}

lol_call: .int 0x465758B3



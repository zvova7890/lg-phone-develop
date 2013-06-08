





    .thumb
    .global hook_data
    .global hook_addr
hook_nop:
    nop

hook_data:

    LDR  R4, [PC, #0x04]
    BX   R4
    NOP

hook_addr:
    nop
    nop


    .arm
    .global test_func
test_func:

    stmfd  sp!, {r0-r3, lr}
    bl     logger
    ldmfd  sp!, {r0-r3, lr}

    MOVS    R7, R1
    MOVS    R5, R0
    CMP     R0, #0
    SUB     SP, SP, #0x14
    ldrne   pc, loc_46575796


    sub    sp, #8
    str    r6, [sp, #0]

    ldr    r6, =jump
    ldr    r6, [r6]

    str    r6, [sp, #4]

    ldmfd  sp!, {r6, pc}

jump: .int 0x46575772+10+1
loc_46575796: .int 0x46575796+1

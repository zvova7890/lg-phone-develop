





    .thumb
    .global hook_data
hook_data:
    push {lr}
    swi 28




    .global bxlr
bxlr:
    mov r0, #0
    bx  lr


    .arm
    .global test_func
test_func:

    ldmfd sp!, {lr}
    mov   r0, lr
    b     logger



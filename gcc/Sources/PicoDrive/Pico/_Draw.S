@ assembly "optimized" version of some funtions from draw.c
@ this is highly specialized, be careful if changing related C code!

@ (c) Copyright 2006, notaz
@ All Rights Reserved


.extern Pico
.extern PicoOpt
.extern HighCol
.extern Scanline
.extern HighSprZ
.extern rendstatus
.extern DrawLineDest
.extern DrawStripVSRam
.extern DrawStripInterlace


@ helper
.macro TilePixel pat lsrr offs
.if !\lsrr
    ands    r4, \pat, r2
.else
    ands    r4, \pat, r2, lsr #\lsrr
.endif
    orrne   r4, r3, r4
    strneb  r4, [r1,#\offs]
.endm

@ TileNorm (r1=pdest, r2=pixels8, r3=pal) r4: scratch, pat: register with helper pattern 0xf
.macro TileNorm pat
    TilePixel \pat, 12, 0         @ #0x0000f000
    TilePixel \pat,  8, 1         @ #0x00000f00
    TilePixel \pat,  4, 2         @ #0x000000f0
    TilePixel \pat,  0, 3         @ #0x0000000f
    TilePixel \pat, 28, 4         @ #0xf0000000
    TilePixel \pat, 24, 5         @ #0x0f000000
    TilePixel \pat, 20, 6         @ #0x00f00000
    TilePixel \pat, 16, 7         @ #0x000f0000
.endm

@ TileFlip (r1=pdest, r2=pixels8, r3=pal) r4: scratch, pat: register with helper pattern 0xf
.macro TileFlip pat
    TilePixel \pat, 16, 0         @ #0x000f0000
    TilePixel \pat, 20, 1         @ #0x00f00000
    TilePixel \pat, 24, 2         @ #0x0f000000
    TilePixel \pat, 28, 3         @ #0xf0000000
    TilePixel \pat,  0, 4         @ #0x0000000f
    TilePixel \pat,  4, 5         @ #0x000000f0
    TilePixel \pat,  8, 6         @ #0x00000f00
    TilePixel \pat, 12, 7         @ #0x0000f000
.endm

@ shadow/hilight mode

@ this one is for hi priority layer
.macro TilePixelShHP lsrr offs
.if !\lsrr
    ands    r4, r12, r2
.else
    ands    r4, r12, r2, lsr #\lsrr
.endif
    ldreqb  r4, [r1,#\offs]
    orrne   r4, r3, r4
    strneb  r4, [r1,#\offs]
    tsteq   r4, #0x80
    andeq   r4, r4, #0x3f
    streqb  r4, [r1,#\offs]
.endm

@ TileNorm (r1=pdest, r2=pixels8, r3=pal) r4: scratch, r12: register with helper pattern 0xf, touches r3 high bits
.macro TileNormShHP
    TilePixelShHP 12, 0         @ #0x0000f000
    TilePixelShHP  8, 1         @ #0x00000f00
    TilePixelShHP  4, 2         @ #0x000000f0
    TilePixelShHP  0, 3         @ #0x0000000f
    TilePixelShHP 28, 4         @ #0xf0000000
    TilePixelShHP 24, 5         @ #0x0f000000
    TilePixelShHP 20, 6         @ #0x00f00000
    TilePixelShHP 16, 7         @ #0x000f0000
.endm

@ TileFlip (r1=pdest, r2=pixels8, r3=pal) r4: scratch, pat: register with helper pattern 0xf
.macro TileFlipShHP
    TilePixelShHP 16, 0         @ #0x000f0000
    TilePixelShHP 20, 1         @ #0x00f00000
    TilePixelShHP 24, 2         @ #0x0f000000
    TilePixelShHP 28, 3         @ #0xf0000000
    TilePixelShHP  0, 4         @ #0x0000000f
    TilePixelShHP  4, 5         @ #0x000000f0
    TilePixelShHP  8, 6         @ #0x00000f00
    TilePixelShHP 12, 7         @ #0x0000f000
.endm


@ TileSingleSh (r1=pdest, r2=pixels8, r3=pal) r4,r7: scratch, r0=sx; r12: helper pattern 0xf
.macro TileSingleSh
    tst     r0, #1              @ not aligned?
    mov     r7, #0x00c000
    orr     r7, r7, #0xc0
    ldrneb  r4, [r1]
    ldreqh  r4, [r1]
    orr     r4, r4, r7
    strneb  r4, [r1], #1
    streqh  r4, [r1], #2
    ldrh    r4, [r1]
    orr     r4, r4, r7
    strh    r4, [r1], #2
    ldrh    r4, [r1]
    orr     r4, r4, r7
    strh    r4, [r1], #2
    ldrh    r4, [r1]
    orr     r4, r4, r7
    strh    r4, [r1], #2
    ldrneb  r4, [r1]
    orr     r4, r4, r7
    strneb  r4, [r1], #1
.endm

@ TileSingleHi (r1=pdest, r2=pixels8, r3=pal) r4,r7: scratch, r0=sx, r12: register with helper pattern 0xf
.macro TileSingleHi
    tst     r1,  #1              @ not aligned?
    mov     r7,  #0x008000
    orr     r7,  r7, #0x80
    ldrneb  r4,  [r1], #1
    ldreqh  r4,  [r1], #2        @ 1ci
    ldrh    r12, [r1], #2
    bic     r4,  r4,  r7, lsr #1
    orr     r4,  r4,  r7
    strneb  r4,  [r1, #-3]
    streqh  r4,  [r1, #-4]
    ldrh    r4,  [r1], #2
    bic     r12, r12, r7, lsr #1
    orr     r12, r12, r7
    strh    r12, [r1, #-4]
    ldrh    r12, [r1], #2
    bic     r4,  r4,  r7, lsr #1
    orr     r4,  r4,  r7
    strh    r4,  [r1, #-4]
    ldrneb  r4,  [r1]
    bic     r12, r12, r7, lsr #1
    orr     r12, r12, r7
    strh    r12, [r1, #-2]
    bicne   r4,  r4,  r7, lsr #1
    orrne   r4,  r4,  r7
    strneb  r4,  [r1], #1
    mov     r12, #0xf
.endm

.macro TileDoShGenPixel shift ofs
.if \shift
    ands    r4, r12, r2, lsr #\shift
.else
    ands    r4, r12, r2
.endif
    beq     3f
    cmp     r4, #0xe
    beq     2f
    bgt     1f
    orr     r4, r3, r4
    strb    r4, [r1,#\ofs]
    b       3f
1:
    ldrb    r4, [r1,#\ofs]        @ 2ci
    orr     r4, r4, #0xc0
    strb    r4, [r1,#\ofs]
    b       3f
2:
    ldrb    r4, [r1,#\ofs]        @ 2ci
    bic     r4, r4, #0xc0
    orr     r4, r4, #0x80
    strb    r4, [r1,#\ofs]
3:
.endm

@ TileFlipSh (r1=pdest, r2=pixels8, r3=pal) r4,r7: scratch, r0=sx, r12: register with helper pattern 0xf
.macro TileFlipSh
    TileDoShGenPixel 16,  0 @ #0x000f0000
    TileDoShGenPixel 20,  1 @ #0x00f00000
    TileDoShGenPixel 24,  2 @ #0x0f000000
    TileDoShGenPixel 28,  3 @ #0xf0000000
    TileDoShGenPixel  0,  4 @ #0x0000000f
    TileDoShGenPixel  4,  5 @ #0x000000f0
    TileDoShGenPixel  8,  6 @ #0x00000f00
    TileDoShGenPixel 12,  7 @ #0x0000f000
.endm

@ TileNormSh (r1=pdest, r2=pixels8, r3=pal) r4,r7: scratch, r0=sx, r12: register with helper pattern 0xf
.macro TileNormSh
    TileDoShGenPixel 12,  0 @ #0x0000f000
    TileDoShGenPixel  8,  1 @ #0x00000f00
    TileDoShGenPixel  4,  2 @ #0x000000f0
    TileDoShGenPixel  0,  3 @ #0x0000000f
    TileDoShGenPixel 28,  4 @ #0xf0000000
    TileDoShGenPixel 24,  5 @ #0x0f000000
    TileDoShGenPixel 20,  6 @ #0x00f00000
    TileDoShGenPixel 16,  7 @ #0x000f0000
.endm


@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@ struct TileStrip
@ {
@   int nametab; // 0x00
@   int line;    // 0x04
@   int hscroll; // 0x08
@   int xmask;   // 0x0C
@   int *hc;     // 0x10 (pointer to cache buffer)
@   int cells;   // 0x14
@ };

@ int DrawLayer(int plane, int *hcache, int maxcells, int sh)

.global DrawLayer @ int plane, int *hcache, int maxcells, int sh

DrawLayer:
    stmfd   sp!, {r4-r11,lr}

    ldr     r11, =(Pico+0x22228)  @ Pico.video
    mov     r8, #1

    ldrb    r7, [r11, #16]        @ ??hh??ww

    mov     r6, r1                @ hcache
    orr     r9, r2, r3, lsl #31   @ r9=maxcells|(sh<<31)

    mov     r1, r7, lsl #4
    orr     r1, r1, #0x00ff

    and     r10, r7,  #3
    cmp     r10, #1
    biclt   r1,  r1, #0xfc00
    biceq   r1,  r1, #0xfe00
    bicgt   r1,  r1, #0xff00      @ r1=ymask=(height<<8)|0xff; ...; // Y Mask in pixels

    add     r10, r10, #5
    cmp     r10, #7
    subge   r10, r10, #1          @ r10=shift[width] (5,6,6,7)

    @ calculate xmask:
    mov     r5, r8, lsl r10
    sub     r5, r5, #1            @ r5=xmask

    @ Find name table:
    tst     r0,  r0
    ldreqb  r12, [r11, #2]
    ldrneb  r12, [r11, #4]

    ldr     r2, =Scanline         @ trying to make good use of pipeline here
    ldr     lr, =(Pico+0x10000)   @ lr=Pico.vram

    moveq   r12, r12, lsl #10
    movne   r12, r12, lsl #13
    and     r12, r12, #(7<<13)    @ r12=(ts->nametab<<1) (halfword compliant)

    ldrh    r8, [r11, #12]
    ldrb    r7, [r11, #11]
    ldr     r2, [r2]

    mov     r4, r8, lsr #8        @ pvid->reg[13]
    mov     r4, r4, lsl #10       @ htab=pvid->reg[13]<<9; (halfwords)
    tst     r7, #2
    addne   r4, r4, r2, lsl #2    @ htab+=Scanline<<1; // Offset by line
    tst     r7, #1
    biceq   r4, r4, #0x1f         @ htab&=~0xf; // Offset by tile
    add     r4, r4, r0, lsl #1    @ htab+=plane
    bic     r4, r4, #0x00ff0000   @ just in case
    ldrh    r3, [lr, r4]          @ r3=hscroll

    tst     r7, #4
    bne     .DrawStrip_vsscroll

    @ Get vertical scroll value:
    add     r7, lr,  #0x012000
    add     r7, r7,  #0x000180    @ r7=Pico.vsram (Pico+0x22180)
    ldr     r7, [r7]

    tst     r8, #2
    tstne   r8, #4
    bne     .DrawStrip_interlace

    tst     r0, r0
    movne   r7, r7, lsr #16

    @ Find the line in the name table
    add     r2, r2, r7
    and     r2, r2, r1
    mov     r4, r2, lsr #3
    add     r10, r10, #1           @ shift[width]++
    add     r12, r12, r4, lsl r10  @ nametab+=(ts.line>>3)<<shift[width];

    @ ldmia   r0, {r1,r2,r3,r5,r6,r9} @ r2=line, r3=ts->hscroll, r5=ts->xmask, r6=ts->hc, r9=ts->cells
@    mov     r12,r1,  lsl #1 @ r12=(ts->nametab<<1) (halfword compliant)

    and     r10,r2,  #7
    mov     r10,r10, lsl #1 @ r10=ty=(ts->line&7)<<1;
    orr     r10,r10, r9, lsl #24

    rsb     r8, r3, #0
    mov     r8, r8, lsr #3  @ r8=tilex=(-ts->hscroll)>>3

    sub     r1, r3, #1
    and     r1, r1, #7
    add     r7, r1, #1      @ r7=dx=((ts->hscroll-1)&7)+1

    tst     r9, #1<<31
    mov     r3, #0
    orrne   r10,r10, #1<<23 @ r10=(cells<<24|sh<<23|hi_not_empty<<22|ty)
    movne   r3, #0x40       @ default to shadowed pal on sh mode

    mvn     r9, #0          @ r9=prevcode=-1

    cmp     r7, #8
    addne   r10,r10, #0x01000000 @ we will loop cells+1 times if there is scroll

    @ cache some stuff to avoid mem access
    ldr     r11,=HighCol
    mov     r0, #0xf
    add     r1, r11, r7         @ r1=pdest


    @ r4 & r7 are scratch in this loop
.dsloop_subr1:
    sub     r1, r1, #8
.dsloop: @ 40-41 times
    subs    r10,r10, #0x01000000
    bmi     .dsloop_exit

.dsloop_enter:
    and     r7, r5, r8
    add     r7, lr, r7, lsl #1 @ Pico.vram+((tilex&ts->xmask) as halfwords)
    ldrh    r7, [r7, r12]      @ r7=code (int, but from unsigned, no sign extend)

    add     r1, r1, #8
    add     r8, r8, #1

    tst     r7, #0x8000
    bne     .DrawStrip_hiprio

    cmp     r7, r9
    beq     .DrawStrip_samecode @ we know stuff about this tile already

    mov     r9, r7          @ remember code

    movs    r2, r9, lsl #20 @ if (code&0x1000)
    mov     r2, r2, lsl #1
    add     r2, r2, r10, lsl #17
    mov     r2, r2, lsr #17
    eorcs   r2, r2, #0x0e   @ if (code&0x1000) addr^=0xe;

    ldr     r2, [lr, r2, lsl #1] @ pack=*(unsigned int *)(Pico.vram+addr); // Get 8 pixels

    bic     r7, r3, #0x3f
    and     r3, r9, #0x6000
    add     r3, r7, r3, lsr #9 @ r3=pal=((code&0x6000)>>9);

.DrawStrip_samecode:
    tst     r2, r2
    beq     .dsloop              @ tileline blank

    cmp     r2, r2, ror #4
    beq     .DrawStrip_SingleColor @ tileline singlecolor 

    tst     r9, #0x0800
    beq     .DrawStrip_TileNorm

    @ (r1=pdest, r2=pixels8, r3=pal) r4: scratch, r0: helper pattern
    TileFlip r0
    b       .dsloop

.DrawStrip_TileNorm:
    TileNorm r0
    b       .dsloop

.DrawStrip_SingleColor:
    and     r4, r2, #0xf
    orr     r4, r3, r4
    orr     r4, r4, r4, lsl #8
    tst     r1, #1             @ not aligned?
    strneb  r4, [r1], #1
    streqh  r4, [r1], #2
    strh    r4, [r1], #2
    strh    r4, [r1], #2
    strh    r4, [r1], #2
    strneb  r4, [r1], #1       @ have a remaining unaligned pixel?
    b       .dsloop_subr1

.DrawStrip_hiprio:
    tst     r10, #0x00c00000
    beq     .DrawStrip_hiprio_maybempt
    sub     r0, r1, r11
    orr     r7, r7, r0,  lsl #16
    orr     r7, r7, r10, lsl #25 @ (ty<<25)
    tst     r7, #0x1000
    eorne   r7, r7, #7<<26  @ if(code&0x1000) cval^=7<<26;
    str     r7, [r6], #4    @ cache hi priority tile
    mov     r0, #0xf
    b       .dsloop

.DrawStrip_hiprio_maybempt:
    cmp     r7, r9
    beq     .dsloop         @ must've been empty, otherwise we wouldn't get here
    movs    r2, r7, lsl #20 @ if (code&0x1000)
    mov     r2, r2, lsl #1
    add     r2, r2, r10, lsl #17
    mov     r2, r2, lsr #17
    eorcs   r2, r2, #0x0e   @ if (code&0x1000) addr^=0xe;
    ldr     r2, [lr, r2, lsl #1] @ pack=*(unsigned int *)(Pico.vram+addr); // Get 8 pixels
    mov     r9, r7          @ remember code
    tst     r2, r2
    orrne   r10, r10, #1<<22
    bne     .DrawStrip_hiprio
    b       .dsloop

.dsloop_exit:
    mov     r0, #0
    str     r0, [r6]    @ terminate the cache list

    ldmfd   sp!, {r4-r11,lr}
    bx      lr


.DrawStrip_vsscroll:
    @ shit, we have 2-cell column based vscroll
    @ let the c code handle this (for now)

    @   int nametab; // 0x00
    @   int line;    // 0x04
    @   int hscroll; // 0x08
    @   int xmask;   // 0x0C
    @   int *hc;     // 0x10 (pointer to cache buffer)
    @   int cells;   // 0x14

    sub     sp, sp, #6*4
    orr     r2, r1, r10, lsl #24 @ ts.line=ymask|(shift[width]<<24); // save some stuff instead of line
    mov     r1, r0               @ plane
    mov     r0, r12, lsr #1      @ halfwords
    and     r9, r9, #0xff
    stmia   sp, {r0,r2,r3,r5,r6,r9}

    mov     r0, sp
    bl      DrawStripVSRam @ struct TileStrip *ts, int plane

    add     sp, sp, #6*4
    ldmfd   sp!, {r4-r11,lr}
    bx      lr

@ interlace mode 2? Sonic 2?
.DrawStrip_interlace:
    tst     r0, r0
    moveq   r7, r7, lsl #21
    movne   r7, r7, lsl #5

    @ Find the line in the name table
    add     r2, r7, r2, lsl #22    @ r2=(vscroll+(Scanline<<1))<<21 (11 bits);
    orr     r1, r1, #0x80000000
    and     r2, r2, r1, ror #10    @ &((ymask<<1)|1)<<21;
    mov     r2, r2, lsr #21
    mov     r4, r2, lsr #4
    mov     r12, r12, lsr #1       @ halfwords
    add     r0, r12, r4, lsl r10   @ nametab+=(ts.line>>4)<<shift[width];
    and     r9, r9, #0xff

    sub     sp, sp, #6*4
    stmia   sp, {r0,r2,r3,r5,r6,r9}

    mov     r0, sp
    bl      DrawStripInterlace @ struct TileStrip *ts

    add     sp, sp, #6*4
    ldmfd   sp!, {r4-r11,lr}
    bx      lr

.pool

@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


.global BackFill @ int reg7, int sh

BackFill:
    stmfd   sp!, {r4-r9,lr}

    ldr     lr, =(HighCol+8)

    mov     r0, r0, lsl #26
    mov     r0, r0, lsr #26
    orr     r0, r0, r1, lsl #6
    orr     r0, r0, r0, lsl #8
    orr     r0, r0, r0, lsl #16

    mov     r1, r0
    mov     r2, r0
    mov     r3, r0
    mov     r4, r0
    mov     r5, r0
    mov     r6, r0
    mov     r7, r0

    @ go go go!
    stmia   lr!, {r0-r7} @ 10*8*4
    stmia   lr!, {r0-r7}
    stmia   lr!, {r0-r7}
    stmia   lr!, {r0-r7}
    stmia   lr!, {r0-r7}
    stmia   lr!, {r0-r7}
    stmia   lr!, {r0-r7}
    stmia   lr!, {r0-r7}
    stmia   lr!, {r0-r7}
    stmia   lr!, {r0-r7}

    ldmfd   sp!, {r4-r9,r12}
    bx      r12


@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


.global DrawTilesFromCache @ int *hc, int sh

DrawTilesFromCache:
    stmfd   sp!, {r4-r8,r11,lr}

    mvn     r5, #0         @ r5=prevcode=-1
    mov     r8, r1

    @ cache some stuff to avoid mem access
    ldr     r11,=HighCol
    ldr     lr, =(Pico+0x10000) @ lr=Pico.vram
    mov     r12,#0xf

    @ scratch: r4, r7
.dtfc_loop:
    ldr     r6, [r0], #4    @ read code
    movs    r1, r6, lsr #16 @ r1=dx;
    ldmeqfd sp!, {r4-r8,r11,pc} @ dx is never zero, this must be a terminator, return
    bic     r1, r1, #0xfe00
    add     r1, r11, r1     @ r1=pdest

    mov     r7, r6, lsl #16
    cmp     r5, r7, lsr #16
    beq     .dtfc_samecode  @ if (code==prevcode)

    mov     r5, r7, lsr #16

    mov     r2, r5, lsl #21
    mov     r2, r2, lsr #17 @ r2=addr=(code&0x7ff)<<4;
    add     r2, r2, r6, lsr #25 @ addr+=ty

    and     r3, r5, #0x6000
    mov     r3, r3, lsr #9  @ r3=pal=((code&0x6000)>>9);

    ldr     r2, [lr, r2, lsl #1] @ pack=*(unsigned int *)(Pico.vram+addr); // Get 8 pixels

.dtfc_samecode:
    tst     r8, r8
    bne     .dtfc_shadow

    tst     r2, r2
    beq     .dtfc_loop

    cmp     r2, r2, ror #4
    beq     .dtfc_SingleColor @ tileline singlecolor 

    tst     r5, #0x0800
    beq     .dtfc_TileNorm

    @ (r1=pdest, r2=pixels8, r3=pal) r4: scratch, r12: helper pattern
    TileFlip r12
    b       .dtfc_loop

.dtfc_TileNorm:
    TileNorm r12
    b       .dtfc_loop

.dtfc_SingleColor:
    and     r4, r2, #0xf
    orr     r4, r3, r4
    orr     r4, r4, r4, lsl #8
    tst     r1, #1              @ not aligned?
    strneb  r4, [r1], #1
    streqh  r4, [r1], #2
    strh    r4, [r1], #2
    strh    r4, [r1], #2
    strh    r4, [r1], #2
    strneb  r4, [r1], #1        @ have a remaining unaligned pixel?
    b       .dtfc_loop

.dtfc_shadow:
    tst     r2, r2
    beq     .dtfc_shadow_blank

    cmp     r2, r2, ror #4
    beq     .dtfc_SingleColor @ tileline singlecolor 

    tst     r5, #0x0800
    beq     .dtfc_TileNormShHP

    @ (r1=pdest, r2=pixels8, r3=pal) r4: scratch, r12: helper pattern
    TileFlipShHP
    b       .dtfc_loop

.dtfc_TileNormShHP:
    TileNormShHP
    b       .dtfc_loop

.dtfc_shadow_blank:
    ldrb    r4, [r1]        @ 1ci
    ldrb    r12,[r1,#1]
    tst     r4, #0x80
    andeq   r4, r4,#0x3f
    streqb  r4, [r1]
    tst     r12,#0x80
    ldrb    r4, [r1,#2]
    andeq   r12,r12,#0x3f
    streqb  r12,[r1,#1]
    tst     r4, #0x80
    ldrb    r12,[r1,#3]
    andeq   r4, r4,#0x3f
    streqb  r4, [r1,#2]
    tst     r12,#0x80
    ldrb    r4, [r1,#4]
    andeq   r12,r12,#0x3f
    streqb  r12,[r1,#3]
    tst     r4, #0x80
    ldrb    r12,[r1,#5]
    andeq   r4, r4,#0x3f
    streqb  r4, [r1,#4]
    tst     r12,#0x80
    ldrb    r4, [r1,#6]
    andeq   r12,r12,#0x3f
    streqb  r12,[r1,#5]
    tst     r4, #0x80
    ldrb    r12,[r1,#7]
    andeq   r4, r4,#0x3f
    streqb  r4, [r1,#6]
    tst     r12,#0x80
    andeq   r12,r12,#0x3f
    streqb  r12,[r1,#7]
    mov     r12, #0xf
    b       .dtfc_loop

.pool

@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


.global DrawSpritesFromCache @ int *hc, int sh

DrawSpritesFromCache:
    stmfd   sp!, {r4-r11,lr}

    @ cache some stuff to avoid mem access
    ldr     r11,=HighCol
    ldr     lr, =(Pico+0x10000) @ lr=Pico.vram
    mov     r6, r1, lsl #31
    orr     r6, r6, #1<<30
    mov     r12,#0xf

    mov     r10, r0

.dsfc_loop:
    ldr     r9, [r10], #4    @ read code
    bic     r6, r6, #7       @ using pipeline
    tst     r9, r9
    ldmeqfd sp!, {r4-r11,pc}

    mov     r4, r9, lsl #28
    orr     r6, r6, r4, lsr #30
    add     r6, r6, #1       @ r6=s1cc???? ... ?????www (s=shadow/hilight, cc=pal, w=width)

    and     r5, r9, #3
    add     r5, r5, #1       @ r5=delta
    tst     r9, #0x10000
    rsbne   r5, r5, #0       @ Flip X
    mov     r5, r5, lsl #4

    mov     r2, r9, lsr #17
    mov     r8, r2, lsl #1   @ tile=((unsigned int)code>>17)<<1;

    and     r3, r9, #0x30    @ r3=pal=(code&0x30);

    bic     r6, r6, #3<<28
    orr     r6, r6, r3, lsl #24

    mov     r0, r9, lsl #16
    mov     r0, r0, asr #22  @ sx=(code<<16)>>22
    adds    r0, r0, #0       @ set ZV
    b       .dsfc_inloop_enter

@ scratch: r4, r7
.dsfc_inloop:
    sub     r6, r6, #1
    tst     r6, #7
    beq     .dsfc_loop
    adds    r0, r0, #8
    add     r8, r8, r5

.dsfc_inloop_enter:
    ble     .dsfc_inloop
    cmp     r0, #328
    bge     .dsfc_loop

    mov     r8, r8, lsl #17
    mov     r8, r8, lsr #17   @ tile&=0x7fff; // Clip tile address

    ldr     r2, [lr, r8, lsl #1] @ pack=*(unsigned int *)(Pico.vram+tile); // Get 8 pixels
    add     r1, r11, r0       @ r1=pdest
    tst     r2, r2
    beq     .dsfc_inloop

    cmp     r12, r6, lsr #28
    beq     .dsfc_shadow

    cmp     r2, r2, ror #4
    beq     .dsfc_SingleColor @ tileline singlecolor 

    tst     r9, #0x10000
    beq     .dsfc_TileNorm

    @ TileFlip (r1=pdest, r2=pixels8, r3=pal) r4: scratch, r12: helper pattern
    TileFlip r12
    b       .dsfc_inloop

.dsfc_TileNorm:
    TileNorm r12
    b       .dsfc_inloop

.dsfc_SingleColor:
    tst     r0, #1              @ not aligned?
    and     r4, r2, #0xf
    orr     r4, r3, r4
    orr     r4, r4, r4, lsl #8
    strneb  r4, [r1], #1
    streqh  r4, [r1], #2
    strh    r4, [r1], #2
    strh    r4, [r1], #2
    strh    r4, [r1], #2
    strneb  r4, [r1], #1
    b       .dsfc_inloop

.dsfc_shadow:
    cmp     r2, r2, ror #4
    beq     .dsfc_singlec_sh

    tst     r9, #0x10000
    beq     .dsfc_TileNorm_sh

    @ (r1=pdest, r2=pixels8, r3=pal) r4: scratch, r12: helper pattern
    TileFlipSh
    b       .dsfc_inloop

.dsfc_TileNorm_sh:
    TileNormSh
    b       .dsfc_inloop

.dsfc_singlec_sh:
    cmp     r2, #0xe0000000
    bcc     .dsfc_SingleColor   @ normal singlecolor tileline (carry inverted in ARM)
    tst     r2, #0x10000000
    bne     .dsfc_sh_sh
    TileSingleHi
    b       .dsfc_inloop

.dsfc_sh_sh:
    TileSingleSh
    b       .dsfc_inloop

.pool

@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@ + 0  :    hhhhvvvv ab--hhvv yyyyyyyy yyyyyyyy // a: offscreen h, b: offs. v, h: horiz. size
@ + 4  :    xxxxxxxx xxxxxxxx pccvhnnn nnnnnnnn // x: x coord + 8

.global DrawSprite @ unsigned int *sprite, int **hc, int sh

DrawSprite:
    stmfd   sp!, {r4-r9,r11,lr}

    ldr     r3, [r0]        @ sprite[0]
    ldr     r7, =Scanline
    mov     r6, r3, lsr #28
    sub     r6, r6, #1      @ r6=width-1 (inc later)
    mov     r5, r3, lsr #24
    and     r5, r5, #7      @ r5=height

    mov     r4, r3, lsl #16 @ r4=sy<<16 (tmp)

    ldr     r7, [r7]
    ldr     r9, [r0, #4]
    sub     r7, r7, r4, asr #16 @ r7=row=Scanline-sy

    tst     r2, r2
    mov     r2, r9, asr #16 @ r2=sx
    bic     r9, r9, #0xfe000000
    orrne   r9, r9, #1<<31  @ r9=code|(sh<<31)

    tst     r9, #0x1000
    movne   r4, r5, lsl #3
    subne   r4, r4, #1
    subne   r7, r4, r7      @ if (code&0x1000) row=(height<<3)-1-row; // Flip Y

    mov     r8, r9, lsl #21
    mov     r8, r8, lsr #21
    add     r8, r8, r7, lsr #3 @ tile+=row>>3; // Tile number increases going down
    
    tst     r9, #0x0800
    mlane   r8, r5, r6, r8  @ if (code&0x0800) { tile+=delta*(width-1);
    rsbne   r5, r5, #0      @ delta=-delta; } // r5=delta now

    mov     r8, r8, lsl #4
    and     r7, r7, #7
    add     r8, r8, r7, lsl #1 @ tile+=(row&7)<<1; // Tile address

    tst     r9, #0x8000
    bne     .dspr_cache       @ if(code&0x8000) // high priority - cache it

    @ cache some stuff to avoid mem access
    ldr     r11,=HighCol
    ldr     lr, =(Pico+0x10000) @ lr=Pico.vram
    mov     r12,#0xf

    mov     r5, r5, lsl #4     @ delta<<=4; // Delta of address
    and     r4, r9, #0x6000
    orr     r9, r9, r4, lsl #16
    orr     r9, r9, #0x10000000 @ r9=scc1 ???? ... <code> (s=shadow/hilight, cc=pal)

    tst     r9, #1<<31
    mov     r3, r4, lsr #9     @ r3=pal=((code>>9)&0x30);
    orrne   r3, r3, #0x40      @ shadow by default

    add     r6, r6, #1         @ inc now
    adds    r0, r2, #0         @ mov sx to r0 and set ZV flags
    b       .dspr_loop_enter

.dspr_loop:
    subs    r6, r6, #1         @ width--
    ldmeqfd sp!, {r4-r9,r11,pc}@ return
    adds    r0, r0, #8         @ sx+=8
    add     r8, r8, r5         @ tile+=delta

.dspr_loop_enter:
    ble     .dspr_loop         @ sx <= 0
    cmp     r0, #328
    ldmgefd sp!, {r4-r9,r11,pc}@ return

    mov     r8, r8, lsl #17
    mov     r8, r8, lsr #17    @ tile&=0x7fff; // Clip tile address

    ldr     r2, [lr, r8, lsl #1] @ pack=*(unsigned int *)(Pico.vram+addr); // Get 8 pixels
    add     r1, r11, r0        @ r1=pdest
    tst     r2, r2
    beq     .dspr_loop

    cmp     r12, r9, lsr #28
    beq     .dspr_shadow

    cmp     r2, r2, ror #4
    beq     .dspr_SingleColor @ tileline singlecolor 

    tst     r9, #0x0800
    beq     .dspr_TileNorm

    @ (r1=pdest, r2=pixels8, r3=pal) r4: scratch, r12: helper pattern
    TileFlip r12
    b       .dspr_loop

@ scratch: r4, r7
.dspr_TileNorm:
    TileNorm r12
    b       .dspr_loop

.dspr_SingleColor:
    and     r4, r2, #0xf
    orr     r4, r3, r4
    orr     r4, r4, r4, lsl #8
    tst     r0, #1              @ not aligned?
    strneb  r4, [r1], #1
    streqh  r4, [r1], #2
    strh    r4, [r1], #2
    strh    r4, [r1], #2
    strh    r4, [r1], #2
    strneb  r4, [r1], #1
    b       .dspr_loop

.dspr_shadow:
    cmp     r2, r2, ror #4
    beq     .dspr_singlec_sh

    tst     r9, #0x0800
    beq     .dspr_TileNorm_sh

    @ (r1=pdest, r2=pixels8, r3=pal) r4: scratch, r12: helper pattern
    TileFlipSh
    b       .dspr_loop

.dspr_TileNorm_sh:
    TileNormSh
    b       .dspr_loop

.dspr_singlec_sh:
    cmp     r2, #0xe0000000
    bcc     .dspr_SingleColor   @ normal tileline
    tst     r2, #0x10000000
    bne     .dspr_sh_sh
    TileSingleHi
    b       .dspr_loop

.dspr_sh_sh:
    TileSingleSh
    b       .dspr_loop


.dspr_cache:
    @ *(*hc)++ = (tile<<16)|((code&0x0800)<<5)|((sx<<6)&0x0000ffc0)|((code>>9)&0x30)|((sprite[0]>>24)&0xf);
    mov     r4, r8, lsl #16     @ tile
    tst     r9, #0x0800
    orrne   r4, r4, #0x10000    @ code&0x0800
    mov     r2, r2, lsl #22
    orr     r4, r4, r2, lsr #16 @ (sx<<6)&0x0000ffc0
    and     r2, r9, #0x6000
    orr     r4, r4, r2, lsr #9  @ (code>>9)&0x30
    mov     r3, r3, lsl #12
    ldr     r2, [r1]
    orr     r4, r4, r3, lsr #28 @ (sprite[0]>>24)&0xf

    str     r4, [r2], #4
    str     r2, [r1]

    ldmfd   sp!, {r4-r9,r11,lr}
    bx      lr

@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global DrawWindow @ int tstart, int tend, int prio, int sh // int *hcache

DrawWindow:
    stmfd   sp!, {r4-r11,lr}

    ldr     r11, =(Pico+0x22228)  @ Pico.video
    ldr     r10, =Scanline
    ldrb    r12, [r11, #3]        @ pvid->reg[3]

    ldr     r10, [r10]
    ldr     r4,  [r11, #12]
    mov     r5,  r10, lsr #3
    and     r10, r10, #7
    mov     r10, r10, lsl #1      @ r10=ty

    mov     r12, r12, lsl #10

    tst     r4, #1                @ 40 cell mode?
    andne   r12, r12, #0xf000     @ 0x3c<<10
    andeq   r12, r12, #0xf800
    addne   r12, r12, r5, lsl #7
    addeq   r12, r12, r5, lsl #6  @ nametab
    add     r12, r12, r0, lsl #2  @ +starttile

    ldr     r6, =rendstatus
    ldr     lr, =(Pico+0x10000) @ lr=Pico.vram
    ldrb    r6, [r6]

    @ fetch the first code now
    ldrh    r7, [lr, r12]

    ands    r6, r6, #2            @ we care about bit 1 only
    orr     r6, r6, r2
    bne     .dw_no_sameprio

    cmp     r2, r7, lsr #15
    ldmnefd sp!, {r4-r11,pc}      @ assume that whole window uses same priority

.dw_no_sameprio:
    orr     r6, r6, r3, lsl #8    @ shadow mode

    sub     r8, r1, r0
    mov     r8, r8, lsl #1        @ cells

    mvn     r9, #0                @ r9=prevcode=-1

    @ cache some stuff to avoid mem access
    ldr     r11,=(HighCol+8)
    add     r1, r11, r0, lsl #4 @ r1=pdest
    mov     r0, #0xf
    b       .dwloop_enter

    @ r4,r5 & r7 are scratch in this loop
.dwloop:
    add     r1, r1, #8
.dwloop_nor1:
    add     r12, r12, #2    @ halfwords
    ldrh    r7, [lr, r12]   @ r7=code (int, but from unsigned, no sign extend)
    subs    r8, r8, #1
    beq     .dwloop_end     @ done

    eor     r5, r6, r7, lsr #15
    tst     r5, #1
    orrne   r6, r6, #2      @ wrong pri
    bne     .dwloop

    cmp     r7, r9
    beq     .dw_samecode    @ we know stuff about this tile already

.dwloop_enter:
    mov     r9, r7          @ remember code

    movs    r2, r9, lsl #20 @ if (code&0x1000)
    mov     r2, r2, lsl #1
    add     r2, r10, r2, lsr #17 @ r2=addr=(code&0x7ff)<<4; addr+=ty
    eorcs   r2, r2, #0x0e   @ if (code&0x1000) addr^=0xe;

    and     r3, r9, #0x6000
    mov     r3, r3, lsr #9  @ r3=pal=((code&0x6000)>>9);

    ldr     r2, [lr, r2, lsl #1] @ pack=*(unsigned int *)(Pico.vram+addr); // Get 8 pixels

.dw_samecode:
    tst     r6, #0x100
    bne     .dw_shadow
.dw_shadow_done:
    tst     r2, r2
    beq     .dwloop              @ tileline blank

    cmp     r2, r2, ror #4
    beq     .dw_SingleColor @ tileline singlecolor 

    tst     r9, #0x0800
    beq     .dw_TileNorm

    @ (r1=pdest, r2=pixels8, r3=pal) r4: scratch, r0: helper pattern
    TileFlip r0
    b       .dwloop

.dw_TileNorm:
    TileNorm r0
    b       .dwloop

.dw_SingleColor:
    and     r4, r0, r2         @ #0x0000000f
    orr     r4, r3, r4
    orr     r4, r4, r4, lsl #8
    orr     r4, r4, r4, lsl #16
    mov     r5, r4
    stmia   r1!, {r4,r5}
    b       .dwloop_nor1       @ we incremeted r1 ourselves

.dw_shadow:
    tst     r6, #1             @ hi pri?
    orreq   r3, r3, #0x40
    beq     .dw_shadow_done
    ldr     r4, [r1]
    tst     r4, #0x00000080
    biceq   r4, r4, #0x000000c0
    tst     r4, #0x00008000
    biceq   r4, r4, #0x0000c000
    tst     r4, #0x00800000
    biceq   r4, r4, #0x00c00000
    tst     r4, #0x80000000
    biceq   r4, r4, #0xc0000000
    str     r4, [r1]
    ldr     r4, [r1,#4]
    tst     r4, #0x00000080
    biceq   r4, r4, #0x000000c0
    tst     r4, #0x00008000
    biceq   r4, r4, #0x0000c000
    tst     r4, #0x00800000
    biceq   r4, r4, #0x00c00000
    tst     r4, #0x80000000
    biceq   r4, r4, #0xc0000000
    str     r4, [r1,#4]
    b       .dw_shadow_done

.dwloop_end:
    ldr     r0, =rendstatus
    ldr     r1, [r0]
    and     r6, r6, #2
    orr     r1, r1, r6
    str     r1, [r0]

    ldmfd   sp!, {r4-r11,r12}
    bx      r12


@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


@ hilights 2 pixels in RGB444/BGR444 format
.macro TileDoShHi2Pixels444 reg
    mov     \reg, \reg, ror #12
    adds    \reg, \reg, #0x40000000
    orrcs   \reg, \reg, #0xf0000000
    mov     \reg, \reg, ror #28
    adds    \reg, \reg, #0x40000000
    orrcs   \reg, \reg, #0xf0000000
    mov     \reg, \reg, ror #28
    adds    \reg, \reg, #0x40000000
    orrcs   \reg, \reg, #0xf0000000
    mov     \reg, \reg, ror #24
    adds    \reg, \reg, #0x40000000
    orrcs   \reg, \reg, #0xf0000000
    mov     \reg, \reg, ror #28
    adds    \reg, \reg, #0x40000000
    orrcs   \reg, \reg, #0xf0000000
    mov     \reg, \reg, ror #28
    adds    \reg, \reg, #0x40000000
    orrcs   \reg, \reg, #0xf0000000
    mov     \reg, \reg, ror #12
.endm


.global FinalizeLineBGR444 @ int sh

FinalizeLineBGR444:
    stmfd   sp!, {r4-r6,lr}
    mov     r6, r0
    ldr     lr, =(Pico+0x22228)  @ Pico.video
    ldr     r0, =DrawLineDest
    ldrb    r12, [lr, #12]
    ldr     r0, [r0]
    sub     r3, lr, #0x128       @ r3=Pico.cram

    tst     r12, #1
    movne   r2, #320/4           @ len
    bne     .fl_no32colBGR444
    ldr     r4, =PicoOpt
    mov     r2, #256/4
    ldr     r4, [r4]
    tst     r4, #0x100
    addeq   r0, r0, #32*2

.fl_no32colBGR444:
    tst     r6, r6
    beq     .fl_noshBGR444

    ldr     r4, =HighPal

    ldrb    r12, [lr, #-0x1a]      @ 0x2220e ~ dirtyPal
    tst     r12, r12
    moveq   r3, r4
    beq     .fl_noshBGR444
    mov     r12, #0
    strb    r12, [lr, #-0x1a]

    mov     lr, #0x40/8
    @ copy pal:
.fl_loopcpBGR444:
    ldmia   r3!, {r1,r5,r6,r12}
    subs    lr, lr, #1
    stmia   r4!, {r1,r5,r6,r12}
    bne     .fl_loopcpBGR444

    @ shadowed pixels:
    mov     r12,    #0x0077
    orr     r12,r12,#0x0700
    orr     r12,r12,r12,lsl #16
    sub     r3, r3, #0x40*2
    add     r5, r4, #0x80*2
    mov     lr, #0x40/4
.fl_loopcpBGR444_sh:
    ldmia   r3!, {r1,r6}
    subs    lr, lr, #1
    and     r1, r12, r1, lsr #1
    and     r6, r12, r6, lsr #1
    stmia   r4!, {r1,r6}
    stmia   r5!, {r1,r6}
    bne     .fl_loopcpBGR444_sh

    @ hilighted pixels:
    sub     r3, r3, #0x40*2
    mov     lr, #0x40/2
.fl_loopcpBGR444_hi:
    ldr     r1, [r3], #4
    TileDoShHi2Pixels444 r1
    str     r1, [r4], #4
    subs    lr, lr, #1
    bne     .fl_loopcpBGR444_hi

    sub     r3, r4, #0x40*3*2


.fl_noshBGR444:
    ldr     r1, =(HighCol+8)
    mov     lr, #0xff
    mov     lr, lr, lsl #1

.fl_loopBGR444:

    ldr     r12, [r1], #4
    subs    r2, r2, #1

    and     r4, lr, r12, lsl #1
    ldrh    r4, [r3, r4]
    and     r5, lr, r12, lsr #7
    ldrh    r5, [r3, r5]
    and     r6, lr, r12, lsr #15
    ldrh    r6, [r3, r6]
    orr     r4, r4, r5, lsl #16

    and     r5, lr, r12, lsr #23
    ldrh    r5, [r3, r5]              @ 2c.i.
    orr     r5, r6, r5, lsl #16

    stmia   r0!, {r4,r5}
    bne     .fl_loopBGR444


    ldmfd   sp!, {r4-r6,lr}
    bx lr


@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


@ hilights 2 pixels in RGB555/BGR555 format
.macro TileDoShHi2Pixels555 reg
    adds    \reg, \reg, #0x40000000
    orrcs   \reg, \reg, #0xf0000000
    mov     \reg, \reg, ror #27
    adds    \reg, \reg, #0x40000000
    orrcs   \reg, \reg, #0xf0000000
    mov     \reg, \reg, ror #26
    adds    \reg, \reg, #0x40000000
    orrcs   \reg, \reg, #0xf0000000
    mov     \reg, \reg, ror #27
    adds    \reg, \reg, #0x40000000
    orrcs   \reg, \reg, #0xf0000000
    mov     \reg, \reg, ror #27
    adds    \reg, \reg, #0x40000000
    orrcs   \reg, \reg, #0xf0000000
    mov     \reg, \reg, ror #26
    adds    \reg, \reg, #0x40000000
    orrcs   \reg, \reg, #0xf0000000
    mov     \reg, \reg, ror #27
.endm


@ Convert 0000bbb0 ggg0rrr0
@ to      rrrrrggg gggbbbbb

@ r2,r3,r9 - scratch, lr = 0x001c001c, r8 = 0x00030003
.macro convRGB565 reg
    and     r2,   lr,   \reg,lsl #1
    and     r9,   r8,   \reg,lsr #2
    orr     r2,   r2,   r9           @ r2=red
    and     r3,   lr,   \reg,lsr #7
    and     r9,   r8,   \reg,lsr #10
    orr     r3,   r3,   r9           @ r3=blue
    and     \reg, \reg, lr,  lsl #3
    orr     \reg, \reg, \reg,lsl #3  @ green
    orr     \reg, \reg, r2,  lsl #11 @ add red back
    orr     \reg, \reg, r3           @ add blue back
.endm

vidConvCpyRGB565: @ void *to, void *from, int pixels
    stmfd   sp!, {r4-r9,lr}

    mov     r12, r2, lsr #3 @ repeats
    mov     lr, #0x001c0000
    orr     lr, lr,  #0x01c  @ lr == pattern 0x001c001c
    mov     r8, #0x00030000
    orr     r8, r8,  #0x003  @ lr == pattern 0x001c001c

.loopRGB565:
    ldmia   r1!, {r4-r7}
    subs    r12, r12, #1
    convRGB565 r4
    str     r4, [r0], #4
    convRGB565 r5
    str     r5, [r0], #4
    convRGB565 r6
    str     r6, [r0], #4
    convRGB565 r7
    str     r7, [r0], #4

    bgt     .loopRGB565

    ldmfd   sp!, {r4-r9,lr}
    bx      lr



.global FinalizeLineRGB555 @ int sh

FinalizeLineRGB555:
    stmfd   sp!, {r4-r8,lr}
    ldr     r5, =(Pico+0x22228)  @ Pico.video
    ldr     r4, =HighPal

    ldrb    r7, [r5, #-0x1a]     @ 0x2220e ~ dirtyPal
    mov     r6, r0
    mov     r1, #0
    tst     r7, r7
    beq     .fl_noconvRGB555
    strb    r1, [r5, #-0x1a]
    sub     r1, r5, #0x128       @ r1=Pico.cram
    mov     r0, r4
    mov     r2, #0x40
    bl      vidConvCpyRGB565

.fl_noconvRGB555:
    ldrb    r12, [r5, #12]
    ldr     r0, =DrawLineDest
    ldr     r0, [r0]

    tst     r12, #1
    movne   r2, #320/8           @ len
    bne     .fl_no32colRGB555
    ldr     r3, =PicoOpt
    mov     r2, #256/8
    ldr     r3, [r3]
    tst     r3, #0x100
    addeq   r0, r0, #32*2

.fl_no32colRGB555:
    mov     r3, r4
    tst     r6, r6
    beq     .fl_noshRGB555
    tst     r7, r7
    beq     .fl_noshRGB555

    @ shadowed pixels:
    mov     r12,    #0x008e
    orr     r12,r12,#0x7300
    orr     r12,r12,r12,lsl #16
    add     r4, r3, #0x40*2
    add     r5, r3, #0xc0*2
    mov     lr, #0x40/4
.fl_loopcpRGB555_sh:
    ldmia   r3!, {r1,r6}
    subs    lr, lr, #1
    and     r1, r12, r1, lsr #1
    and     r6, r12, r6, lsr #1
    stmia   r4!, {r1,r6}
    stmia   r5!, {r1,r6}
    bne     .fl_loopcpRGB555_sh

    @ hilighted pixels:
    sub     r3, r3, #0x40*2
    mov     lr, #0x40/2
.fl_loopcpRGB555_hi:
    ldr     r1, [r3], #4
    TileDoShHi2Pixels555 r1
    str     r1, [r4], #4
    subs    lr, lr, #1
    bne     .fl_loopcpRGB555_hi

    sub     r3, r3, #0x40*2


.fl_noshRGB555:
    ldr     r1, =(HighCol+8)
    mov     lr, #0xff
    mov     lr, lr, lsl #1

.fl_loopRGB555:

    ldr     r12, [r1], #4
    ldr     r7,  [r1], #4

    and     r4, lr, r12, lsl #1
    ldrh    r4, [r3, r4]
    and     r5, lr, r12, lsr #7
    ldrh    r5, [r3, r5]
    and     r6, lr, r12, lsr #15
    ldrh    r6, [r3, r6]
    orr     r4, r4, r5, lsl #16

    and     r5, lr, r12, lsr #23
    ldrh    r5, [r3, r5]
    and     r8, lr, r7, lsl #1
    ldrh    r8, [r3, r8]
    orr     r5, r6, r5, lsl #16

    and     r6, lr, r7, lsr #7
    ldrh    r6, [r3, r6]
    and     r12,lr, r7, lsr #15
    ldrh    r12,[r3, r12]
    orr     r8, r8, r6, lsl #16

    and     r6, lr, r7, lsr #23
    ldrh    r6, [r3, r6]             @ 1 cycle interlock here (r6)
    subs    r2, r2, #1
    orr     r12,r12, r6, lsl #16

    stmia   r0!, {r4,r5,r8,r12}
    bne     .fl_loopRGB555


    ldmfd   sp!, {r4-r8,lr}
    bx lr

@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@ utility
.global blockcpy @ void *dst, void *src, size_t n

blockcpy:
    stmfd   sp!, {r4,r5}
    mov     r2, r2, lsr #4
blockcpy_loop:
    ldmia   r1!, {r3-r5,r12}
    subs    r2, r2, #1
    stmia   r0!, {r3-r5,r12}
    bne     blockcpy_loop
    ldmfd   sp!, {r4,r5}
    bx      lr


.global blockcpy_or @ void *dst, void *src, size_t n, int pat

blockcpy_or:
    stmfd   sp!, {r4-r6}
    orr     r3, r3, r3, lsl #8
    orr     r3, r3, r3, lsl #16
    mov     r2, r2, lsr #4
blockcpy_loop_or:
    ldmia   r1!, {r4-r6,r12}
    subs    r2, r2, #1
    orr     r4, r4, r3
    orr     r5, r5, r3
    orr     r6, r6, r3
    orr     r12,r12,r3
    stmia   r0!, {r4-r6,r12}
    bne     blockcpy_loop_or
    ldmfd   sp!, {r4-r6}
    bx      lr


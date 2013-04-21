
#define DATA_ABORT_VECTOR      0xFFFF0010
#define DATA_ABORT_SUBSPCLR4   0xE25EF004



unsigned int doms, dav;
void unlock_mem_access()
{
    //doms =  __MRC(15, 0, 3, 0, 0);
    asm("mrc p15, 0, %0, c3, c0" : "=r"(doms));


    //__MCR(15, 0, 0xFFFFFFFF, 3, 0, 0);
    asm("mcr p15, 0, %0, c3, c0" ::"r"(0xFFFFFFFF));


    dav = *( (unsigned int *)( DATA_ABORT_VECTOR ) );
    *( (unsigned int *)( DATA_ABORT_VECTOR ) ) = DATA_ABORT_SUBSPCLR4;

    //__MCR(15, 0, DATA_ABORT_VECTOR, 7, 10, 1);
    asm("mcr p15, 0, %0, c7, c10, 1" ::"r"(DATA_ABORT_VECTOR));

    //__MCR(15, 0, DATA_ABORT_SUBSPCLR4, 7, 10, 4);
    asm("mcr p15, 0, %0, c7, c10, 4" ::"r"(DATA_ABORT_SUBSPCLR4));

    //__MCR(15, 0, DATA_ABORT_VECTOR, 7, 5, 1);
    asm("mcr p15, 0, %0, c7, c5, 1" ::"r"(DATA_ABORT_VECTOR));
}



void lock_mem_access()
{
    *( (unsigned int *)( DATA_ABORT_VECTOR ) ) = dav;

    //__MCR(15, 0, DATA_ABORT_VECTOR, 7, 10, 1);
    asm("mcr p15, 0, %0, c7, c10, 1" ::"r"(DATA_ABORT_VECTOR));

    //__MCR(15, 0, dav, 7, 10, 4);
    asm("mcr p15, 0, %0, c7, c10, 4" ::"r"(dav));

    //__MCR(15, 0, DATA_ABORT_VECTOR, 7, 5, 1);
    asm("mcr p15, 0, %0, c7, c5, 1" ::"r"(DATA_ABORT_VECTOR));

    //__MCR(15, 0, doms, 3, 0, 0);
    asm("mcr p15, 0, %0, c3, c0" ::"r"(doms));
}

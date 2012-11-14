#ifndef __ELF_H__
#define __ELF_H__

#define SWILIB_BASE 0x300000

#pragma diag_suppress=Ta035

#pragma swi_number=0x0B
__swi __arm int __elf_load(int argc, char *argv[], unsigned int *start, unsigned int *ret);

#pragma swi_number=0x0C
__swi __arm int __elf_unload(void *base);

#pragma swi_number=0x31
__swi __arm void __exekiller_run(void *exe);


#endif // __ELF_H__


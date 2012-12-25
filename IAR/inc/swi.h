#ifndef __SWI_H__
#define __SWI_H__


typedef struct {
  int (*evt_handler)(int event_id, int cmd, int subcmd);
  void *base; 
  void *userdata; 
}ELF_PARASITE_INFO;

#pragma diag_suppress=Ta035

#pragma swi_number=0x0
__swi __arm unsigned int *swihook_getlib();

#pragma swi_number=0x1
__swi __arm int swihook_setfunc(unsigned short swinum, unsigned int address);

#pragma swi_number=0x2
__swi __arm unsigned int swihook_getfunc(unsigned short swinum);

#pragma swi_number=0x3
__swi __arm int swihook_clearfunc(unsigned short swinum);

#pragma swi_number=0xB
__swi __arm int elf_load(char *filename, int argc, char *argv[], unsigned int *start, unsigned int *ret);


#endif // __SWI_H__


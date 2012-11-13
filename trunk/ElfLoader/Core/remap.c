#include "intrinsics.h"
#include "string.h"

#include "remap.h"
#include "fwlib.h"


unsigned int *__mmu_coarse_malloc()
{
 unsigned int mem_normal  = (int)fwlib->malloc(MMU_COARSE_TABLE_SIZE + MMU_COARSE_TABLE_SIZE + 4);
 if (!mem_normal) return 0;
 unsigned int *mem_align  = (unsigned int *)((mem_normal & ~ ( MMU_COARSE_TABLE_SIZE - 1 )) + MMU_COARSE_TABLE_SIZE);
 memset(mem_align, 0, MMU_COARSE_TABLE_SIZE);
 mem_align[MMU_COARSE_TABLE_SIZE / 4] = mem_normal;
 return mem_align;
}

void __mmu_coarse_free(unsigned int *mem)
{
 if (mem)
  {
    void *memory = (void *)mem[MMU_COARSE_TABLE_SIZE / 4];
    if (memory) fwlib->free(memory);
  }
}


unsigned char *__mmu_coarsepage_malloc()
{
 return (unsigned char *)__mmu_coarse_malloc();
}

void __mmu_coarsepage_free(unsigned char *mem)
{
 __mmu_coarse_free((unsigned int *)mem);
}

void __mmu_coarse_set(unsigned int virt_address, unsigned int phys_address)
{
 int doms =  __MRC(15, 0, 3, 0, 0);
 __MCR(15, 0, 0xFFFFFFFF, 3, 0, 0);
  
 unsigned int *m  = (unsigned int *)__MRC(15, 0, 2, 0, 0);
 
  m[( ( virt_address >> 20) & 0xFFF )] = (int)phys_address | 0x01;
 
 __MCR(15, 0, doms, 3, 0, 0);
}


void __mmu_coarsepage_set(unsigned int *coarsepage, unsigned int virt_address, unsigned int phys_address)
{
 int doms =  __MRC(15, 0, 3, 0, 0);
 __MCR(15, 0, 0xFFFFFFFF, 3, 0, 0);
  
 
  coarsepage[( ( virt_address >> 12) & 0xFF )] = (int)phys_address | 0xFFE;
 
 __MCR(15, 0, doms, 3, 0, 0);
}




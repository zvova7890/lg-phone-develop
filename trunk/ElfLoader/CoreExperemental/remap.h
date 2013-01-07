#ifndef __REMAP_H__
#define __REMAP_H__

#define MMU_MAIN_TABLE_SIZE   0x4000
#define MMU_COARSE_TABLE_SIZE 0x1000

#define MMU_SECTION_SIZE      0x100000
#define MMU_PAGE_SIZE         0x1000


unsigned int *__mmu_coarse_malloc();
void __mmu_coarse_free(unsigned int *mem);
unsigned char *__mmu_coarsepage_malloc();
void __mmu_coarsepage_free(unsigned char *mem);

void __mmu_coarse_set(unsigned int virt_address, unsigned int phys_address);
void __mmu_coarsepage_set(unsigned int *coarsepage, unsigned int virt_address, unsigned int phys_address);


#endif // __REMAP_H__


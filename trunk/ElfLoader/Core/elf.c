#include <string.h>

#include "elf.h"

#include "swihook.h"
#include "fwlib.h"


int __elf_load(char *filename, void *param1, void *param2, void *param3, unsigned int *start, unsigned int *ret)
{
  Elf32_Ehdr ehdr;			// ��������� �����
  Elf32_Phdr phdrs[MAX_PHNUM];	        // ��������� �������
  Elf32_Word dyn[DT_BIND_NOW+1];	// ���� ������������ ������
  
  char *reloc, *base;
  unsigned long minadr=(unsigned long)-1, maxadr=0;
  int n,m;
  
  if (start) *start = 0;
  if (ret) *ret = 0;
  
  memset(dyn, 0, sizeof(dyn));
    
  int fin;
  if ((fin=fwlib->open(filename, FILE_OPEN_READ))<0) return -1; // �� ����������� ����
  if (fwlib->read(fin, &ehdr, sizeof(Elf32_Ehdr))!=sizeof(Elf32_Ehdr))    // �� �������� ����
  {
    fwlib->close(fin); 
    return -2;
  }
  
  
  if (*((long *)ehdr.e_ident) != 0x464C457F) // �� � �� ���� ��� ����� /* \x7FELF */
  {                               
    fwlib->close(fin);
    return -3;
  }
  
  // ��������� ��� ����������� �������� � �������� ����������� ������� � RAM
  if (ehdr.e_phnum > MAX_PHNUM) return -9; // ������� ����� ���������� ���������
  for(n = 0; n < ehdr.e_phnum; n++)
  {
    if (fwlib->seek(fin, FILE_SEEK_SET, ehdr.e_phoff+n*ehdr.e_phentsize))
     {
       fwlib->close(fin); 
       return -4;
     }	// �� ������ ����������� ���������
    if (fwlib->read(fin, &phdrs[n], sizeof(Elf32_Phdr))!=sizeof(Elf32_Phdr))
    {
      fwlib->close(fin); 
      return -5;
    }  // �� �������� ����������� ���������
    
    if (phdrs[n].p_type==PT_LOAD)
    {
      if (minadr > phdrs[n].p_vaddr) minadr=phdrs[n].p_vaddr;
      if (maxadr < (phdrs[n].p_vaddr+phdrs[n].p_memsz))
      {
	maxadr=phdrs[n].p_vaddr+phdrs[n].p_memsz;
      }
    }
  }
  
  // ������� ��� ������� � ������� ��
  if ((base=(char *)fwlib->malloc(maxadr-minadr))==0) // �� ���������� ������ ��� ���� (�������� ��������� RAM)
  {
    fwlib->close(fin);
    return -13;
  }
  
  // ��������� ���������� �������
  memset(base, 0, maxadr-minadr);
  
  // ����� ���� ���������
  for(n=0; n < ehdr.e_phnum; n++)
  { 
    if (fwlib->seek(fin, FILE_SEEK_SET, phdrs[n].p_offset))
    {
      fwlib->close(fin);
      fwlib->free(base); 
      return -6;
    } // �� ������ ������������ �������

    switch (phdrs[n].p_type)
    {
     case PT_LOAD:
       
      // �������� ����������� �������� � �������� ������ 0
      if (phdrs[n].p_filesz!=0) 
       {
	if (fwlib->read(fin, &base[phdrs[n].p_vaddr-minadr], phdrs[n].p_filesz)!= phdrs[n].p_filesz)
        {
          fwlib->close(fin); 
          fwlib->free(base); 
          return -10;
        } // �� �������� ����������� �������
       }
        break;
     case PT_DYNAMIC:
       
      // ������� ������������ ������
      if ((reloc=(char *)fwlib->malloc(phdrs[n].p_filesz))==0) // �� ���������� ������ ��� ������������ �������
      {
	fwlib->close(fin);
	fwlib->free(base);
	return -7;
      }
      
      if (fwlib->read(fin, reloc, phdrs[n].p_filesz)!=phdrs[n].p_filesz)
      {
        fwlib->close(fin); 
        fwlib->free(reloc); 
        fwlib->free(base); 
        return -8;
      }	// �� �������� ������������ �������

      // ������� ��� ���� �� ������������ ������
      m=0;
      while (((Elf32_Dyn *)reloc)[m].d_tag!=DT_NULL)
       {
	if (((Elf32_Dyn *)reloc)[m].d_tag<=DT_BIND_NOW) 
        {
	  dyn[((Elf32_Dyn *)reloc)[m].d_tag]=((Elf32_Dyn *)reloc)[m].d_val;
	}
	m++;
       }
      m=0;
      
      // �������� ��������� REL
      if (dyn[DT_RELSZ]!=0)
       {
	while (m*sizeof(Elf32_Rel)<dyn[DT_RELSZ])
         {

          Elf32_Word ri=ELF32_R_TYPE(((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_info);
          if (ri!=R_ARM_RBASE)
          {
            if (ri==R_ARM_RABS32)
            {
              *((long*)(base+((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_offset))+=(long)base-minadr;
            }
            else
              switch(ri)
               {
                case R_ARM_NONE: break; // ������ ����������
                case R_ARM_ABS32:

                *((long*)(base+((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_offset-minadr))+=(long)base;
                break;
                
                case R_ARM_RELATIVE: // ������ ������ �� minadr � ������ �������� ����������� ������
                  
                *((long*)(base+((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_offset-minadr))+=(long)base-minadr;
                break;  // ����������
                case R_ARM_RBASE: break;
                
                default: 	// ����������� ��� ���������
                  fwlib->close(fin);
                  fwlib->free(base);
                  fwlib->free(reloc);
                  return -12;
               }
           }
	  m++;
	 }
       }

       fwlib->free(reloc);
       break;
      
      default:	// ����������� ��� ����������� ��������
       fwlib->close(fin);
       fwlib->free(base);
       return -11;
    }
  }

  fwlib->close(fin);
  {
    //extern __arm void ExecuteIMB(void);
    //ExecuteIMB();	
  }
  long r = ((TElfEntry *)(base+ehdr.e_entry-minadr))(filename, base, param1, param2, param3);
  
  if (start) *start = (unsigned int)base;
  if (ret) *ret = (unsigned int)r;
  
  
  return 0;
}


void __elf_unload(void *base)
{
 if (base)
   fwlib->free(base);
}

void __elf_init()
{
 __disable_interrupt();
 __swihook_setfunc(SWINUM_ELFLOAD, (int)__elf_load);
 __swihook_setfunc(SWINUM_ELFUNLOAD, (int)__elf_unload);
 __enable_interrupt();
}

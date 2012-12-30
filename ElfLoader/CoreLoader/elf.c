#include <string.h>
#include "fwlib.h"
#include "elf.h"


__thumb long elfload(char *filename, void *param1, void *param2, void *param3)
{
  Elf32_Ehdr ehdr;			// ��������� �����
  Elf32_Phdr phdrs[MAX_PHNUM];	        // ��������� �������
  Elf32_Word dyn[DT_BIND_NOW+1];	// ���� ������������ ������
  
  char *reloc, *base;
  unsigned long minadr=(unsigned long)-1, maxadr=0;
  int n,m;
  
  memset(dyn, 0, sizeof(dyn));
    
  int fin;
  if ((fin=fw.open(filename, FILE_OPEN_MODE_READ))<0) return -1; // �� ����������� ����
  if (fw.read(fin, &ehdr, sizeof(Elf32_Ehdr))!=sizeof(Elf32_Ehdr))    // �� �������� ����
  {
    fw.close(fin); 
    return -2;
  }
  
  
  if (*((long *)ehdr.e_ident) != 0x464C457F) // �� � �� ���� ��� ����� /* \x7FELF */
  {                               
    fw.close(fin);
    return -3;
  }
  
  // ��������� ��� ����������� �������� � �������� ����������� ������� � RAM
  if (ehdr.e_phnum > MAX_PHNUM) return -9; // ������� ����� ���������� ���������
  for(n = 0; n < ehdr.e_phnum; n++)
  {
    if (fw.seek(fin, FILE_SEEK_MODE_SET, ehdr.e_phoff+n*ehdr.e_phentsize))
     {
       fw.close(fin); 
       return -4;
     }	// �� ������ ����������� ���������
    if (fw.read(fin, &phdrs[n], sizeof(Elf32_Phdr))!=sizeof(Elf32_Phdr))
    {
      fw.close(fin); 
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
  if ((base=(char *)fw.malloc(maxadr-minadr))==0) // �� ���������� ������ ��� ���� (�������� ��������� RAM)
  {
    fw.close(fin);
    return -13;
  }
  
  // ��������� ���������� �������
  memset(base, 0, maxadr-minadr);
  
  // ����� ���� ���������
  for(n=0; n < ehdr.e_phnum; n++)
  { 
    if (fw.seek(fin, FILE_SEEK_MODE_SET, phdrs[n].p_offset))
    {
      fw.close(fin);
      fw.free(base); 
      return -6;
    } // �� ������ ������������ �������

    switch (phdrs[n].p_type)
    {
     case PT_LOAD:
       
      // �������� ����������� �������� � �������� ������ 0
      if (phdrs[n].p_filesz!=0) 
       {
	if (fw.read(fin, &base[phdrs[n].p_vaddr-minadr], phdrs[n].p_filesz)!= phdrs[n].p_filesz)
        {
          fw.close(fin); 
          fw.free(base); 
          return -10;
        } // �� �������� ����������� �������
       }
        break;
     case PT_DYNAMIC:
       
      // ������� ������������ ������
      if ((reloc=(char *)fw.malloc(phdrs[n].p_filesz))==0) // �� ���������� ������ ��� ������������ �������
      {
	fw.close(fin);
	fw.free(base);
	return -7;
      }
      
      if (fw.read(fin, reloc, phdrs[n].p_filesz)!=phdrs[n].p_filesz)
      {
        fw.close(fin); 
        fw.free(reloc); 
        fw.free(base); 
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
                  fw.close(fin);
                  fw.free(base);
                  fw.free(reloc);
                  return -12;
               }
           }
	  m++;
	 }
       }

       fw.free(reloc);
       break;
      
      default:	// ����������� ��� ����������� ��������
       fw.close(fin);
       fw.free(base);
       return -11;
    }
  }

  fw.close(fin);
  {
    //extern __arm void ExecuteIMB(void);
    //ExecuteIMB();	
  }
  ((TElfEntry *)(base+ehdr.e_entry-minadr))(filename,param1,param2,param3);
  return 0;
}

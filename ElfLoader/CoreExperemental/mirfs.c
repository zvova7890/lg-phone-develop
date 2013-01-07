#include <string.h>
#include <stdio.h>
#include <intrinsics.h>

#include "corelib.h"
#include "core.h"
#include "mirfs.h"

char __mirfs_folder[256];

void __mirfs_init(char *repfs_folder)
{
 unsigned int   *mirfs_chk_address  = (unsigned int *)MIRFS_CHECK_ADDRESS;
 unsigned int   *mirfs_blx_address  = (unsigned int *)MIRFS_THUMB_BLX_ADDRESS;
 void           *mirfs_j32_address  = (unsigned int *)MIRFS_J32_ADDRESS;
 
 strcpy(__mirfs_folder, repfs_folder);
 
 __disable_interrupt();
 int doms =  __MRC(15, 0, 3, 0, 0);
 __MCR(15, 0, 0xFFFFFFFF, 3, 0, 0);
   
 mirfs_blx_address[0]  = MIRFS_THUMB_BLX_OPCODE;
 mirfs_chk_address[0]  = MIRFS_THUMB_MOVR01_OPCODE;
 
 memcpy(mirfs_j32_address, (void *)&__mirfs_j32, MIRFS_J32_SIZE);
   
 __MCR(15, 0, doms, 3, 0, 0);
 __enable_interrupt();
}

void __mirfs_changer(char *path_dest, char *path_src)
{

 if (
     !strncmp(path_src, FILE_PATH_SYS, 4) || 
     !strncmp(path_src, FILE_PATH_CUS, 4)
    )
  {
   char            *path_rep;
   FS_INFO          file;
    
   path_rep = mem_malloc(4096);
    
   strcpy(path_rep, __mirfs_folder);
   strcat(path_rep, path_src);
   
   if (!fs_getinfo(path_rep, &file))
    {
      if (!(file.attr & FS_ATTR_FOLDER)) {
       //__core_lprintf("repfs: %s -> %s\r\n", path_src, path_dest); 
       strcpy(path_dest, path_rep);
      }
    }
   
   if (path_rep)  mem_free(path_rep);
  }
}



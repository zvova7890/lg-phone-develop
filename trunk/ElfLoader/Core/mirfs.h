#ifndef __MIRFS_H__
#define __MIRFS_H__


/* Mirrored File System */

void __mirfs_init(char *repfs_folder);
__arm void __mirfs_changer(char *path_dest, char *path_src);


extern void __mirfs_j32();


#endif // __MIRFS_H__

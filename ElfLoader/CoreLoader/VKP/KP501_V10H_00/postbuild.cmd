elf2vkp.exe coreloader.elf -vkp coreloader_fls.vkp -pd clheader.txt -ff ff.fls -sa PATCH_INITHOOK=0x195748 -sa CODE,DATA_C=0x7623F8
elf2vkp.exe coreloader.elf -vkp coreloader_bin.vkp

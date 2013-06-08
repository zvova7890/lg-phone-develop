

#include <Api/ApiLinkLib/ApiLink.h>
#include <stdio.h>




T_CMD_INFO *T_CMD_ALLOC (int Size)
{
    printf("T_CMD_ALLOC(%d)\n", Size);
    return 0;
}


void T_CMD_FREE (T_CMD_INFO* rc)
{

}


void T_CMD_MEMSET (T_CMD_INFO* rc, int c, int ParamSize)
{

}

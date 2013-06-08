
#ifndef __T_CMD_H__
#define __T_CMD_H__



typedef struct
{
	unsigned	Msg;
	void*		Param;
} T_CMD_INFO;




T_CMD_INFO *T_CMD_ALLOC (int Size);
void T_CMD_FREE (T_CMD_INFO* rc);
void T_CMD_MEMSET (T_CMD_INFO* rc, int c, int ParamSize);



#endif /* __T_CMD_H__ */




#include <stdio.h>
#include <string.h>







int main()
{
  int i = 54;
  int end = 134;
  
  
  FILE *fp = fopen("ololo.h", "w+");
  
  
  for(;i < end; ++i)
  {
    fprintf(fp, "	const void *				__0x%x;\n", i*4);
  }
  
  fclose(fp);
  
}




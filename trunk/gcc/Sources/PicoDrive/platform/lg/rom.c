
#include <stdio.h>
#include <stdlib.h>
#include "../../Pico/PicoInt.h"


unsigned char *RomData=NULL;
int RomLen=0;


static int _Byteswap(unsigned char *data,int len)
{
  int i=0;

  if (len<2) return 1; // Too short

  do
  {
    unsigned short *pd=(unsigned short *)(data+i);
    int word=*pd; // Get word

    word=(word<<8)|(word>>8); // Byteswap it
    *pd=(unsigned short)word; // Put word
    i+=2;
  }
  while (i+2<=len);

  return 0;
}

// Interleve a 16k block and byteswap
static int InterleveBlock(unsigned char *dest,unsigned char *src)
{
  int i=0;
  for (i=0;i<0x2000;i++) dest[(i<<1)  ]=src[       i]; // Odd
  for (i=0;i<0x2000;i++) dest[(i<<1)+1]=src[0x2000+i]; // Even
  return 0;
}


// Decode a SMD file
static int DecodeSmd(unsigned char *data,int len)
{
  unsigned char *temp=NULL;
  int i=0;

  temp=(unsigned char *)malloc(0x4000);
  if (temp==NULL) return 1;
  memset(temp,0,0x4000);

  // Interleve each 16k block and shift down by 0x200:
  for (i=0; i+0x4200<=len; i+=0x4000)
  {
    InterleveBlock(temp,data+0x200+i); // Interleve 16k to temporary buffer
    memcpy(data+i,temp,0x4000); // Copy back in
  }

  free(temp);
  return 0;
}

int RomLoad(const char *RomName)
{
  FILE *file=NULL;
  const char *name=NULL;
  int nameLen=0;
  int fileLen=0,space=0;

  name = RomName;

  file=fopen(name,"rb"); if (file==NULL) return 1;

  nameLen=strlen(name);

  {
    // Find out the length of the file:
    fseek(file,0,SEEK_END); fileLen=ftell(file);
    fseek(file,0,SEEK_SET);
  }

  // Allocate space for it:
  space=(fileLen+0x3fff)&~0x3fff;

  RomData=(unsigned char *)malloc(space);
  if (RomData==NULL) { fclose(file); return 1; }
  memset(RomData,0,space);

  // Read in file:
  fread(RomData,1,fileLen,file);

  fclose(file);

  RomLen=fileLen;

  // Check for SMD:
  if ((fileLen&0x3fff)==0x200)
  {
    // Decode and byteswap:
    DecodeSmd(RomData,RomLen);
    RomLen-=0x200;
  }
  else
  {
    // Just byteswap:
    _Byteswap(RomData,RomLen);
  }

  PicoCartInsert(RomData,RomLen);
  return 0;
}

void RomFree()
{
//  PicoCartInsert(NULL,0); // Unplug rom

  if (RomData) free(RomData);
  RomData=NULL; RomLen=0;
}


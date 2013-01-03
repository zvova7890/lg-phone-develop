int char8to16(int c)
{
  if (c<168) return (c);
  c-=168;
  if (!c)  c=1;
  else if (c<24) 
  {
    if (c==2) c=4;
    else if (c==10) c=6;
    else if (c==11) c=0x56;
    else if (c==16) c=0x51;
    else if (c==18) c=0x54;
    else if (c==23) c=0x57;
    else return (c);
  }
  else if (c>87) return (c);
    else c-=8;
  c+=0x400;
  return (c); 
}

int char16to8(int c)
{
  if (c<0x400) return (c);
  c-=0x400;
  if (c<16)
  {
    if (c==1) c=0;
    else if (c==4) c=2;
    else if (c==6) c=10;
    else return (c);
  }
  else if (c>79)
  {
    if (c==0x51) c=16;
    else if (c==0x54) c=18;
    else if (c==0x56) c=11;
    else if (c==0x57) c=23;
    else return (c);
  }
  else c+=8;
  c+=168;
  return (c);
}


void cp1251_2_utf8(char *dest, char *src, int len)
{
 int p = 0;
 for (int i = 0; i < len; i++)
  {
   if (src[i] == '\0') {
     dest[i + p] = '\0'; return;
   } else
      {
       if ( src[i] < 0x80 )
        {
         dest[i + p] = src[i];
        } else
           {
            //Unicode
            unsigned short s = char8to16(src[i]);
            dest[i + 0 + p] = ( ( s >> 6 ) & 0x1F ) | 0xD0;
            dest[i + 1 + p] = (   s        & 0x3F ) | 0x80;
            p++;
           }
      }
  }
  dest[len - 1 + p] = '\0';
}

void cp1251_2_utf16(unsigned short *dest, const char *src)
{
 for (int i = 0; ; i++)
  {
    if (src[i] == '\0') { dest[i] = 0x0000; return; }
     else dest[i] = char8to16(src[i]);
  }
}

void utf16_2_cp1251(char *dest, const unsigned short *src)
{
 for (int i = 0; ; i++)
  {
    if (src[i] == 0x0000) { dest[i] = 0x00; return; }
     else dest[i] = char16to8(src[i]);
  }
}



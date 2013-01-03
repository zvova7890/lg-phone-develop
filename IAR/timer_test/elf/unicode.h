#ifndef __UNICODE_H__
#define __UNICODE_H__

void cp1251_2_utf8(char *dest, char *src, int len);
void cp1251_2_utf16(unsigned short *dest, const char *src);
void utf16_2_cp1251(char *dest, const unsigned short *src);

#endif // __UNICODE_H__


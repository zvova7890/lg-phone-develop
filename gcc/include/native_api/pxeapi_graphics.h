#ifndef __PXEAPI_GRAPHICS_H__
#define __PXEAPI_GRAPHICS_H__

#include <wchar.h>
#include "pxeapi_macro.h"

/* *****************************************************************************

 � ���� ����� ������������ ����������� API, ��������� � LG KP501 V10H_00.
 ������� � ���������:
  ������ ����� aka Dimadze

***************************************************************************** */

//�������������� ����� �������
#define ChangeGDI                 Graphics_ChangeGDI
#define Repaint                   Graphics_Repaint
#define GetScreenBuffer           Graphics_GetScreenBuffer
#define GetScreenWidth            Graphics_GetScreenWidth
#define GetScreenHeight           Graphics_GetScreenHeight
#define GetScreenDepth            Graphics_GetScreenDepth
#define DrawRect                  Graphics_DrawRect
#define DrawLine                  Graphics_DrawLine
#define DrawThickRect             Graphics_DrawThickRect
#define DrawFillRect              Graphics_DrawFillRect
#define DrawThickRect             Graphics_DrawThickRect
#define DrawRoundRect             Graphics_DrawRoundRect
#define DrawFillRoundRect         Graphics_DrawFillRoundRect
#define DrawBitmap                Graphics_DrawBitmap
#define DrawString                Graphics_DrawString
#define DrawStringSetColor        Graphics_DrawStringSetColor
#define DrawStringSetOutLine      Graphics_DrawStringSetOutLine
#define MakeRGBColor              Graphics_MakeRGBColor

/* ************************************************************************** */

#define DISPLAY_WITDH         240
#define DISPLAY_HEIGHT        400
#define STATUSBAR_HEIGHT      22

#define GDI_STATE_NORMAL      0
#define GDI_STATE_LANDSCAPE   1

//����� ���������� ��� ����������� �-�� (��������� ������)
__pxeapi int Graphics_ChangeGDI(int state)
__pxe_api_ret_onearg(0x1C/4, 0x04/4, int, state)

//����������� ������
__pxeapi void Graphics_Repaint()
__pxe_api_void_noargs(0x1C/4, 0x0C/4)

//��������� ������ ������������ ������
__pxeapi void *Graphics_GetScreenBuffer()
__pxe_api_ret_noargs(0x1C/4, 0x18/4, void *)

//��������� ������ ������ � ����������� �� ���������
__pxeapi unsigned short Graphics_GetScreenWidth()
__pxe_api_ret_noargs(0x1C/4, 0x20/4, unsigned short)

//��������� ������ ������ � ����������� �� ���������
__pxeapi unsigned short Graphics_GetScreenHeight()
__pxe_api_ret_noargs(0x1C/4, 0x24/4, unsigned short)

//��������� ������� ������ (���������� ��� �� �������)
__pxeapi unsigned char Graphics_GetScreenDepth()
__pxe_api_ret_noargs(0x1C/4, 0x28/4, unsigned char)

//��������� �����
__pxeapi int Graphics_DrawLine(short x1, short y1, short x2, short y2, unsigned int color)
__pxe_api_ret(0x1C/4, 0x68/4, int, x1, y1, x2, y2, color)

//��������� ������ ��������������
__pxeapi int Graphics_DrawRect(short x1, short y1, short x2, short y2, unsigned int color)
__pxe_api_ret(0x1C/4, 0x78/4, int, x1, y1, x2, y2, color)

//��������� ������ �������������� � ���������� ������� �����, ������� ������ �� �������� ���������� ����
__pxeapi int Graphics_DrawThickRect(short x1, short y1, short x2, short y2, unsigned int color, int thickness)
__pxe_api_ret(0x1C/4, 0x7C/4, int, x1, y1, x2, y2, color, thickness, -1, 32)

//��������� ������������ ��������������
__pxeapi int Graphics_DrawFillRect(short x1, short y1, short x2, short y2, unsigned int color)
__pxe_api_ret(0x1C/4, 0x80/4, int, x1, y1, x2, y2, color)

//��������� ������ �������������� �� ������������ ������
__pxeapi int Graphics_DrawRoundRect(short x1, short y1, short x2, short y2, int x_rnd, int y_rnd, unsigned int color)
__pxe_api_ret(0x1C/4, 0x84/4, int, x1, y1, x2, y2, x_rnd, y_rnd, color)

//��������� ������������ �������������� �� ������������ ������
__pxeapi int Graphics_DrawFillRoundRect(short x1, short y1, short x2, short y2, int x_rnd, int y_rnd, unsigned int color)
__pxe_api_ret(0x1C/4, 0x8C/4, int, x1, y1, x2, y2, x_rnd, y_rnd, color)

//��������� ������� (��������) ��� (����-)������������
__pxeapi int Graphics_DrawBitmap(int x, int y, int w, int h, int depth, void *bitmap)
__pxe_api_ret(0x1C/4, 0xC8/4, int, x, y, w, h, depth, bitmap)

//��������� ��������� ������
__pxeapi int Graphics_DrawString(int x, int y, const wchar_t *text, unsigned char font)
__pxe_api_ret(0x1C/4, 0xF4/4, int, x, y, text, font)

//����� ���� ������, ������� ����� ����� ���������
__pxeapi void Graphics_DrawStringSetColor(unsigned int color)
__pxe_api_void_onearg(0x1C/4, 0x13C/4, color)

//����� ��� ������������� ������, ������� ����� ����� ���������
__pxeapi void Graphics_DrawStringSetOutLine(int outline)
__pxe_api_void_onearg(0x1C/4, 0x15C/4, outline)

//��������� �������� ����� �� ��� ������� RGB
__pxeapi unsigned int Graphics_MakeRGBColor(unsigned char r, unsigned char g, unsigned char b)
__pxe_api_ret(0x1C/4, 0x16C/4, unsigned int, r, g, b)


#endif // __PXEAPI_GRAPHICS_H__



#ifndef __PXEAPI_GRAPHICS_H__
#define __PXEAPI_GRAPHICS_H__

#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif


/* *****************************************************************************

 В этом файле представлено графическое API, найденное в LG KP501 V10H_00.
 Найдено и оформлено:
  Шамаев Дамир aka Dimadze

***************************************************************************** */

//Альтернативные имена функций
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

//Переворот экрана
int Graphics_ChangeGDI(int state);

void Graphics_Repaint();

//Получение адреса графического буфера
void *Graphics_GetScreenBuffer();

//Получение ширины экрана в зависимости от состояния
unsigned short Graphics_GetScreenWidth();

//Получение высоты экрана в зависимости от состояния
unsigned short Graphics_GetScreenHeight();

//Получение глубины экрана (количество бит на пиксель)
unsigned char Graphics_GetScreenDepth();


#ifdef __cplusplus
}
#endif


#endif // __PXEAPI_GRAPHICS_H__



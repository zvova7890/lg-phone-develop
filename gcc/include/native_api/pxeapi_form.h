#ifndef __PXEAPI_FORMS_H__
#define __PXEAPI_FORMS_H__

/* *****************************************************************************

 � ���� ����� ������������ API ��� ������ � �������, ��������� � LG KP501 V10H_00.
 ������� � ���������:
  ������ ����� aka Dimadze

***************************************************************************** */

//�������������� ����� �������
#define CreateForm                  Form_Create
#define DestroyForm                 Form_Destroy
#define SetFormPosition             Form_SetPosition
#define SetFormTitleText            Form_SetTitleText
#define SetFormTitleFont            Form_SetTitleFont
#define SetFormTitleHeight          Form_SetTitleHeight
#define SetFormSoftKeys             Form_SetSoftKeys
#define SetFormCreateList           Form_CreateList
#define SetFormListStyle            Form_SetListStyle
#define AddFormListItem             Form_AddListItem
#define GetSelectFormListItem       Form_GetSelectListItem
#define FormTouchHandling           Form_TouchHandling
#define FormTouchHandling2          Form_TouchHandling2
#define FormTouchHandling3          Form_TouchHandling3


/* ************************************************************************** */


#define FORM_TITLE_FONT_NORMAL    24
#define FORM_TITLE_HEIGHT_NORMAL  42

//�������� �����
__pxeapi int Form_Create()
__pxe_api_ret_noargs(0x88/4, 0x00/4, int)

//����������� �����
__pxeapi int Form_Destroy(int form_handle)
__pxe_api_ret_onearg(0x88/4, 0x04/4, int, form_handle)

//������������ ������� �����
__pxeapi int Form_SetPosition(int form_handle, short x, short y)
__pxe_api_ret(0x90/4, 0x10/4, int, form_handle, x, y)

//������������ ��������� �����
__pxeapi int Form_SetTitleText(int form_handle, const unsigned short *title)
__pxe_api_ret(0x90/4, 0x2C/4, int, form_handle, title)

//������������ ������ ��������� �����
__pxeapi int Form_SetTitleFont(int form_handle, unsigned char font)
__pxe_api_ret(0x90/4, 0x30/4, int, form_handle, font)

//������������ ������ ��������� �����
__pxeapi int Form_SetTitleHeight(int form_handle, int height)
__pxe_api_ret(0x90/4, 0x34/4, int, form_handle, height)

//������������ ����-������ � ����� (�� 3-�) 
__pxeapi int Form_SetSoftKeys(int form_handle, const unsigned  short *soft1, const unsigned short *soft2, const unsigned short *soft3)
__pxe_api_ret(0x88/4, 0x60/4, int, form_handle, soft1, soft2, soft3)

//�������� ������ � �����
__pxeapi int Form_CreateList(int form_handle, int arg1, int arg2, int arg3, int arg4, int arg5)
__pxe_api_ret(0x88/4, 0x34/4, int, form_handle, arg1, arg2, arg3, arg4, arg5);

//��������� ����� ������
__pxeapi int Form_SetListStyle(int list_handle, int arg1, int style)
__pxe_api_ret(0x90/4, 0x08/4, int, list_handle, arg1, style)

//���������� ������ �������� � ������
__pxeapi int Form_AddListItem(int list_handle, const unsigned short *name, int item_id, int arg_FFFF)
__pxe_api_ret(0xB0/4, 0x78/4, int, list_handle, name, item_id, arg_FFFF);

//��������� ���������� �������� � ������
__pxeapi int Form_GetSelectListItem(int list_handle)
__pxe_api_ret_onearg(0xB0/4, 0x58/4, int, list_handle);

//���������� ������ � ������� ��������� #1
__pxeapi int Form_TouchHandling(int form_handle, int arg_0)
__pxe_api_ret(0x74/4, 0xB4/4, int, form_handle, arg_0)

//���������� ������ � ������� ��������� #2
__pxeapi int Form_TouchHandling2(int form_handle, int action, int arg_0)
__pxe_api_ret(0x74/4, 0xB8/4, int, form_handle, action, arg_0)

//���������� ������ � ������� ��������� #3
__pxeapi int Form_TouchHandling3(int form_handle, int action, int x, int y, int arg_4)
__pxe_api_ret(0x74/4, 0xC4/4, int, form_handle, action, x, y, arg_4)

#endif // __PXEAPI_FORMS_H__



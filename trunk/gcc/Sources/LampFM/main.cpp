
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

#include <fs.h>
#include <loader.h>
#include <mem.h>
#include <pxeapi_graphics.h>
#include <pxeapi.h>
#include <taskapi.h>
#include <wchar.h>
#include <unistd.h>
#include <fcntl.h>

#include <nucleus.h>

#include "png_ops.h"

#include <gl.h>

#include <Widget.h>
#include "FileViewWidget.h"
#include "GlobalMenuButton.h"
#include "ExtManager.h"
#include "FileViewWidgetListEngine.h"
#include "LocalFSProtocol.h"
#include "Keyboard/Keyboard.h"


#include <Api/ApiLinkLib/ApiLink.h>

#include "main.h"


//class MainScreen;
int my_application = 0;
static int setup_h;
std::string elfdir;


ResourceManager *_global_res_manager;
ExtManager *ext_manager;
EventManager event_mngr;
Widget active_area(Rect(0, 0, 240, 400), &event_mngr);
EffectManager global_emanager(&active_area);
FSProtocolsContainer protocols;

//GlobalMenuButton *menu_test = 0;
FileViewWidget *main_view = 0;
Keyboard *kbd;

unsigned int last_time, fps, fps_count;
bool _inited = false;
/*===================================================================*/
/*============================ GUI ==================================*/
/*===================================================================*/
#define WINDOW_ID_SCREEN 0x5001

static inline unsigned int cur_sec() {
    return *((volatile unsigned int *)( 0xF470001C ));
}


ResourceManager & resourceManager() {
    return *_global_res_manager;
}


EventManager & eventManager() {
    return event_mngr;
}


ExtManager & extensionManager() {
    return *ext_manager;
}

Widget & mainWidget() {
    return active_area;
}

FSProtocolsContainer & protocolsContainer() {
    return protocols;
}


Keyboard *mainKeyboard() {
    return kbd;
}

void Screen_OnDraw()
{
    if(!_inited)
        return;

    active_area.paint();

    ++fps_count;
    if(last_time != cur_sec())
    {
        fps = fps_count;
        fps_count = 0;
        last_time = cur_sec();
    }

    char f[28];
    sprintf(f, "fps: %d", fps);
    glSetPen(0xAFFF0000);
    glDrawString(f, 0, 0, 240, 30, 13, FT_TEXT_W_RIGHT | FT_TEXT_H_CENTER, 0, 128);


    event_mngr.update();
}


void refresh()
{
    Screen_OnDraw();
    GrSys_Refresh();
}





//Действие при создании окна
void Screen_OnInit()
{
    GLContext *gl_context = glCreateContext(DISPLAY_WITDH, DISPLAY_HEIGHT, 16, GetScreenBuffer());
    glActivateContext(gl_context);
    glEnable(GL_ALPHA_TEST);

    active_area.activateLongPress(true);

    protocols.pushProtocol("local", new LocalFSProtocol);


    event_mngr.setRefreshFunc( [](void *) {
        GrSys_Refresh();
    });

    event_mngr.setPaintFunc( [](void *) {
        Screen_OnDraw();
    });

    main_view = new FileViewWidget(&active_area, &global_emanager, Rect(0, 0, 240, 400));

    main_view->onExitSignal().connect( std::function<void(FileViewWidget*)>([](FileViewWidget *) {
        TaskMngr_AppExit(0, 0, 0);
    }) );

    active_area.add(main_view);

    main_view->cdEffectPrepare(false);
    main_view->cdUp("/", false);

    _inited = true;
    main_view->cdEffectStart(EFFECT_CENTER_SCALE);

    kbd = new Keyboard(Rect(0, 250, 240, 150), &active_area);

}



//Действие при уничтожении окна
void Screen_OnExit()
{
    delete kbd;
    delete main_view;
    delete _global_res_manager;
    delete ext_manager;

    glDestroyContext( glActiveContext() );
}



//Действие при активации
void Screen_OnAwake()
{
    GrSys_SelectGDI(0);
    refresh();
}

//Действие при сворачивании
void Screen_OnSleep()
{

}

//Действие при зажатии настоящией кнопки или рабочей области тачскрина
void Screen_OnKeyDown(int key)
{
    switch (key)
    {
    case KEY_CAMERA:
    {
        image_t img;

        img.bitmap = Graphics_GetScreenBuffer();
        img.w = 240;
        img.h = 400;
        img.bit = 16;

        save_png_to_file (&img, "/usr/Zbin/shoot.png");
        break;
    }

    case KEY_SEND:
        main_view->switchNextWorkSpace();
        break;

    case KEY_MULTI:
        TaskMngr_Show();
        break;

    case KEY_END:
        TaskMngr_AppExit(0, 0, 0);
        break;
    }

    refresh();
}


//Действие при отпускании настоящией кнопки
void Screen_OnKeyUp(int key)
{
    GL_UNUSED(key)
}


//Действие при отрисовке статус-бара
void Screen_OnIndicatorDraw()
{
    //refresh();
}


//Действие при срабатывании таймеров
extern "C" void __timer_notifier(int timer_id);
void Screen_OnTimer(int timer_id, int param)
{
    GL_UNUSED(param)

    __timer_notifier(timer_id);

    if(timer_id == 0) {

        /*for(int i=0; i<19; ++i) {
            main_view->switchViewType();
            refresh();
        }*/
    }

    event_mngr.update();
}

//Действие при манипуляциях с тачскрином
void Screen_OnPointing(int action, int position)
{
    static int last_action;
    int x, y;

    x = PXE_LOWORD(position);
    y = PXE_HIWORD(position);

    if(action == TOUCH_ACTION_MOVE && last_action != 1) {
        last_action = 1;
        //setup_h = SetUP_GetHandle();
        NU_Sleep(2);
        SetUP_SetTouchpadSensitivity(setup_h, TOUCHPAD_SENSITIVITY_SET, 1);
    } else if(action != TOUCH_ACTION_MOVE && last_action != 2) {
        last_action = 2;
        //setup_h = SetUP_GetHandle();
        SetUP_SetTouchpadSensitivity(setup_h, TOUCHPAD_SENSITIVITY_SET, 9);
    }

    active_area.touch(action, x, y);
    event_mngr.update();
}


//Главный обработчик окна WINDOW_ID_MAINMENU от приложения
int Window_EventHandler(int cmd, int subcmd, int status)
{
    switch (cmd)
    {
    case Window_OnInit:
        Screen_OnInit();
        break;
    case Window_OnExit:
        Screen_OnExit();
        break;
    case Window_OnAwake:
        printf("Window_OnAwake: %d\n", cmd);
        Screen_OnAwake();
        break;
    case Window_OnSleep:
        Screen_OnSleep();
        break;
    case Window_OnKeyDown:
        Screen_OnKeyDown(subcmd);
        break;
    case Window_OnKeyUp:
        Screen_OnKeyUp(subcmd);
        break;
    case Window_OnDraw:
        refresh();
        break;
    case Window_OnTimer:
        Screen_OnTimer(subcmd, status);
        break;
    case Window_OnPointing:
        Screen_OnPointing(subcmd, status);
        break;
    case Window_OnIndicatorDraw:
        Screen_OnIndicatorDraw();
        break;
    default:
        printf("Ololo event: %d\n", cmd);
        break;
    }

    return 1;
}



int listener(int event_id, int wparam, int lparam)
{
    switch (event_id)
    {
    case PXE_RUN_CREATE_EVENT:
        TaskMngr_AppSetName(my_application, 0, 0, 0);

        //Получаем хендл настроек
        setup_h = SetUP_GetHandle();

        //Устанавливаем чувствительность тачпада
        SetUP_SetTouchpadSensitivity(setup_h, TOUCHPAD_SENSITIVITY_SET, 9);

        Window_Create(WINDOW_ID_SCREEN, Window_EventHandler);
        Window_Init(WINDOW_ID_SCREEN);
        return 1;

    case PXE_RUN_DESTROY_EVENT:
        // Уничтожаем окно
        SetUP_CloseHandle(setup_h);
        Window_DestroyAll();
        ElfDestroy();
        return 1;

        //Событие при активации приложения
    case PXE_RUN_RESUME_EVENT:
        //refresh_all = 1;
        Window_TransEvent(PXE_RUN_PAINT_EVENT, 0, 0);
        return 1;

    case PXE_RUN_SUSPEND_EVENT:
        //SetUP_SetTouchpadSensitivity(setup_h, TOUCHPAD_SENSITIVITY_DEFAULT, 0);
        return 1;

    case 102: // on awake
        //SetUP_SetTouchpadSensitivity(setup_h, TOUCHPAD_SENSITIVITY_SET, 9);
        Screen_OnAwake();
        Window_TransEvent(event_id, wparam, lparam);
        return 1;

    case 101: // on suspend
        Screen_OnSleep();
        Window_TransEvent(event_id, wparam, lparam);
        return 1;

    default:

        //printf("event_id: %d\n", event_id);
        Window_TransEvent(event_id, wparam, lparam);
        return 1;
    }
}


int main(int argc, char *argv[])
{
    GL_UNUSED(argc)
    char *end = strrchr(argv[0], '/');
    if(end) {
        ++end;
        elfdir.assign(argv[0], 0, end-argv[0]);
    }

    _global_res_manager = new ResourceManager(elfdir);
    ext_manager = new ExtManager(elfdir);

    static ELF_PARASITE_INFO parasite;
    my_application = RegisterApplicationEventListener(&parasite, listener, L"MyMegaApplication");
    return /*(float)argc / 2.2f*/0;
}



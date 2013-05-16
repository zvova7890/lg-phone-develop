
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
static int gdi_state = 0;
//static int name = 0;

ExtManager *ext_manager;
std::string elfdir;


void rebase_for_current_gdi();
void switch_gdi(int id);


class MainWidget : public Widget
{
public:

    MainWidget(const Rect & rect, EventManager *event_manager) :
        Widget(rect, event_manager)
    {}

    ~MainWidget() {
        delete m_kbd;
        delete m_effectManager;
        delete m_resourceManager;
    }

    void init()
    {
        m_resourceManager = new ResourceManager( elfdir );
        m_kbd = new Keyboard(Rect(0, GRSYS_HEIGHT-140, GRSYS_WIDTH, 140), this);
        m_kbd->handleResizeEvent().connect( [](Widget *w) {
           w->setSize(Rect(0, GRSYS_HEIGHT-140, GRSYS_WIDTH, 140));
        });


        m_effectManager = new EffectManager( this );

        provideExtraWidget("keyboard", m_kbd);
    }

    Widget *providesExtraWidget(const std::string &s) {
        return m_extra_widgets[s];
    }

    void provideExtraWidget(const std::string &s, Widget *w) {
        m_extra_widgets[s] = w;
    }

    ResourceManager *resourceManager() {
        return m_resourceManager;
    }

    EffectManager *effectManager() {
        return m_effectManager;
    }


    void resizeEvent() {

        printf("Width: %d\n", GRSYS_WIDTH);


        //glSetContextProp(glActiveContext(), GRSYS_WIDTH, GRSYS_HEIGHT, 16, Graphics_GetScreenBuffer());
        /*glDestroyContext(glActiveContext());

        glActivateContext( glCreateContext(GRSYS_WIDTH, GRSYS_HEIGHT, 16, Graphics_GetScreenBuffer()) );
        glEnable(GL_ALPHA_TEST);*/

        setSize(Rect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT));

        m_effectManager->resizeEvent();
        Widget::resizeEvent();
    }

protected:
    std::map <std::string, Widget *> m_extra_widgets;
    ResourceManager *m_resourceManager;
    Keyboard *m_kbd;
    EffectManager *m_effectManager;
};



EventManager event_mngr;
MainWidget *main_widget = 0;
FSProtocolsContainer protocols;

//GlobalMenuButton *menu_test = 0;
FileViewWidget *main_view = 0;


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
    return *main_widget->resourceManager();
}


EventManager & eventManager() {
    return event_mngr;
}


ExtManager & extensionManager() {
    return *ext_manager;
}


FSProtocolsContainer & protocolsContainer() {
    return protocols;
}



void Screen_OnDraw()
{
    if(!_inited)
        return;

    main_widget->paint();

    /*++fps_count;
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
*/

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
    GLContext *gl_context = glCreateContext(GRSYS_WIDTH, GRSYS_HEIGHT, 16, GetScreenBuffer());
    glActivateContext(gl_context);
    glEnable(GL_ALPHA_TEST);


    protocols.pushProtocol("local", new LocalFSProtocol);

    event_mngr.setPaintFunc( [](void *){
        Screen_OnDraw();
    } );

    event_mngr.setRefreshFunc( [](void *){
        GrSys_Refresh();
    } );

    main_widget = new MainWidget(Rect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT-0), &event_mngr);
    main_widget->init();
    main_widget->activateLongPressSupport(true);


    main_view = new FileViewWidget(main_widget, main_widget->effectManager(), main_widget->rect());
    main_view->onExitSignal().connect( std::function<void(FileViewWidget*)>([](FileViewWidget *) {
        TaskMngr_AppExit(0, 0, 0);
    }) );

    main_view->handleResizeEvent().connect([](Widget *w) {
        w->setSize(w->parent()->rect());
        w->eventManager()->updateAfterEvent();
    });

    main_widget->add(main_view);

    main_view->cdEffectPrepare(false);
    main_view->cdUp("/", false);

    _inited = true;
    main_view->cdEffectStart(EFFECT_CENTER_SCALE);
}



//Действие при уничтожении окна
void Screen_OnExit()
{
    Graphics_ChangeGDI(0);

    delete main_view;
    delete ext_manager;
    delete main_widget;

    glDestroyContext( glActiveContext() );
}



//Действие при активации
void Screen_OnAwake()
{
    switch_gdi(gdi_state);
    refresh();
}

//Действие при сворачивании
void Screen_OnSleep()
{
    gdi_state = GrSys_GetGDIID();
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
            img.w = GRSYS_WIDTH;
            img.h = GRSYS_HEIGHT;
            img.bit = 16;

            save_png_to_file (&img, "/usr/Zbin/shoot.png");
            break;
        }

        case KEY_SEND:
            //TaskMngr_AppSetName(my_application, 0, ++name, 0); //5
            main_view->switchNextWorkSpace();
            break;

        case KEY_MULTI:
            TaskMngr_Show();
            break;

        case KEY_END:
            TaskMngr_AppExit(0, 0, 0);
            break;
    }

    //refresh();
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

    //printf("x %d - y %d\n", x, y);


    if( GrSys_GetGDIID() == 1) {
        /* retranslate coordinates */
        int t = x;

        x = y;
        y = 240-t;
    }

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

    main_widget->touch(action, x, y);
    event_mngr.update();
}


void lg_general_axel_event(int position)
{
    printf("position: %d\n", position);

    if(position == 2 && GrSys_GetGDIID() == 1) {
        switch_gdi(0);
    }
    else if(position == 1 && GrSys_GetGDIID() != 1) {
        switch_gdi(1);
    }

    main_widget->motionSensorEvent(position);
    event_mngr.update();
}


void lg_axel_event(int x, int y, int z)
{
    main_widget->motionSensorEvent(x, y, z);
    //event_mngr.update();
}



void rebase_for_current_gdi()
{
    glSetContextProp(glActiveContext(), GRSYS_WIDTH, GRSYS_HEIGHT, 16, Graphics_GetScreenBuffer());
}


void switch_gdi(int id)
{
    //if(id == GrSys_GetGDIID())
      //  return;

    GrSys_SelectGDI(id);
    rebase_for_current_gdi();

    main_widget->resizeEvent();
}


//Главный обработчик окна WINDOW_ID_MAINMENU от приложения
int Window_EventHandler(unsigned long cmd, unsigned long subcmd, unsigned long status)
{
    //printf("cmd: %d\n", cmd);
    switch (cmd)
    {
        case MSG_INIT:
            Screen_OnInit();
            break;

        case MSG_EXIT:
            Screen_OnExit();
            break;

        case MSG_RESUME:
            Screen_OnAwake();
            break;

        case MSG_SLEEP:
                printf("Sleep\n");
            Screen_OnSleep();
            break;

        case MSG_KEYDOWN:
            Screen_OnKeyDown(subcmd);
            break;

        case MSG_KEYUP:
            Screen_OnKeyUp(subcmd);
            break;

        case MSG_DRAW:
            refresh();
            break;

        case MSG_TIMER:
            Screen_OnTimer(subcmd, status);
            break;

        case MSG_POINTING:
            Screen_OnPointing(subcmd, status);
            break;

        case MSG_INDICATOR:
            Screen_OnIndicatorDraw();
            break;

        default:
            //printf("Ololo event: %d\n", cmd);
            break;
    }

    return 1;
}



int listener(unsigned long event_id, unsigned long wparam, unsigned long lparam)
{
    //printf("event_id: %d\n", event_id);

    switch (event_id)
    {
        case BNS_EVENT_START:
        {
            TaskMngr_AppSetName(my_application, 0, 5, 0);

            //Получаем хендл настроек
            setup_h = SetUP_GetHandle();

            //Устанавливаем чувствительность тачпада
            SetUP_SetTouchpadSensitivity(setup_h, TOUCHPAD_SENSITIVITY_SET, 9);

            MsgHandler_RegisterProcessor(WINDOW_ID_SCREEN, Window_EventHandler);
            MsgHandler_SetActivePID(WINDOW_ID_SCREEN);

            AccelSensor_Enable();
            AccelSensor_EventsEnable(1);

            return 1;
        }

        case BNS_EVENT_TERMINATE:
            // Уничтожаем окно
            SetUP_CloseHandle(setup_h);

            MsgHandler_Terminate();
            ElfDestroy();
            return 1;

            //Событие при активации приложения
        case BNS_EVENT_RESUME:
            MsgHandler_SendMessage(WINDOW_ID_SCREEN, MSG_RESUME, 0, 0);
            return 1;

        case BNS_EVENT_SUSPEND:
            MsgHandler_SendMessage(WINDOW_ID_SCREEN, MSG_SLEEP, 0, 0);
            return 1;

        case BNS_EVENT_MOTION_SENSOR:
            lg_general_axel_event(lparam);
            return 1;

        default:
            //printf("event_id: %d\n", event_id);
            Window_TransEvent(event_id, wparam, lparam);
            return 1;
    }
}



void init_fds();
int main(int argc, char *argv[])
{
    GL_UNUSED(argc)
    char *end = strrchr(argv[0], '/');
    if(end) {
        ++end;
        elfdir.assign(argv[0], 0, end-argv[0]);
    }

    init_fds();
    ext_manager = new ExtManager(elfdir);

    static ELF_PARASITE_INFO parasite;
    my_application = RegisterApplicationEventListener(&parasite, listener, L"MyMegaApplication");
    return 0;
}



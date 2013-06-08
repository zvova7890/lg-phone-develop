
#ifndef __PC_BUILD__
#define COMPILE_FOR_REPLACE
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <fs.h>
#include <loader.h>
#include <mem.h>
#include <pxeapi_graphics.h>
#include <pxeapi.h>
#include <taskapi.h>
#include <wchar.h>
#include <nucleus.h>
#include <gl.h>
#include <lgos_timers.h>

#include <Api/ApiLinkLib/ApiLink.h>

#ifdef COMPILE_FOR_REPLACE
#include <prochandler.h>
#endif

#include <Core/ResourceManager.h>
#include <Widget/Button.h>
#include "main.h"
#include "EffectManager.h"

#include "Contacts.h"
#include "PhoneSettings.h"
#include "DisplaySettings.h"
#include "Applications.h"
#include "cmd.h"


#ifdef COMPILE_FOR_REPLACE
ProcHandlerStruct *proc_hook = 0;
#endif

H_PROCESS my_application = 0;
/*===================================================================*/
/*============================ GUI ==================================*/
/*===================================================================*/
#define WINDOW_ID_SCREEN 10

char msg_pool[512];
#define msg(m, ...) { sprintf(msg_pool, m, ##__VA_ARGS__); Screen_OnDraw(); }

std::string elfdir = "./";
ResourceManager *res_manager = 0;
EventManager *event_manager;
MyWindow *window = 0;
EffectManager *effects = 0;
RootWindow *root_window;
int setup_h = 0;
int exit_is_now = 0;


void render_test();


void app_exit()
{
#ifdef COMPILE_FOR_REPLACE

    H_PROCESS idle = ProcMngr_SearchApp(L"PhoneIdle.pxo");

    FxUi_SwitchToProc(idle, 8);

    H_SHAREDMEM hmem = ShMem_GetHandle(L"TaskApi");
    void ** mem = (void**)ShMem_GetMem(hmem);
    ((void(*)(int, int, int))mem[2])(0, 0, 3);
#else
    exit_is_now = 1;
    TaskMngr_AppExit(0, 0, 0);
#endif
}





RootWindow::RootWindow(const Rect &r, EventManager *p) :
    Widget(r, p)
{}


void *RootWindow::providesExtraExtension(const std::string &s) {
    if(s == "resource")
        return res_manager;

    return 0;
}



MyWindow::MyWindow(const Rect &r, Widget *p) :
    Widget(r, p),
    bar(Rect(realRect().x2()-36, 75, 36, 308), this),
    exit(Rect(realRect().x2()-41, 29, 39, 34), this, "<-")
{
    background = &res_manager->image("background");

    m_tabs.push_back(new Tab(Rect(0, 65, rect().w()-36, rect().h()-60), this));
    m_tabs.push_back(new Tab(Rect(0, 65, rect().w()-36, rect().h()-60), this));
    m_tabs.push_back(new Tab(Rect(0, 65, rect().w()-36, rect().h()-60), this));
    m_tabs.push_back(new Tab(Rect(0, 65, rect().w()-36, rect().h()-60), this));

    /* =======================================*/

    m_tabs.at(0)->setName("Связь");
    m_tabs.at(0)->addButton(&res_manager->image("dial"), "Набор номера", [](Tab *, Button *) {
        H_PROCESS h = App_RunEx(L"LGAPP/Pxo/PhoneIdle.pxo", 0, FOREGROUND_PRIORITY, TRUE);
        EvHandler_PostEvent(h, 328000, 4, 32008);
    });

    m_tabs.at(0)->addButton(&res_manager->image("speeddial"), "Быстрый набор", [](Tab *, Button *) {
        CMD_Exec(0x22D00000);
    });

    m_tabs.at(0)->addButton(&res_manager->image("contacts"), "Контакты", [this](Tab *, Button *) {
        showContacts(this);
    });

    m_tabs.at(0)->addButton(&res_manager->image("calls"), "История звонков", [this](Tab *, Button *) {
        CMD_Exec(0x2C500000);
    });

    m_tabs.at(0)->addButton(&res_manager->image("newmessage"), "Новое сообщение", [this](Tab *, Button *) {
        CMD_Exec(0x27400000);
    });


    m_tabs.at(0)->addButton(&res_manager->image("newmail"), "Новый e-mail", [this](Tab *, Button *) {
        CMD_NewMail();
    });

    m_tabs.at(0)->addButton(&res_manager->image("messages"), "Сообщения", [this](Tab *, Button *) {
        CMD_MyMusic();
    });



    /* =======================================*/
    m_tabs.at(1)->setName("Развлечения");
    m_tabs.at(1)->addButton(&res_manager->image("gallery"), "Галерея", [this](Tab *, Button *) {
        CMD_Pxo(L"Gallery.pxo");
    });

    m_tabs.at(1)->addButton(&res_manager->image("myfolders"), "Мои папки", [this](Tab *, Button *) {
        execelf("/usr/zbin/apps/nfm/nfm.elf", 0, 0, 0, 0);
    });

    m_tabs.at(1)->addButton(&res_manager->image("camera"), "Камера", [this](Tab *, Button *) {
        T_CMD_INFO *tcinfo = T_CMD_ALLOC(0x1C);
        if(tcinfo) {
            T_CMD_MEMSET(tcinfo, 0, 0x1C);

            tcinfo->Msg = 1;
            H_PROCESS p = CMD_Pxo(L"Camera.pxo");
            EvHandler_PostEvent(p, 100200, 0, (int)tcinfo);
        }
    });

    m_tabs.at(1)->addButton(&res_manager->image("videocamera"), "Видео камера", [this](Tab *, Button *) {
        T_CMD_INFO *tcinfo = T_CMD_ALLOC(0x1C);
        if(tcinfo) {
            T_CMD_MEMSET(tcinfo, 0, 0x1C);

            tcinfo->Msg = 1;
            H_PROCESS p = CMD_Pxo(L"Camcorder.pxo");
            EvHandler_PostEvent(p, 100200, 0, (int)tcinfo);
        }
    });

    m_tabs.at(1)->addButton(&res_manager->image("muveestudio"), "Muvee studio", [this](Tab *, Button *) {
        CMD_Pxo(L"CamMuvee.pxo");
    });

    m_tabs.at(1)->addButton(&res_manager->image("music"), "Музыка", [this](Tab *, Button *) {
        CMD_MyMusic();
    });

    m_tabs.at(1)->addButton(&res_manager->image("radio"), "Радио", [this](Tab *, Button *) {
        CMD_Pxo(L"FMRadio.pxo");
    });

    m_tabs.at(1)->addButton(&res_manager->image("apps"), "Игры/Прилож", [this](Tab *, Button *) {
        showApplications(this);
    });



    /* =======================================*/
    m_tabs.at(2)->setName("Инструменты");
    m_tabs.at(2)->addButton(&res_manager->image("browser"), "Браузер");
    m_tabs.at(2)->addButton(&res_manager->image("organizer"), "Органайзер");
    m_tabs.at(2)->addButton(&res_manager->image("alarm"), "Будильник", [this](Tab *, Button *) {
        CMD_Pxo(L"AlarmClock.pxo");
    });

    m_tabs.at(2)->addButton(&res_manager->image("dictaphone"), "Диктофон", [this](Tab *, Button *) {
        CMD_VoiceRecorder();
    });

    m_tabs.at(2)->addButton(&res_manager->image("paint"), "Панель рис.", [this](Tab *, Button *) {
        CMD_Pxo(L"DrawingPanel.pxo");
    });

    m_tabs.at(2)->addButton(&res_manager->image("tools"), "Инструменты");
    m_tabs.at(2)->addButton(&res_manager->image("simmenu"), "Сим меню");



    /* =======================================*/
    m_tabs.at(3)->setName("Настройки");
    m_tabs.at(3)->addButton(&res_manager->image("profiles"), "Профили", [this](Tab *, Button *) {
        CMD_Pxo(L"Profiles.pxo");
    });

    m_tabs.at(3)->addButton(&res_manager->image("displaysettings"), "Настр. экрана", [this](Tab *, Button *) {
        showDisplaySettings(this);
    });

    m_tabs.at(3)->addButton(&res_manager->image("phonesettings"), "Настр. телефона", [this](Tab *, Button *) {
        showPhoneSettings(this);
    });

    m_tabs.at(3)->addButton(&res_manager->image("callsettings"), "Настр. вызова");
    m_tabs.at(3)->addButton(&res_manager->image("sensorsettings"), "Настр. сенсора");
    m_tabs.at(3)->addButton(&res_manager->image("bluetooth"), "Bluetooth", [this](Tab *, Button *) {
        CMD_Pxo(L"Bluetooth.pxo");
    });

    m_tabs.at(3)->addButton(&res_manager->image("connectionsettings"), "Соеденение");


    bar.changeBarAction().connect([this](Bar*, int tab) {
        if(tab < 5) {

            if((unsigned)tab < m_tabs.size()) {
                curentTab->close();
                curentTab = m_tabs.at(tab);
                curentTab->show();
            }
        }
    });

    bar.show();


    curentTab = m_tabs.at(0);
    curentTab->show();


    exit.releasedSignal().connect([](Button *b) {
        if(b->isTouched())
            app_exit();
    });

    exit.show();
}


MyWindow::~MyWindow()
{
    for(Tab *t : m_tabs)
        delete t;
}



void MyWindow::paintEvent()
{
    //glClear(0xFF000000);

    if(!background->isEmpty())
        drawImage(0, 0, background);
    else
        glClear(0xFF000000);

    glSetPen(0xFFFFFFFF);
    glDrawString(curentTab->name().c_str(), realRect().x() + 10, realRect().y()+30,  realRect().x()+10+(realRect().w()-20),
                 realRect().y()+30+20, 18, FT_TEXT_H_CENTER, 0, 128);




    Widget::paintEvent();
}



void MyWindow::touchEvent(int action, int x, int y)
{
    Widget::touchEvent(action, x, y);
    eventManager()->updateAfterEvent();
}




void Screen_OnDraw()
{
    render_test();
    return;

    root_window->paint();

    Indicator_Draw(0);
    event_manager->update();
}



//Действие при создании окна
void Screen_OnInit()
{
    static bool inited = false;

    auto effect = []() {
        effects->pushPrevScreen(Image::grabScreen());
        event_manager->paint();
        effects->pushNextScreen( Image::grabScreen() );

        //effects->start( "conveyor", EffectManager::EFFECT_ALPHA_OUT, 2, 10, 1 );
    };


    GrSys_SelectGDI(0);
    Indicator_SetShowStyle( INDICATORSTY_SHOW );

    if(inited) {
        effect();
        return;
    }

    inited = true;

    glActivateContext( glCreateContext(GRSYS_WIDTH, GRSYS_HEIGHT, 16, GrSys_GetGrBuf()) );
    glEnable( GL_ALPHA_TEST );


    event_manager = new EventManager();

    event_manager->setPaintFunc( [](void *) {
        Screen_OnDraw();
    });

    event_manager->setRefreshFunc( [](void *) {
        GrSys_Refresh();
    });


    res_manager = new ResourceManager(elfdir);
    res_manager->setImagesDir( elfdir + "icons/" );


    root_window = new RootWindow(Rect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT), event_manager);
    root_window->__name = "root_window";

    window = new MyWindow(Rect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT), root_window);
    window->__name = "window";

    effects = new EffectManager(root_window);
    effects->__name = "effects";

    window->show();

    effect();

    // Hack!
    Timer::oneShoot(event_manager, 80, []() {
        event_manager->updateAfterEvent();
    });
}


//Действие при уничтожении окна
void Screen_OnExit()
{
#ifndef COMPILE_FOR_REPLACE
    if(exit_is_now) {


        delete effects;
        delete window;
        delete root_window;
        delete res_manager;
        delete event_manager;

        glDestroyContext( glActiveContext() );
    }
#endif

    printf("Screen_OnExit()!!!\n");
}



//Действие при активации
void Screen_OnAwake()
{
    GrSys_SelectGDI(0);
    Indicator_SetShowStyle( INDICATORSTY_SHOW );

    Screen_OnDraw();
    GrSys_Refresh();
}

//Действие при сворачивании
void Screen_OnSleep()
{

}


H_PROCESS handler = 0;
static LGOS_TIMER tmr;
bool active_tmr = false;
//Действие при зажатии настоящией кнопки или рабочей области тачскрина
void Screen_OnKeyDown(int key)
{
    switch (key)
    {
        case KEY_CAMERA:
        {
/*
 * 0  - Меню
 * 1  - Оборзеватель
 * 2  - Настройки экрана
 * 3  - Настройки телефона
 * 4  - Настройка вызова
 * 5  - Соединение
 * 6  - Сообщения
 * 7  -
 * 8  - Игры/Приложения
 * 9  - Сообщения
 * 10 - Органайзер
*/


/*
 *   MsgHandler_InsertActivePID
 *
 * 1 - Дефолтный вид
 * 2 -
 * 3 - Вызовы
 * 4 -
*/

/*
 *   MsgHandler_SetActivePID
 *
 * 1 -
 * 2 - дефолт
 * 3 - вызовы
 * 4 -
*/
            if(active_tmr)
                LGOS_Timer_Delete(&tmr);
            active_tmr = false;

            static int lol = 4;

            //handler = App_RunEx(L"LGAPP/Pxo/MainMenu.pxo", 0, FOREGROUND_PRIORITY, TRUE);
            //EvHandler_PostEvent(handler, 101200, lol++, 0);

            MsgHandler_SetActivePID(lol++);


            LGOS_Timer_Create(&tmr, "LOOOL");

            LGOS_Timer_SetLoop(&tmr, 0);
            LGOS_Timer_SetPeriod(&tmr, 5000, 5000);
            LGOS_Timer_SetProc(&tmr, [](void *d) {
                printf("EXIT APP NA!!\n");
                //App_Resume(my_application, 0);
                MsgHandler_SetActivePID(WINDOW_ID_SCREEN);
                LGOS_Timer_Delete((LGOS_TIMER*)d);
                active_tmr = false;
            }, &tmr);

            LGOS_Timer_Start(&tmr);
            active_tmr = true;

            /*image_t img;

            img.bitmap = Graphics_GetScreenBuffer();
            img.w = 240;
            img.h = 400;
            img.bit = 16;

            save_png_to_file (&img, "/usr/Zbin/shoot.png");*/
            break;
        }

        case KEY_MULTI:
#ifndef COMPILE_FOR_REPLACE
            App_RunEx(L"LGAPP/Pxo/TaskList.pxo", 0, FOREGROUND_PRIORITY, TRUE);
#else
            MsgHandler_SetActivePID(2);
            proc_hook->old_listener(BNS_EVENT_KEYDOWN, key, 0);
#endif
            break;

        case KEY_END:
        {
#ifndef COMPILE_FOR_REPLACE
            TaskMngr_AppExit(0, 0, 0);
#else
            //App_Exit(my_application, 0);

            app_exit();
#endif
            break;
        }

        case BNS_VOLUP_K:
            event_manager->updateAfterEvent();
            break;

        case BNS_VOLDOWN_K:
            break;

    }

    event_manager->update();
}


//Действие при отпускании настоящией кнопки
void Screen_OnKeyUp(int key)
{
    (void) key;
    event_manager->update();
}


//Действие при отрисовке статус-бара
void Screen_OnIndicatorDraw()
{
    Indicator_Draw(1);
    event_manager->update();
}


//Действие при срабатывании таймеров
extern "C" void __timer_notifier(int timer_id);
void Screen_OnTimer(int timer_id, int param)
{
    (void) timer_id;
    GL_UNUSED(param);

    __timer_notifier(timer_id);
    event_manager->update();
}


//Действие при манипуляциях с тачскрином
void Screen_OnPointing(int action, int position)
{
    static int last_action;
    int x, y;

    x = PXE_LOWORD(position);
    y = PXE_HIWORD(position);

    if( GrSys_GetGDIID() == 1) {
        /* retranslate coordinates */
        int t = x;

        x = y;
        y = 240-t;
    }

    if(action == TOUCH_ACTION_MOVE && last_action != 1) {
        last_action = 1;
        if(setup_h) SetUP_SetTouchpadSensitivity(setup_h, TOUCHPAD_SENSITIVITY_SET, 1);
    } else if(action != TOUCH_ACTION_MOVE && last_action != 2) {
        last_action = 2;
        if(setup_h) SetUP_SetTouchpadSensitivity(setup_h, TOUCHPAD_SENSITIVITY_SET, 9);
    }


    root_window->touch(action, x, y);
    event_manager->update();
}


int Window_EventHandler(unsigned long cmd, unsigned long subcmd, unsigned long status)
{
    switch (cmd)
    {
    case Window_OnInit:
        Screen_OnInit();
        break;
    case Window_OnExit:
        Screen_OnExit();
        break;

    case MSG_AWAKE: case MSG_RESUME:
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
        Screen_OnDraw();
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
        //printf("Ololo event: %d\n", cmd);
        break;
    }


    return 1;
}



#ifndef COMPILE_FOR_REPLACE
int listener(unsigned long event_id, unsigned long wparam, unsigned long lparam)
{
    switch (event_id)
    {
        case BNS_EVENT_START:

            TaskMngr_AppSetName((int)my_application, 0, 0, 0);

            MsgHandler_RegisterProcessor(WINDOW_ID_SCREEN, Window_EventHandler);
            MsgHandler_SetActivePID(WINDOW_ID_SCREEN);

            setup_h = SetUP_GetHandle();
            break;

        case BNS_EVENT_TERMINATE:
        {
            if(setup_h)
                SetUP_CloseHandle(setup_h);
            setup_h = 0;

            MsgHandler_Terminate();
            ElfDestroy();
            break;
        }

        case BNS_EVENT_RESUME:
            MsgHandler_SendMessage(WINDOW_ID_SCREEN, MSG_RESUME, 0, 0);
            break;

        default:


            //printf("Event: %lu, %lu, %lu\n", event_id, wparam, lparam);
            MsgHandler_Translate(event_id, wparam, lparam);
            break;
    }

    return 1;
}


#ifdef __PC_BUILD__
extern "C" int lgmain(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
    GL_UNUSED(argc);
    GL_UNUSED(argv);

    char *end = strrchr(argv[0], '/');
    if(end) {
        ++end;
        elfdir.assign(argv[0], 0, end-argv[0]);
    }


    //__clear_stdout();

    static ELF_PARASITE_INFO info;
    my_application = (H_PROCESS)RegisterApplicationEventListener(&info, listener, L"lol");
    return 0;
}



#else

int whoo = 0;
int listener(unsigned long event_id, unsigned long wparam, unsigned long lparam)
{
    switch (event_id)
    {
        case BNS_EVENT_START:
            MsgHandler_RegisterProcessor(WINDOW_ID_SCREEN, Window_EventHandler);
            proc_hook->old_listener(event_id, wparam, lparam);


            setup_h = SetUP_GetHandle();
            break;

        case BNS_EVENT_TERMINATE:
        {
            if(setup_h)
                SetUP_CloseHandle(setup_h);
            setup_h = 0;

            proc_hook->old_listener(event_id, wparam, lparam);


            if(exit_is_now)
                ElfDestroy();

            my_application = 0;
            break;
        }

        case BNS_EVENT_RESUME:
            MsgHandler_SendMessage(WINDOW_ID_SCREEN, MSG_RESUME, 0, 0);
            proc_hook->old_listener(event_id, wparam, lparam);
            break;

        case 101200:
            // wparam == 0 - менюха
            // wparam == 6 - сообщения
            whoo = wparam;

            if(wparam == 0)
                MsgHandler_SetActivePID(WINDOW_ID_SCREEN);
            else
                proc_hook->old_listener(event_id, wparam, lparam);

            //if(wparam == 0)
                //MsgHandler_InsertActivePID(WINDOW_ID_SCREEN);

            printf(" -> Event: %lu, %lu, %lu\n", event_id, wparam, lparam);
            break;

        case 7000:

            MsgHandler_InsertActivePID(2);
            break;

        default:


            //printf("Event: %lu, %lu, %lu\n", event_id, wparam, lparam);
            proc_hook->old_listener(event_id, wparam, lparam);
            break;
    }

    return 1;
}



void init_elf(void *api)
{
    proc_hook->old_init(api);

    printf("init: %X\n", (int)proc_hook->old_init);
    printf("list: %X\n", (int)proc_hook->old_listener);
}


void hook_erased(int id)
{
    if(root_window) {
        delete effects;
        delete window;
        delete root_window;
        delete res_manager;
        delete event_manager;

        root_window = 0;
        glDestroyContext( glActiveContext() );
    }


    if(my_application) {
        H_PROCESS idle = ProcMngr_SearchApp(L"PhoneIdle.pxo");

        FxUi_SwitchToProc(idle, 8);

        if(my_application)
            App_Exit(my_application, 0);
    }

    ElfDestroy();
    printf("Elf destroyed, because hook is replaced or removed\n");
}


void install_hook()
{
    int id = proc_handler_install_hook((unsigned short*)L"MainMenu.pxo", 1, init_elf, listener, hook_erased);
    if(id < 0) {
        ElfDestroy();
        printf("Can`t install hook\n");
        return;
    }


    proc_hook = proc_handler_hook(id);
    printf("Hook installed. Access granted %X\n", (int)proc_hook);
}



int main(int argc, char *argv[])
{
    GL_UNUSED(argc);
    GL_UNUSED(argv);

    char *end = strrchr(argv[0], '/');
    if(end) {
        ++end;
        elfdir.assign(argv[0], 0, end-argv[0]);
    }


    __clear_stdout();

    install_hook();
    return 0;
}

#endif

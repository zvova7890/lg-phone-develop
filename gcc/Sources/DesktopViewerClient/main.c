
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#include <Api/ApiLinkLib/ApiLink.h>

#include <nucleus.h>
#include <fs.h>
#include <loader.h>
#include <mem.h>
#include <pxeapi_graphics.h>
#include <pxeapi.h>
#include <taskapi.h>
#include <wchar.h>
#include <gl.h>



/*

        !!ВНИМАНИЕ!!

Как работает:

1. Запускаем EdgeD.elf
2. Запускаем EdgeD.jar, коннектимся, не закрываем, сворачиваем в фон. Пока жава работает, сессия будет открыта
3. EdgeD.elf перехватывает функцию Socket_Create и берёд оттуда ИД сессии
4. В пользовательском эльфе узнать ИД сессии можно из переменной окружения EDGE_SESSION(в хекс)


*/






int my_application = 0;
int setup_h = 0;
/*===================================================================*/
/*============================ GUI ==================================*/
/*===================================================================*/

#define WINDOW_ID_SCREEN 0x5001
#define IP_ADDR(A,B,C,D) (((unsigned long)D<<24)|((unsigned long)C<<16)|((unsigned long)B<<8)|((unsigned long)A<<0))


int socket_id = -1;
int session_id = -1;
int state = 0;
int received = 0;
int writed = 0;
FILE *fp = 0;


void Draw();


void Socket_OnConnected(int id)
{
    printf("Socket_OnConnected(%d)\n", id);
    state = 1;
    Draw();
}


void Socket_OnSend(int id)
{
    char ololo[512] =
            "GET /background.png HTTP/1.1\r\n"
            "Connection: close\r\n"
            "\r\n";

    Socket_Send(socket_id, ololo, strlen(ololo));

    state = 2;
    Draw();
}


void Socket_OnReceive(int id)
{
    static int header_received = 0;

    char data[4*1024+1];
    int sz = Socket_Receive(socket_id, data, 4*1024);
    data[sz>0? sz : 0] = 0;

    printf("Socket_OnReceive(%d) = %d\n", id, sz);

    // пропустим хидер
    if(fp && header_received && sz > 0) {
        int s = fwrite(data, 1, sz, fp);
        writed += s>0? s : 0;
    }

    if(!header_received)
        header_received = 1;
    else
        received += sz>0? sz : 0;


    state = 3;
    Draw();
}


void Socket_OnRemoteClosed(int id)
{
    state = 4;
    Draw();
}


void Draw()
{
    glSetPen(0xFFFFFFFF);
    glDrawFilledRectange(0, 40, 240, 400);

    char str[128];

    if(session_id > -1)
        sprintf(str, "%d, %d, %d", state, received, writed);
    else
        sprintf(str, "Session not found");

    glSetPen(0xFF000000);
    glDrawString(str, 0, 80, 240, 400, 20, FT_TEXT_SENTENCEBREAK, 0, 128);

    GrSys_Refresh();
}


int test()
{
    if(session_id < 0) {
        printf("Session not started\n");
        return 0;
    }

    fp = fopen("/usr/zbin/lol.jpg", "w+");

    TS_SOCKET_ADDRESS addr;
    memset(&addr, 0, sizeof(addr));

    addr.enFamily = 1;
    addr.ip.Ipv4Address.Address32 = IP_ADDR(46, 247, 247, 207);

    socket_id = Socket_Create(1, 1, session_id);
    Socket_Connect(socket_id, &addr, 8080);
    state = 0;

    return 0;
}


//Действие при создании окна
void Screen_OnInit()
{
    glActivateContext( glCreateContext(GRSYS_WIDTH, GRSYS_HEIGHT, 16, Graphics_GetScreenBuffer()) );
    glEnable(GL_ALPHA_TEST);

    char *id = getenv("EDGE_SESSION");

    if(id) {
        sscanf(id, "%X", &session_id);
    } else
        session_id = -1;
}


//Действие при уничтожении окна
void Screen_OnExit()
{
    if(fp) {
        fclose(fp);
        fp = 0;
    }

    Socket_Shutdown(socket_id, E_SOCKET_SHUTDOWN_FLAG_READnWRITE);
    Socket_Close(socket_id);

    glDestroyContext(glActiveContext());
}


//Действие при зажатии настоящией кнопки или рабочей области тачскрина
void Screen_OnKeyDown(int key)
{
    switch(key)
    {
    case KEY_END:
        TaskMngr_AppExit(0, 0, 0);
        break;

    case KEY_MULTI:
        TaskMngr_Show();
        break;

    case KEY_SEND:

        test();
        break;
    }

    Draw();
}


//Действие при отпускании настоящией кнопки
void Screen_OnKeyUp(int key)
{
}


//Действие при отрисовке окна
void Screen_OnDraw()
{
    Draw();
}


//Действие при отрисовке статус-бара
void Screen_OnIndicatorDraw()
{
    //Draw();
}



//Действие при срабатывании таймеров
void Screen_OnTimer(int timer_id, int param)
{

}


//Действие при манипуляциях с тачскрином
void Screen_OnPointing(int action, int position)
{
    static int last_action;
    int x, y;

    x = PXE_LOWORD(position);
    y = PXE_HIWORD(position);

}


//Действие при активации
void Screen_OnAwake()
{
}

//Действие при сворачивании
void Screen_OnSleep()
{
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
        break;
    }

    return 1;
}



int listener(int event_id, int wparam, int lparam)
{
    switch (event_id)
    {
    case BNS_EVENT_START:
        TaskMngr_AppSetName(my_application, 0, 0, 0);
        Window_Create(WINDOW_ID_SCREEN, Window_EventHandler);
        Window_Init(WINDOW_ID_SCREEN);

        //Получаем хендл настроек
        setup_h = SetUP_GetHandle();

        //Устанавливаем чувствительность тачпада
        SetUP_SetTouchpadSensitivity(setup_h, TOUCHPAD_SENSITIVITY_SET, 9);

        return 1;

    case BNS_EVENT_TERMINATE:
        SetUP_CloseHandle(setup_h);

        // Уничтожаем окно
        Window_DestroyAll();
        ElfDestroy();
        return 1;

        //Событие при активации приложения
    case BNS_EVENT_RESUME:
        Window_TransEvent(PXE_RUN_PAINT_EVENT, 0, 0);
        return 1;

    case BNS_EVENT_SUSPEND:
        return 1;

    case BNS_EVENT_SOCKET:
        switch(wparam)
        {
            case SWP_SOCKET_CONNECT_SUCCESS:
                Socket_OnConnected(lparam);
                return 1;

            case SWP_SOCKET_SEND_ENABLE:
                Socket_OnSend(lparam);
                return 1;

            case SWP_SOCKET_RECEIVE_ENABLE:
                Socket_OnReceive(lparam);
                return 1;

            case SWP_SOCKET_CLOSED_BY_NETWORK:
                Socket_OnRemoteClosed(lparam);
                return 1;

            default:
                printf("least socket: %d\n", wparam);

        }
        return 1;

    default:
        //printf("least wparam: %d\n", wparam);
        Window_TransEvent(event_id, wparam, lparam);
        return 1;
    }
}


int main(int argc, char *argv[])
{
    static ELF_PARASITE_INFO parasite;
    my_application = RegisterApplicationEventListener(&parasite, listener, L"MyMegaApplication");
    return 0;
}



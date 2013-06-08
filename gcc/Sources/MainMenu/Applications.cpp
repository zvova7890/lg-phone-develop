

#include <Api/ApiLinkLib/ApiLink.h>
#include <pxeapi.h>
#include <gl.h>
#include <loader.h>

#include <Widget/Widget.h>
#include <Core/ResourceManager.h>
#include <Widget/ListMenu.h>
#include <Widget/Button.h>
#include "EffectManager.h"
#include "MenuWidget.h"
#include "main.h"
#include "cmd.h"
#include "Applications.h"




extern ResourceManager *res_manager;
extern EventManager *event_manager;
extern RootWindow *root_window;
extern EffectManager *effects;


static std::list<Widget *> restoreWidget;



static void close_window()
{
    if(!restoreWidget.empty()) {
        Widget *w = restoreWidget.back();
        restoreWidget.erase( (--restoreWidget.end()) );

        effects->pushPrevScreen(Image::grabScreen());
        w->show();

        event_manager->paint();
        effects->pushNextScreen(Image::refScreen());
        effects->start("alpha", EffectManager::EFFECT_ALPHA_IN);
    }
}



/*
void showContactsInfo(Widget *last)
{
    restoreWidget.push_back(last);
    last->hide();


    effects->pushNextScreen(Image::grabScreen());
    MenuWidget *contacts = new MenuWidget(Rect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT), root_window);
    contacts->setFullScreenBlock(true);
    contacts->setName("Информация");

    contacts->addItem(0, "Номера сервиса", []() {
        CMD_Exec(0x22B00000);
    });

    contacts->addItem(0, "Собственные номера", []() {
        CMD_Exec(0x22A00000);
    });

    contacts->addItem(0, "Информация о памяти", []() {
        CMD_Exec(0x23000000);
    });

    contacts->addItem(0, "Моя визитная карточка", []() {
        CMD_Exec(0x22500000);
    });

    contacts->closingAction().connect([](MenuWidget *) {
        close_window();
    });

    contacts->show();

    event_manager->paint();
    effects->pushPrevScreen(Image::grabScreen());
    effects->start("alpha", 0);
}

*/



void showApplications(Widget *last)
{
    restoreWidget.push_back(last);
    last->hide();


    effects->pushNextScreen(Image::grabScreen());
    MenuWidget *contacts = new MenuWidget(Rect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT), root_window);
    contacts->setFullScreenBlock(true);
    contacts->setName("Игры/Прилож.");

    contacts->addItem(&res_manager->image("apps/GamesApps"), "Игры и приложения", []() {
        CMD_Exec(0x20000F0E - 2);
    });

    contacts->addItem(&res_manager->image("apps/elfs"), "Эльфы", []() {
        execelf("/usr/Zbin/core/apps.elf", 0, 0, 0, 0);
    });


    contacts->addItem(&res_manager->image("apps/pipegame"), "Трубопровод", []() {
        App_Run(L"/LGAPP/Pxo/PipeGame.pxo", 0);
    });

    contacts->addItem(&res_manager->image("apps/roulettegame"), "Чертово колесо", []() {
        App_Run(L"/LGAPP/Pxo/Game_Roulette.pxo", 0);
    });

    contacts->addItem(&res_manager->image("apps/dicegame"), "Кости в полёте", []() {
        App_Run(L"/LGAPP/Pxo/Game_dice.pxo", 0);
    });

    contacts->addItem(&res_manager->image("apps/settings"), "Настройки", []() {
        CMD_Exec(0x20000FCD);
    });


    contacts->closingAction().connect([](MenuWidget *) {
        close_window();
    });

    contacts->show();

    event_manager->paint();

    effects->pushPrevScreen(Image::refScreen());
    effects->start("alpha", 0);
}



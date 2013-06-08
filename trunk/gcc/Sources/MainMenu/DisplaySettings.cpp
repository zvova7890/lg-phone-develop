

#include <Api/ApiLinkLib/ApiLink.h>
#include <pxeapi.h>
#include <gl.h>


#include <Widget/Widget.h>
#include <Core/ResourceManager.h>
#include <Widget/ListMenu.h>
#include <Widget/Button.h>
#include "EffectManager.h"
#include "MenuWidget.h"
#include "main.h"
#include "cmd.h"
#include "DisplaySettings.h"




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



void showDisplaySettings(Widget *last)
{
    restoreWidget.push_back(last);
    last->hide();


    effects->pushNextScreen(Image::grabScreen());
    MenuWidget *contacts = new MenuWidget(Rect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT), root_window);
    contacts->setFullScreenBlock(true);
    contacts->setName("Настр. дисплея");

    contacts->addItem(&res_manager->image("displaysettings/wallpapers"), "Обои", []() {
        CMD_Exec(0x20000F7F);
    });

    contacts->addItem(&res_manager->image("displaysettings/menustyle"), "Главное меню", []() {
        CMD_Exec(0x20000F76);
    });

    contacts->addItem(&res_manager->image("displaysettings/dialstyle"), "Набор", []() {
        CMD_Exec(0x20000F77);
    });

    contacts->addItem(&res_manager->image("displaysettings/fonts"), "Шрифты", []() {
        CMD_Exec(0x20000F7A);
    });

    contacts->addItem(&res_manager->image("displaysettings/backlight"), "Подсветка", []() {
        CMD_Exec(0x20000F7F-1);
    });

    contacts->addItem(&res_manager->image("displaysettings/brightness"), "Яркость", [=]() {
        CMD_Exec(0x20000F7F-3);
    });

    contacts->addItem(&res_manager->image("displaysettings/hellomessage"), "Приветствие", [=]() {
        CMD_ResetSettings(0x20000F78);
    });

    contacts->addItem(&res_manager->image("displaysettings/turn"), "Включение", [=]() {
        CMD_Exec(0x20000F7B-6);
    });

    contacts->addItem(&res_manager->image("displaysettings/turn"), "Выключение", [=]() {
        CMD_Exec(0x20000F7B-7);
    });


    contacts->closingAction().connect([](MenuWidget *) {
        close_window();
    });

    contacts->show();

    event_manager->paint();

    effects->pushPrevScreen(Image::refScreen());
    effects->start("alpha", 0);
}





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
#include "PhoneSettings.h"




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



void showPhoneSettings(Widget *last)
{
    restoreWidget.push_back(last);
    last->hide();


    effects->pushNextScreen(Image::grabScreen());
    MenuWidget *contacts = new MenuWidget(Rect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT), root_window);
    contacts->setFullScreenBlock(true);
    contacts->setName("Настр. телефона");

    contacts->addItem(&res_manager->image("phonesettings/datetime"), "Дата и время", []() {
        CMD_Exec(0x100EF000);
    });

    contacts->addItem(&res_manager->image("phonesettings/powersave"), "Экономия энергии", []() {
        CMD_Exec(0x100E4000);
    });

    contacts->addItem(&res_manager->image("phonesettings/locale"), "Языки", []() {
        CMD_Exec(0x100EB000);
    });

    contacts->addItem(&res_manager->image("phonesettings/keylock"), "Автоблокировка", []() {
        CMD_Exec(0x100E6000);
    });

    contacts->addItem(&res_manager->image("phonesettings/security"), "Безопастность", []() {
        CMD_Exec(0x200E3000);
    });

    contacts->addItem(&res_manager->image("phonesettings/memorymanager"), "Менеджер памяти", [=]() {
        H_PROCESS h;
        if( (h = CMD_Exec(0x100EA000)) != 0 ) {
            EvHandler_PostEvent(h, 0x55794, 0, 0);
        }
    });

    contacts->addItem(&res_manager->image("phonesettings/reset"), "Сброс установок", [=]() {
        CMD_ResetSettings(0x100E8000);
    });

    contacts->addItem(&res_manager->image("contacts/info"), "Информация о телефоне", [=]() {
        CMD_Exec(0x100E9000);
    });


    contacts->closingAction().connect([](MenuWidget *) {
        close_window();
    });

    contacts->show();

    event_manager->paint();

    effects->pushPrevScreen(Image::refScreen());
    effects->start("alpha", 0);
}



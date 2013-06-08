
#include <Api/ApiLinkLib/ApiLink.h>
#include <pxeapi.h>
#include <gl.h>
#include "Contacts.h"


#include <Widget/Widget.h>
#include <Core/ResourceManager.h>
#include <Widget/ListMenu.h>
#include <Widget/Button.h>
#include "EffectManager.h"
#include "MenuWidget.h"
#include "main.h"
#include "cmd.h"


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





void showContacts(Widget *last)
{
    restoreWidget.push_back(last);
    last->hide();


    effects->pushNextScreen(Image::grabScreen());
    MenuWidget *contacts = new MenuWidget(Rect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT), root_window);
    contacts->setFullScreenBlock(true);
    contacts->setName("Контакты");

    contacts->addItem(&res_manager->image("contacts/add"), "Добавить контакт", []() {
        CMD_Exec(0x22F00000);
    });

    contacts->addItem(&res_manager->image("contacts/search"), "Поиск", []() {
        CMD_Exec(0x22E00000);
    });

    contacts->addItem(&res_manager->image("contacts/speeddial"), "Быстрый набор", []() {
        CMD_Exec(0x22D00000);
    });

    contacts->addItem(&res_manager->image("contacts/group"), "Группы", []() {
        CMD_Exec(0x22C00000);
    });

    contacts->addItem(&res_manager->image("contacts/setup"), "Настройки", []() {
        CMD_Exec(0x22900000);
    });

    contacts->addItem(&res_manager->image("contacts/info"), "Информация", [=]() {
        showContactsInfo(contacts);
    });


    contacts->closingAction().connect([](MenuWidget *) {
        close_window();
    });

    contacts->show();

    event_manager->paint();

    effects->pushPrevScreen(Image::refScreen());
    effects->start("alpha", 0);
}

# Предисловие #
QtCreator является мощной IDE написанной на С++Qt для использования в связке с библиотеками Qt. Но у ide есть возможность подстраивать среду под свои нужды. Чем мы и займёмся.


&lt;hr&gt;



# Установка Qt и QtCreator #
## Windows ##
[Скачиваем Qt4](http://qt-project.org/downloads) библиотеки(Не sdk полностью, там много ненужного) и QtCreator.<br />
Должно выглядеть примерно так(Выбирать версию с MinGW!): Qt libraries 4.8.4 for Windows (minGW 4.4, 317 MB)<br />

Минимальная версия QtCreator - 2.6.<br />
Примерно так: Qt Creator 2.7.1 for Windows (52 MB)

## Unix ##
Ставим все штатными средствами из репозиториев. Qt4 и QtCreator



&lt;hr&gt;


# Установка gcc #
[Читать](http://code.google.com/p/lg-phone-develop/wiki/CompillersSetup), если ещё не читали



&lt;hr&gt;


# Настройка конфигов #
Для начала нам нужно найти папку "mkspecs". На unix-like ОС она находится по пути "/usr/share/qt/mkspecs/" либо "/usr/local/share/qt/mkspecs/".
На ОС семейства Windows она находится в папке с установленым Qt.
Скачиваем под свою ос по [данной](http://code.google.com/p/lg-phone-develop/source/browse/#svn%2Fwiki%2FQtCreator) ссылке папки и распихиваеем их в папку с Qt.
Далее, нам нужно заменить пути расположения либ и хедеров:

Открываем ${ВАША ПАПКА С Qt}/mkspecs/unsupported/lg-gcc/qmake.conf:
```

INCLUDEPATH           = /home/vova7890/compilers/lg/include/
QMAKE_INCDIR          = /home/vova7890/compilers/lg/include/
INCLUDEPATH           += /home/vova7890/compilers/lg/include/native_api/
QMAKE_INCDIR          += /home/vova7890/compilers/lg/include/native_api/
QMAKE_LIBDIR          = /home/vova7890/compilers/lg/lib/
```

/home/vova7890/compilers/lg - заменяем на свой.

В windows версии можно не менять, если вы установили gcc в C:\lg-dev



&lt;hr&gt;


# Настройка компиляторов #
Настраиваем компилятор:
  * Инструменты -> Сборка и запуск
  * Вкладка "Компиляторы", жмём "добавить" -> выпадающий список, выбираем "gcc"
    1. Название: arm-eabi-gcc
    1. Путь к компилятору: /usr/arm-eabi/bin/g++(Указываем свой, куда устанавливали)
    1. ABI: особое | arm - unix - generic - elf - 32
Настраиваем инструментарий:
  * Инструменты -> Сборка и запуск
  * Вкладка "инструментарий", жмём "добавить"
    1. Название: arm-eabi-gcc
    1. Тип устройства: Desktop
    1. Устройство: Локальный запуск
    1. Sysroot:
    1. Компилятор: arm-eabi-gcc
    1. Профиль: выбираем любой
    1. Qt mkspec: unsupported/lg-gcc
Все, сохраняем, создаём проект:
    * Как обычно, "Создать новый проект или файл"
    * Проект без использования Qt -> Простой проект на языке С(или С++), далее
    * Вводим имя проекта
    * Выбираем наш компилятор arm-eabi-gcc галочкой, остальные убираем
Все, теперь осталось подстроить проект:
    * Открываем .pro файл
    * Вписываем необходимые либы, по желанию или надобности c, c++, и т.п.
```ini

LIBS   += -lcrt -lscrt -lgcc
```

Дополнительные параметры:
```bash

# имя исполняемого файла
TARGET = atfs.elf

# темплейт, точно не знаю зачем
TEMPLATE = app

# мы не желаем использовать Qt
CONFIG -= qt
```



&lt;hr&gt;


Все, теперь можем собирать проект и кидать на телефон ;)
Удачи!
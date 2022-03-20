QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boss.cpp \
    bullet1.cpp \
    bullet2.cpp \
    changestage1.cpp \
    changestage2.cpp \
    enemiespreset1.cpp \
    enemiespreset2.cpp \
    enemiespreset3.cpp \
    enemiespreset4.cpp \
    enemiespreset5.cpp \
    enemiespreset6.cpp \
    gameoverscreen.cpp \
    gamewinscreen.cpp \
    levelonegraphic.cpp \
    levelthreegraphic.cpp \
    leveltwographic.cpp \
    main.cpp \
    mainwindow.cpp \
    menubuttonlogic.cpp \
    minimenu.cpp \
    spaceship.cpp \
    startmenu.cpp \
    startscreen.cpp

HEADERS += \
    boss.h \
    bullet1.h \
    bullet2.h \
    changestage1.h \
    changestage2.h \
    enemiespreset1.h \
    enemiespreset2.h \
    enemiespreset3.h \
    enemiespreset4.h \
    enemiespreset5.h \
    enemiespreset6.h \
    gameoverscreen.h \
    gamewinscreen.h \
    levelonegraphic.h \
    levelthreegraphic.h \
    leveltwographic.h \
    mainwindow.h \
    minimenu.h \
    spaceship.h \
    startmenu.h \
    startscreen.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    source.qrc

win32-msvc*{
    LIBS += -luser32
}

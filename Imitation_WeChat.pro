QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/backgroundwidget.cpp \
    src/chatmessagebox.cpp \
    src/chatwidget.cpp \
    src/friendlistitem.cpp \
    src/friendlistwidget.cpp \
    src/main.cpp \
    src/loginwidget.cpp \
    src/optionbarwidget.cpp \
    src/roundedbtn.cpp \
    src/wechatmainwidget.cpp

HEADERS += \
    include/backgroundwidget.h \
    include/chatmessagebox.h \
    include/chatwidget.h \
    include/friendlistitem.h \
    include/friendlistwidget.h \
    include/loginwidget.h \
    include/optionbarwidget.h \
    include/roundedbtn.h \
    include/wechatmainwidget.h

FORMS += \
    ui/loginwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc

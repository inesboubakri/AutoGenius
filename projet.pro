QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
TARGET = Atelier_Connexion
TEMPLATE = app
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    aaaa.cpp \
    bbbb.cpp \
    cccc.cpp \
    connection.cpp \
    locaux.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    aaaa.h \
    bbbb.h \
    cccc.h \
    connection.h \
    locaux.h \
    mainwindow.h

FORMS += \
    aaaa.ui \
    bbbb.ui \
    cccc.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

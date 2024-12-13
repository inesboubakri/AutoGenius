QT       += core gui
QT       += sql
QT += core gui serialport
QT += charts
QT += core gui widgets printsupport
QT += axcontainer axserver
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    clients.cpp \
    connection.cpp \
    main.cpp \
    mainabir.cpp \
    mainaziz.cpp \
    mainwindow.cpp \
    service.cpp

HEADERS += \
    arduino.h \
    clients.h \
    connection.h \
    mainabir.h \
    mainaziz.h \
    mainwindow.h \
    service.h

FORMS += \
    mainabir.ui \
    mainaziz.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc

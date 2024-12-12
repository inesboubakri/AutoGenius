QT       += core gui sql
QT       += core gui sql charts
QT       += core serialport widgets
QT += axcontainer
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += core gui printsupport
CONFIG += c++17
TARGET = Atelier_Connexion
TEMPLATE = app
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connection.cpp \
    dialog.cpp \
    emailsender.cpp \
    employee.cpp \
    locaux.cpp \
    mailer.cpp \
    main.cpp \
    mainwindow.cpp \
    service.cpp

HEADERS += \
    connection.h \
    dialog.h \
    emailsender.h \
    employee.h \
    locaux.h \
    mailer.h \
    mainwindow.h \
    service.h

FORMS += \
    dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

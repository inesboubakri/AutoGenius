/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *pushButton;
    QPushButton *pushButton_32;
    QLineEdit *password;
    QPushButton *pushButton_37;
    QLineEdit *cin;
    QCommandLinkButton *commandLinkButton;
    QWidget *page_2;
    QWidget *widget;
    QPushButton *pushButton_33;
    QLineEdit *cin_2;
    QCommandLinkButton *commandLinkButton_2;
    QWidget *widget_2;
    QPushButton *pushButton_34;
    QLineEdit *cin_3;
    QCommandLinkButton *commandLinkButton_3;
    QCommandLinkButton *commandLinkButton_4;
    QWidget *page_3;
    QLineEdit *pass;
    QPushButton *pushButton_35;
    QLineEdit *passretape;
    QPushButton *pushButton_38;
    QPushButton *pushButton_2;
    QCommandLinkButton *commandLinkButton_5;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(551, 340);
        stackedWidget = new QStackedWidget(Dialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 551, 341));
        stackedWidget->setStyleSheet(QString::fromUtf8("\n"
"color:rgb(33, 33, 41);\n"
"font-family: 'Sans-Serif';\n"
" font-size: 20px;    \n"
" background-color: rgb(209, 255, 117);;\n"
"border-radius:20px;\n"
"font-color:white;\n"
"\n"
"\n"
""));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        pushButton = new QPushButton(page);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(354, 220, 111, 23));
        pushButton_32 = new QPushButton(page);
        pushButton_32->setObjectName(QString::fromUtf8("pushButton_32"));
        pushButton_32->setGeometry(QRect(10, 40, 111, 41));
        pushButton_32->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color:rgb(33, 33, 41);\n"
"font-family: 'Sans-Serif';\n"
" font-size: 24px;    \n"
" background-color: transparent;\n"
"border-radius:20px;\n"
"font-color:white;\n"
"\n"
"\n"
"}"));
        password = new QLineEdit(page);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(210, 110, 281, 31));
        password->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    font-family: 'Sans-Serif';\n"
"    font-size: 20px;\n"
"    background-color: white;  /* Couleur de fond blanche */\n"
"    border-radius: 20px;\n"
"}\n"
""));
        password->setEchoMode(QLineEdit::EchoMode::Normal);
        pushButton_37 = new QPushButton(page);
        pushButton_37->setObjectName(QString::fromUtf8("pushButton_37"));
        pushButton_37->setGeometry(QRect(20, 110, 171, 41));
        pushButton_37->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color:rgb(33, 33, 41);\n"
"font-family: 'Sans-Serif';\n"
" font-size: 24px;    \n"
" background-color: transparent;\n"
"border-radius:20px;\n"
"font-color:white;\n"
"\n"
"\n"
"}"));
        cin = new QLineEdit(page);
        cin->setObjectName(QString::fromUtf8("cin"));
        cin->setGeometry(QRect(210, 50, 281, 31));
        cin->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    font-family: 'Sans-Serif';\n"
"    font-size: 20px;\n"
"    background-color: white;  /* Couleur de fond blanche */\n"
"    border-radius: 20px;\n"
"}\n"
""));
        commandLinkButton = new QCommandLinkButton(page);
        commandLinkButton->setObjectName(QString::fromUtf8("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(310, 150, 231, 41));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        widget = new QWidget(page_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 50, 541, 101));
        widget->setStyleSheet(QString::fromUtf8("\n"
"color:rgb(33, 33, 41);\n"
"font-family: 'Sans-Serif';\n"
" font-size: 20px;    \n"
" background-color: rgb(209, 255, 117);;\n"
"border-radius:20px;\n"
"font-color:white;\n"
"\n"
"\n"
""));
        pushButton_33 = new QPushButton(widget);
        pushButton_33->setObjectName(QString::fromUtf8("pushButton_33"));
        pushButton_33->setGeometry(QRect(0, 20, 111, 41));
        pushButton_33->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color:rgb(33, 33, 41);\n"
"font-family: 'Sans-Serif';\n"
" font-size: 24px;    \n"
" background-color: transparent;\n"
"border-radius:20px;\n"
"font-color:white;\n"
"\n"
"\n"
"}"));
        cin_2 = new QLineEdit(widget);
        cin_2->setObjectName(QString::fromUtf8("cin_2"));
        cin_2->setGeometry(QRect(190, 20, 281, 31));
        cin_2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    font-family: 'Sans-Serif';\n"
"    font-size: 20px;\n"
"    background-color: white;  /* Couleur de fond blanche */\n"
"    border-radius: 20px;\n"
"}\n"
""));
        commandLinkButton_2 = new QCommandLinkButton(widget);
        commandLinkButton_2->setObjectName(QString::fromUtf8("commandLinkButton_2"));
        commandLinkButton_2->setGeometry(QRect(210, 50, 331, 31));
        commandLinkButton_2->setStyleSheet(QString::fromUtf8(""));
        widget_2 = new QWidget(page_2);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(10, 170, 541, 141));
        widget_2->setStyleSheet(QString::fromUtf8("\n"
"color:rgb(33, 33, 41);\n"
"font-family: 'Sans-Serif';\n"
" font-size: 20px;    \n"
" background-color: rgb(209, 255, 117);;\n"
"border-radius:20px;\n"
"font-color:white;\n"
"\n"
"\n"
""));
        pushButton_34 = new QPushButton(widget_2);
        pushButton_34->setObjectName(QString::fromUtf8("pushButton_34"));
        pushButton_34->setGeometry(QRect(10, 10, 211, 41));
        pushButton_34->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color:rgb(33, 33, 41);\n"
"font-family: 'Sans-Serif';\n"
" font-size: 24px;    \n"
" background-color: transparent;\n"
"border-radius:20px;\n"
"font-color:white;\n"
"\n"
"\n"
"}"));
        cin_3 = new QLineEdit(widget_2);
        cin_3->setObjectName(QString::fromUtf8("cin_3"));
        cin_3->setGeometry(QRect(170, 60, 281, 31));
        cin_3->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    font-family: 'Sans-Serif';\n"
"    font-size: 20px;\n"
"    background-color: white;  /* Couleur de fond blanche */\n"
"    border-radius: 20px;\n"
"}\n"
""));
        commandLinkButton_3 = new QCommandLinkButton(widget_2);
        commandLinkButton_3->setObjectName(QString::fromUtf8("commandLinkButton_3"));
        commandLinkButton_3->setGeometry(QRect(360, 100, 131, 41));
        commandLinkButton_4 = new QCommandLinkButton(page_2);
        commandLinkButton_4->setObjectName(QString::fromUtf8("commandLinkButton_4"));
        commandLinkButton_4->setGeometry(QRect(20, 0, 185, 31));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        pass = new QLineEdit(page_3);
        pass->setObjectName(QString::fromUtf8("pass"));
        pass->setGeometry(QRect(250, 120, 281, 31));
        pass->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    font-family: 'Sans-Serif';\n"
"    font-size: 20px;\n"
"    background-color: white;  /* Couleur de fond blanche */\n"
"    border-radius: 20px;\n"
"}\n"
""));
        pass->setEchoMode(QLineEdit::EchoMode::Normal);
        pushButton_35 = new QPushButton(page_3);
        pushButton_35->setObjectName(QString::fromUtf8("pushButton_35"));
        pushButton_35->setGeometry(QRect(20, 170, 241, 41));
        pushButton_35->setStyleSheet(QString::fromUtf8("\n"
"color:rgb(33, 33, 41);\n"
"font-family: 'Sans-Serif';\n"
" font-size: 20px;    \n"
" background-color: rgb(209, 255, 117);;\n"
"border-radius:20px;\n"
"font-color:white;\n"
"\n"
"\n"
""));
        passretape = new QLineEdit(page_3);
        passretape->setObjectName(QString::fromUtf8("passretape"));
        passretape->setGeometry(QRect(250, 220, 281, 31));
        passretape->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"\n"
"    font-family: 'Sans-Serif';\n"
"    font-size: 20px;\n"
"    background-color: white;  /* Couleur de fond blanche */\n"
"    border-radius: 20px;\n"
"}\n"
""));
        passretape->setEchoMode(QLineEdit::EchoMode::Normal);
        pushButton_38 = new QPushButton(page_3);
        pushButton_38->setObjectName(QString::fromUtf8("pushButton_38"));
        pushButton_38->setGeometry(QRect(20, 60, 241, 41));
        pushButton_38->setStyleSheet(QString::fromUtf8("\n"
"color:rgb(33, 33, 41);\n"
"font-family: 'Sans-Serif';\n"
" font-size: 20px;    \n"
" background-color: rgb(209, 255, 117);;\n"
"border-radius:20px;\n"
"font-color:white;\n"
"\n"
"\n"
""));
        pushButton_2 = new QPushButton(page_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(350, 300, 111, 23));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color:rgb(33, 33, 41);\n"
"font-family: 'Sans-Serif';\n"
" font-size: 20px;    \n"
" background-color: rgb(209, 255, 117);;\n"
"border-radius:20px;\n"
"font-color:white;\n"
"\n"
"\n"
"}"));
        commandLinkButton_5 = new QCommandLinkButton(page_3);
        commandLinkButton_5->setObjectName(QString::fromUtf8("commandLinkButton_5"));
        commandLinkButton_5->setGeometry(QRect(20, 0, 185, 31));
        stackedWidget->addWidget(page_3);

        retranslateUi(Dialog);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("Dialog", "Connection", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_32->setToolTip(QCoreApplication::translate("Dialog", "<html><head/><body><p><span style=\" color:#d1d938;\">employees</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_32->setText(QCoreApplication::translate("Dialog", "CIN:", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_37->setToolTip(QCoreApplication::translate("Dialog", "<html><head/><body><p><span style=\" color:#d1d938;\">employees</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_37->setText(QCoreApplication::translate("Dialog", "PASSWORD", nullptr));
        commandLinkButton->setText(QCoreApplication::translate("Dialog", "Mot depasse oublier", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_33->setToolTip(QCoreApplication::translate("Dialog", "<html><head/><body><p><span style=\" color:#d1d938;\">employees</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_33->setText(QCoreApplication::translate("Dialog", "CIN :", nullptr));
        commandLinkButton_2->setText(QCoreApplication::translate("Dialog", "enovyer un code de recupuration", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_34->setToolTip(QCoreApplication::translate("Dialog", "<html><head/><body><p><span style=\" color:#d1d938;\">employees</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_34->setText(QCoreApplication::translate("Dialog", "code recupuration:", nullptr));
        cin_3->setText(QString());
        commandLinkButton_3->setText(QCoreApplication::translate("Dialog", "Valider", nullptr));
        commandLinkButton_4->setText(QCoreApplication::translate("Dialog", "Retoure", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_35->setToolTip(QCoreApplication::translate("Dialog", "<html><head/><body><p><span style=\" color:#d1d938;\">employees</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_35->setText(QCoreApplication::translate("Dialog", "Retape Password :", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_38->setToolTip(QCoreApplication::translate("Dialog", "<html><head/><body><p><span style=\" color:#d1d938;\">employees</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_38->setText(QCoreApplication::translate("Dialog", "Nouvaux password :", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Dialog", "Modifier", nullptr));
        commandLinkButton_5->setText(QCoreApplication::translate("Dialog", "Retoure", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H

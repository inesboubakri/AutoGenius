#ifndef MAINABIR_H
#define MAINABIR_H

#include <QMainWindow>
#include"clients.h"
#include"connection.h"
#include <QDesktopServices>
#include <windows.h>
#include "arduino.h"
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class mainabir; }
QT_END_NAMESPACE

class mainabir : public QMainWindow
{
    Q_OBJECT

public:
    mainabir(QWidget *parent = nullptr);
    ~mainabir();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_6_clicked();



    void on_rechercher_clicked();

    void on_refrech_clicked();

    void on_trier_clicked();

    void on_stat_clicked();

    void on_export_2_clicked();



    void on_appel_clicked();

    void on_calendarWidget_clicked(const QDate &date);




    void on_Cancel_clicked();

    void on_afficher_clicked();

    void on_Calender_clicked();
    void readSerialData();


    void on_afficher_3_clicked();

private:
    Ui::mainabir *ui;
    CLIENTS Etmp;
    bool test;
    Arduino ard;
    bool test2;
    QByteArray pixelData;
    QByteArray byteArray2;
    QLabel *imageLabel;
    const int width = 320;
    const int height = 240;

    void processImage();

    void on_afficher_2_clicked();

};
#endif // mainabir_H

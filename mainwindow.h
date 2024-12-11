#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "employee.h"
#include "arduino.h" // Inclure le fichier Arduino
#include <QMainWindow>
#include <QSqlRecord>
#include <QSqlTableModel>
#include "ui_mainwindow.h" // Vérifiez que cette inclusion existe

QT_BEGIN_NAMESPACE
class Arduino;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void load_list_view();
public slots:
    void readarduino();

private slots:
    void on_confirm_add_clicked();
    void on_delete_clicked();
    void on_edit_clicked();
    void on_confirm_edit_clicked();
    void on_modifierpushbutton_clicked();
    void on_gotoedit_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void on_delete_button_clicked();
    void on_researchcin_textChanged(const QString &arg1);
    void on_pushButton_49_clicked();
    void on_pushButton_47_clicked();
    void on_pushButton_50_clicked();
    void on_faceid_clicked();
    void on_capture_clicked();
    void on_pushButton_70_clicked();

    // Nouveau slot pour gérer les données reçues d'Arduino


private:
    Ui::MainWindow *ui;
    int cin;
    QSerialPort *serialPort;
    QByteArray serialData;
    QString serialbuffer;
    Arduino *arduino; // Ajouter l'objet Arduino en tant que membre privé
};

#endif // MAINWINDOW_H

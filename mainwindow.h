#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "locaux.h"
#include <QMainWindow>
#include"zaklabus1.h"
#include"aaaa.h"
#include "bbbb.h"
#include "cccc.h"
#include<QTableView>
#include <QStandardItemModel>
//QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
//QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_18_clicked();
private:
    Ui::MainWindow *ui;
    aaaa *secondWindow;
    bbbb *ThirdWindow;
    cccc *ForthWindow;
    locaux Etmp;
    QSqlQueryModel *model;
    void loadtab();

};
#endif // MAINWINDOW_H

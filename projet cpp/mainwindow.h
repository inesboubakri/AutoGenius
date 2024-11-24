#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vehicule.h"  // Include the Vehicule header file
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QTableView>
#include <QSqlTableModel>
#include <QGraphicsScene>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // UI setup functions
    void setupConsulterListe();
    void setupVehiculeTypeChart();

    //added
     void checkMaintenanceDates(); // Declaration of the missing function

    //end

private slots:
    void on_modbutton_clicked();

    void on_addbutton_clicked();

    void on_viewbutton_clicked();

    void on_ajouterButton_clicked();

    void on_reloadbutton_clicked();

    void on_delete_vec_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_modifier_btn_clicked();

    void on_lineEdit_Search_textChanged(const QString &arg1);

    void on_pushButton_pdf_clicked();

    // added by
    void on_pushButton_tri_clicked();  // Slot for the filter button
    void on_pushButtonDate_clicked();
    void on_pushButtonQR_clicked();

    //stat
    void on_statsButton_clicked(); // Slot for the statistics button
    //end

private:
    Ui::MainWindow *ui;
    //Vehicule Vtmp;   // Vehicule manager object, replace Partnership with Vehicule
    QTableView *tableView;
    vehicule vec;

    //added
    QGraphicsScene *graphicsScene;
    void displayStatisticsByAddress();
    //end
};

#endif // MAINWINDOW_H


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "partnership.h"
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QTableView>
#include <QSqlTableModel>
#include <QtCharts>

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
    void setupPartnershipSectorChart();

private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_update_clicked();
    void on_pushButton_search_clicked();
    void extractToPdf();
    void on_pushButton_refresh_clicked();

private:
    Ui::MainWindow *ui;
    Partnership Ptmp;   // Partnership manager object
    QTableView *tableView;
};

#endif // MAINWINDOW_H

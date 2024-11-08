#ifndef CCCC_H
#define CCCC_H
#include"Qmainwindow.h"
#include <QDialog>
#include"locaux.h"
#include<QTableView>
#include<QStandardItemModel>
#include <QSqlQueryModel>
namespace Ui {
class cccc;
}

class cccc : public QDialog
{
    Q_OBJECT

public:
    explicit cccc(QWidget *parent = nullptr);
    ~cccc();
signals:
    void localmod();
private slots:
    void tableView_clicked(const QModelIndex &index);
    void on_pushButton_2_clicked();
    void on_pushButton_mod_clicked();

private:
    Ui::cccc *ui;
    //locaux Etmp;
    locaux currentLocal;
    QSqlQueryModel *model;
    void loadTable();
    QMainWindow *ForthWindow;
    QTableView *m_tableView;
    void populateLineEdits();

};

#endif // CCCC_H

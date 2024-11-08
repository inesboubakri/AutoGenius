#ifndef AAAA_H
#define AAAA_H
#include"Qmainwindow.h"
#include <QDialog>
#include"locaux.h"
#include<QTableView>
#include<QStandardItemModel>
namespace Ui {
class aaaa;
}

class aaaa : public QDialog
{
    Q_OBJECT

public:
    explicit aaaa(QWidget *parent = nullptr, QTableView *tableView = nullptr);
    ~aaaa();
signals:
    void localAdded();
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_ajouter_clicked();
private:
    Ui::aaaa *ui;
    locaux Etmp;
    QMainWindow *FirstWindow;
    QTableView *m_tableView;

};

#endif // AAAA_H

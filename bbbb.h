#ifndef BBBB_H
#define BBBB_H
#include"Qmainwindow.h"
#include"locaux.h"
#include <QDialog>
#include <QTableView>
namespace Ui {
class bbbb;
}

class bbbb : public QDialog
{
    Q_OBJECT

public:
    explicit bbbb(QWidget *parent = nullptr, QTableView *tableView = nullptr);
    ~bbbb();
signals:
    void localdel();
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_delete_clicked();
private:
    Ui::bbbb *ui;
    locaux Etmp;
    QMainWindow *ThirdWindow;
    QTableView *m_tableView;
};

#endif // BBBB_H

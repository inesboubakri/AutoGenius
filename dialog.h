#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include"employee.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_commandLinkButton_clicked();

    void on_commandLinkButton_2_clicked();

    void on_commandLinkButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_commandLinkButton_5_clicked();

    void on_commandLinkButton_4_clicked();

private:
    Ui::Dialog *ui;
    Employees emp;
    int cin;
};

#endif // DIALOG_H

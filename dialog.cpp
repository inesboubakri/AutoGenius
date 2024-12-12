#include "dialog.h"
#include "ui_dialog.h"
#include<QMessageBox>
#include "mainwindow.h"
#include"emailsender.h"
#include"mailer.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->widget_2->hide();

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    int cin =ui->cin->text().toInt();
    QString password=ui->password->text();
    bool test=emp.connexion(cin,password);
    if(test){ QMessageBox::information (nullptr, QObject::tr("OK"),
                                 QObject::tr("Connection effectué  avec succee\n"
                                             "Click Cancel to exit."), QMessageBox::Ok);
        MainWindow *w = new MainWindow();
        w->show();
        this->hide();


    }
    else{
        QMessageBox::information (nullptr, QObject::tr("warning"),
                                 QObject::tr("verifier votre corrdonait\n"
                                             "Click Cancel to exit."), QMessageBox::Ok);
    }
}

void Dialog::on_commandLinkButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void Dialog::on_commandLinkButton_2_clicked()
{
    QString cinStr = ui->cin_2->text();

    // Contrôle de saisie : Vérifier que le CIN est un nombre à 8 chiffres
    if (cinStr.isEmpty() || !cinStr.toUInt() || cinStr.length() != 8) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un CIN valide (8 chiffres).");
        return;
    }

    int cin = cinStr.toInt();
    bool test = emp.genererCodeParCIN(cin);
    if (test) {
        ui->widget->hide();
        this->cin = cin; // Stocker le CIN pour un usage ultérieur
        ui->widget_2->show();
    }
}


void Dialog::on_commandLinkButton_3_clicked()
{
    QString codestr = ui->cin_3->text();

    if (codestr.isEmpty() || !codestr.toUInt() || codestr.length() != 7) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un code valide (7 chiffres).");
        return;
    }

    int code = codestr.toInt();
    bool test = emp.verifierEtSupprimerCode(code);
    if (test) {
        ui->stackedWidget->setCurrentIndex(2);
    }
}


void Dialog::on_pushButton_2_clicked()
{
    QString pass = ui->pass->text();
    QString pass2 = ui->passretape->text();

    if (pass.isEmpty() || pass2.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Les champs de mot de passe ne peuvent pas être vides.");
        return;
    }

    if (pass != pass2) {
        QMessageBox::warning(this, "Erreur", "Les mots de passe ne correspondent pas.");
        return;
    }

    if (pass.length() <= 6) {
        QMessageBox::warning(this, "Erreur", "Le mot de passe doit contenir plus de 6 caractères.");
        return;
    }

    bool test = emp.modifierMotDePasse(cin, pass);
    if (test) {
        MainWindow* w = new MainWindow();
        w->show();
        this->hide();
    } else {
        QMessageBox::warning(this, "Erreur", "La modification du mot de passe a échoué.");
    }
}



void Dialog::on_commandLinkButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->widget_2->hide();
    ui->widget->show();


}


void Dialog::on_commandLinkButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->widget_2->hide();
    ui->widget->show();

}


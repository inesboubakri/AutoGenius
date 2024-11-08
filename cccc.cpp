#include "cccc.h"
#include "ui_cccc.h"
#include"mainwindow.h"
#include"locaux.h"
#include <QMessageBox>
#include<QObject>
#include"connection.h"
#include<QTableView>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
cccc::cccc(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cccc)
    ,model(new QSqlQueryModel(this))
    ,ForthWindow(new QMainWindow(this))
    //,m_tableView(tableView)
{
    ui->setupUi(this);
    loadTable();
    connect(ui->pushButton_2, &QPushButton::clicked, this, &cccc::on_pushButton_2_clicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &cccc::on_pushButton_mod_clicked);
    connect(ui->tableView, &QTableView::clicked, this, &cccc::tableView_clicked);
}

cccc::~cccc()
{
    delete ui;
}
void cccc::on_pushButton_2_clicked()
{
    accept();
}
void cccc::loadTable()
{
    // Populate the model with data from the "locaux" table
    model->setQuery("SELECT * FROM locaux");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUMERO_TELEPHONE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_LOCALE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("SERVICE_DISPONIBLE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOM_MANAGER_LOCALE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("STATUT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CAPACITE_VEHICULE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("NOMBRE_EMPLOYEES"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("CIN"));

    // Set model to the table view
    ui->tableView->setModel(model);

    // Allow in-place editing of table data
   // ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
}
void cccc::tableView_clicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    // Retrieve record data from the selected row
    int row = index.row();
    currentLocal.setNOM_LOCALE(model->record(row).value("NOM_LOCALE").toString());
    currentLocal.setNOM_MANAGER_LOCALE(model->record(row).value("NOM_MANAGER_LOCALE").toString());
    currentLocal.setSERVICE_DISPONIBLE(model->record(row).value("SERVICE_DISPONIBLE").toString());
    currentLocal.setADRESSE(model->record(row).value("ADRESSE").toString());
    currentLocal.setSTATUT(model->record(row).value("STATUT").toString());
    currentLocal.setCAPACITE_VEHICULE(model->record(row).value("CAPACITE_VEHICULE").toInt());
    currentLocal.setNUMERO_TELEPHONE(model->record(row).value("NUMERO_TELEPHONE").toInt());
    currentLocal.setNOMBRE_EMPLOYEES(model->record(row).value("NOMBRE_EMPLOYEES").toInt());
    currentLocal.setCIN(model->record(row).value("CIN").toInt());

    // Populate line edits with selected row data
    populateLineEdits();
}
void cccc::populateLineEdits()
{
    ui->lineEditNomLocale->setText(currentLocal.getNOM_LOCALE());
    ui->lineEditManager->setText(currentLocal.getNOM_MANAGER_LOCALE());
    ui->lineEditService->setText(currentLocal.getSERVICE_DISPONIBLE());
    ui->lineEditAdresse->setText(currentLocal.getADRESSE());
    ui->lineEditStatut->setText(currentLocal.getSTATUT());
    ui->lineEditCapacite->setText(QString::number(currentLocal.getCAPACITE_VEHICULE()));
    ui->lineEditTelephone->setText(QString::number(currentLocal.getNUMERO_TELEPHONE()));
    ui->lineEditEmployees->setText(QString::number(currentLocal.getNOMBRE_EMPLOYEES()));
    ui->lineEditCIN->setText(QString::number(currentLocal.getCIN()));
}

void cccc::on_pushButton_mod_clicked()
{
    // Update currentLocal object with new data from input fields
    currentLocal.setNOM_LOCALE(ui->lineEditNomLocale->text());
    currentLocal.setNOM_MANAGER_LOCALE(ui->lineEditManager->text());
    currentLocal.setSERVICE_DISPONIBLE(ui->lineEditService->text());
    currentLocal.setADRESSE(ui->lineEditAdresse->text());
    currentLocal.setSTATUT(ui->lineEditStatut->text());
    currentLocal.setCAPACITE_VEHICULE(ui->lineEditCapacite->text().toInt());
    currentLocal.setNUMERO_TELEPHONE(ui->lineEditTelephone->text().toInt());
    currentLocal.setNOMBRE_EMPLOYEES(ui->lineEditEmployees->text().toInt());
    currentLocal.setCIN(ui->lineEditCIN->text().toInt());

    // Update the record in the database
    if (currentLocal.modifier()) {
        emit localmod(); // Emit signal to update main table in MainWindow
        loadTable();
        ui->tableView->setModel(model);
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("Modifier effectue\n"
                                             "Click Sortir to exit"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                              QObject::tr("Modifier Non effectue\n"
                                          "Click Sortir to exit"),QMessageBox::Cancel);
}

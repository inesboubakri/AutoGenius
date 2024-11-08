#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QFileDialog>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QDebug>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include "vehicule.h"

// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Vtmp.afficher_vehicule());  // Display initial data in the table
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: white; color: black; }");

    // Connect buttons to their respective slots
    connect(ui->pushButton_update, &QPushButton::clicked, this, &MainWindow::on_pushButton_update_clicked);
    connect(ui->pushButton_search, &QPushButton::clicked, this, &MainWindow::on_pushButton_search_clicked);
    connect(ui->pushButton_extract, &QPushButton::clicked, this, &MainWindow::extractToPdf);
    connect(ui->pushButton_refresh, &QPushButton::clicked, this, &MainWindow::on_pushButton_refresh_clicked);
    connect(ui->pushButton_supprimer, &QPushButton::clicked, this, &MainWindow::on_pushButton_supprimer_clicked);

    // Setup initial UI
    setupConsulterListe();
    setupVehiculeTypeChart();

    // Input validation
    ui->lineEdit_matricule->setValidator(new QIntValidator(1, 1000000, this));
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// Slot for adding a vehicle
void MainWindow::on_pushButton_ajouter_clicked()
{
    QString matricule = ui->lineEdit_matricule->text();
    QString marque_vehicule = ui->lineEdit_marque->text();
    QString modele = ui->lineEdit_modele->text();
    QString type_vehicule = ui->lineEdit_type->text();
    QString date_dr_entretient = ui->lineEdit_date_entretient->text();
    QString type_transmission = ui->lineEdit_transmission->text();
    QString statut = ui->lineEdit_statut->text();

    if (matricule.isEmpty() || marque_vehicule.isEmpty() || modele.isEmpty() || type_vehicule.isEmpty() ||
        date_dr_entretient.isEmpty() || type_transmission.isEmpty() || statut.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields.");
        return;
    }

    Vehicule vehicule(matricule, marque_vehicule, modele, type_vehicule, date_dr_entretient, type_transmission, statut);

    if (vehicule.ajouter()) {
        ui->tableView->setModel(Vtmp.afficher_vehicule());
        QMessageBox::information(this, "Success", "Vehicle added successfully.");
    } else {
        QMessageBox::critical(this, "Failure", "Failed to add vehicle.");
    }
}

// Slot for deleting a vehicle
void MainWindow::on_pushButton_supprimer_clicked()
{
    QString matricule = ui->lineEdit_matricule_delete->text();

    if (Vtmp.supprimer(matricule)) {
        ui->tableView->setModel(Vtmp.afficher_vehicule());
        QMessageBox::information(this, "Success", "Vehicle deleted successfully.");
    } else {
        QMessageBox::critical(this, "Failure", "Failed to delete vehicle.");
    }
}

// Slot for updating a vehicle
void MainWindow::on_pushButton_update_clicked()
{
    QString matricule = ui->lineEdit_matricule->text();
    QString marque_vehicule = ui->lineEdit_marque->text();
    QString modele = ui->lineEdit_modele->text();
    QString type_vehicule = ui->lineEdit_type->text();
    QString date_dr_entretient = ui->lineEdit_date_entretient->text();
    QString type_transmission = ui->lineEdit_transmission->text();
    QString statut = ui->lineEdit_statut->text();

    if (matricule.isEmpty() || marque_vehicule.isEmpty() || modele.isEmpty() || type_vehicule.isEmpty() ||
        date_dr_entretient.isEmpty() || type_transmission.isEmpty() || statut.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields.");
        return;
    }

    Vehicule vehicule(matricule, marque_vehicule, modele, type_vehicule, date_dr_entretient, type_transmission, statut);

    if (vehicule.modifier(matricule)) {
        ui->tableView->setModel(Vtmp.afficher_vehicule());
        QMessageBox::information(this, "Update Successful", "The vehicle has been updated successfully.");
    } else {
        QMessageBox::critical(this, "Update Failed", "Failed to update the vehicle.");
    }
}

// Slot for searching vehicles
void MainWindow::on_pushButton_search_clicked()
{
    QString searchTerm = ui->lineEdit_search->text();
    if (searchTerm.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a search term.");
        return;
    }

    ui->tableView->setModel(Vtmp.search(searchTerm));
}

// Slot for exporting vehicles to PDF
void MainWindow::extractToPdf()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "*.pdf");
    if (filePath.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    QPainter painter(&printer);
    int rowHeight = 500;
    int xOffset = 50;
    int yOffset = 100;
    int pageWidth = printer.pageRect().width();

    int numColumns = ui->tableView->model()->columnCount();
    int numRows = ui->tableView->model()->rowCount();
    int columnWidth = pageWidth / numColumns;

    for (int col = 0; col < numColumns; ++col) {
        QString header = ui->tableView->model()->headerData(col, Qt::Horizontal).toString();
        painter.drawText(xOffset + col * columnWidth, yOffset, header);
    }

    yOffset += rowHeight;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numColumns; ++col) {
            QModelIndex index = ui->tableView->model()->index(row, col);
            QString data = index.data().toString();
            painter.drawText(xOffset + col * columnWidth, yOffset + row * rowHeight, data);
        }
    }

    painter.end();
    QMessageBox::information(this, "Export to PDF", "The list has been successfully exported as a PDF.");
}

// Slot for refreshing the table view
void MainWindow::on_pushButton_refresh_clicked()
{
    ui->tableView->setModel(Vtmp.afficher_vehicule());
}

// Setup function to initialize the list view for vehicles
void MainWindow::setupConsulterListe()
{
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("VEHICULE");
    model->select();
    model->setSort(0, Qt::AscendingOrder);

    ui->tableView->setModel(model);
    ui->tableView->setSortingEnabled(true);
}

// Setup function to initialize the vehicle type chart
void MainWindow::setupVehiculeTypeChart()
{
    QMap<QString, int> typeData = Vtmp.getVehiculesByType();

    QtCharts::QBarSet *typeSet = new QtCharts::QBarSet("Number of Vehicles");

    QStringList categories;
    for (auto it = typeData.constBegin(); it != typeData.constEnd(); ++it) {
        categories << it.key();
        *typeSet << it.value();
    }

    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    series->append(typeSet);

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Vehicles by Type");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setTitleText("Number of Vehicles");
    axisY->

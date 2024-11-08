#include "PARTNERSHIP_interface.h"
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

// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Ptmp.afficher());  // Display initial data in the table
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
    setupPartnershipSectorChart();

    // Input validation
    ui->lineEdit_phone->setValidator(new QIntValidator(1, 1000000, this));
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// Slot for adding a partnership
void MainWindow::on_pushButton_ajouter_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString businessSector = ui->lineEdit_businessSector->text();
    int phone = ui->lineEdit_phone->text().toInt();
    QString address = ui->lineEdit_address->text();
    QString email = ui->lineEdit_email->text();
    QString type = ui->lineEdit_type->text();
    QString startDate = ui->lineEdit_startDate->text();
    QString endDate = ui->lineEdit_endDate->text();
    QString status = ui->lineEdit_status->text();

    if (name.isEmpty() || businessSector.isEmpty() || address.isEmpty() || email.isEmpty() || type.isEmpty() || startDate.isEmpty() || endDate.isEmpty() || status.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields.");
        return;
    }

    Partnership partnership(name, businessSector, phone, address, email, type, startDate, endDate, status);

    if (partnership.ajouter()) {
        ui->tableView->setModel(Ptmp.afficher());
        QMessageBox::information(this, "Success", "Partnership added successfully.");
    } else {
        QMessageBox::critical(this, "Failure", "Failed to add partnership.");
    }
}

// Slot for deleting a partnership
void MainWindow::on_pushButton_supprimer_clicked()
{
    int phone = ui->lineEdit_phone_delete->text().toInt();

    if (Ptmp.supprimer(phone)) {
        ui->tableView->setModel(Ptmp.afficher());
        QMessageBox::information(this, "Success", "Partnership deleted successfully.");
    } else {
        QMessageBox::critical(this, "Failure", "Failed to delete partnership.");
    }
}

// Slot for updating a partnership
void MainWindow::on_pushButton_update_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString businessSector = ui->lineEdit_businessSector->text();
    int phone = ui->lineEdit_phone->text().toInt();
    QString address = ui->lineEdit_address->text();
    QString email = ui->lineEdit_email->text();
    QString type = ui->lineEdit_type->text();
    QString startDate = ui->lineEdit_startDate->text();
    QString endDate = ui->lineEdit_endDate->text();
    QString status = ui->lineEdit_status->text();

    if (name.isEmpty() || businessSector.isEmpty() || address.isEmpty() || email.isEmpty() || type.isEmpty() || startDate.isEmpty() || endDate.isEmpty() || status.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields.");
        return;
    }

    Partnership partnership(name, businessSector, phone, address, email, type, startDate, endDate, status);

    if (partnership.modifier(phone)) {
        ui->tableView->setModel(Ptmp.afficher());
        QMessageBox::information(this, "Update Successful", "The partnership has been updated successfully.");
    } else {
        QMessageBox::critical(this, "Update Failed", "Failed to update the partnership.");
    }
}

// Slot for searching partnerships
void MainWindow::on_pushButton_search_clicked() {
    QString searchTerm = ui->lineEdit_search->text();
    if (searchTerm.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a search term.");
        return;
    }

    ui->tableView->setModel(Ptmp.search(searchTerm));
}

// Slot for exporting partnerships to PDF
void MainWindow::extractToPdf() {
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
void MainWindow::on_pushButton_refresh_clicked() {
    ui->tableView->setModel(Ptmp.afficher());
}

// Setup function to initialize the list view
void MainWindow::setupConsulterListe()
{
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("PARTNERSHIP");
    model->select();
    model->setSort(0, Qt::AscendingOrder);

    ui->tableView->setModel(model);
    ui->tableView->setSortingEnabled(true);
}

// Setup function to initialize the sector chart
void MainWindow::setupPartnershipSectorChart() {
    QMap<QString, int> sectorData = Ptmp.getPartnershipsBySector();

    QtCharts::QBarSet *sectorSet = new QtCharts::QBarSet("Number of Partnerships");

    QStringList categories;
    for (auto it = sectorData.constBegin(); it != sectorData.constEnd(); ++it) {
        categories << it.key();
        *sectorSet << it.value();
    }

    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    series->append(sectorSet);

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Partnerships by Business Sector");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setTitleText("Number of Partnerships");
    axisY->setLabelFormat("%.0f");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->chartLayout->addWidget(chartView);
}

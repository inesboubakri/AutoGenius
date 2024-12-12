#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "locaux.h"
#include "qsqlerror.h"
#include "qsqltablemodel.h"
#include <QStackedWidget>
#include <QMessageBox>
#include <QObject>
#include <QTableView>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QInputDialog>
#include <QRegularExpression>
#include <QRandomGenerator>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QAxObject>
#include <QAxWidget>
#include <QPainter>
#include <QTextDocument>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QVariant>
#include <QTimer>
#include <QDate>
#include <QBrush>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isSidebarVisible(true)
    , modelloc(new QSqlQueryModel(this))
    , proxyModelloc(new QSortFilterProxyModel(this))
    , modellocdel(new QSqlQueryModel(this))
    , proxyModellocdel(new QSortFilterProxyModel(this))
    , modellocmod(new QSqlQueryModel(this))
    , proxyModellocmod(new QSortFilterProxyModel(this))
    , modellochis(new QSqlQueryModel(this))
    , proxyModellochis(new QSortFilterProxyModel(this))
    , modelemp(new QSqlQueryModel(this))
    , proxyModelemp(new QSortFilterProxyModel(this))
    , modelser(new QSqlQueryModel(this))
    , proxyModelser(new QSortFilterProxyModel(this))
    , modelsertools(new QSqlQueryModel(this))
    , proxyModelsertools(new QSortFilterProxyModel(this))
    , modelsertask(new QSqlQueryModel(this))
    , proxyModelsertask(new QSortFilterProxyModel(this))

{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("service"));
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::toggleSidebar);
    QPushButton *returnButton = new QPushButton(this);
    returnButton->setIcon(QIcon(":/resources/img.qrc/../../qt/format_justify_center.png"));
    returnButton->setIconSize(QSize(24, 24)); // Adjust icon size
    returnButton->setFixedSize(32, 32); // Adjust button size
    returnButton->setStyleSheet("QPushButton{background-color:rgb(255, 255, 255);border-radius: 5px;padding: 5px;}QPushButton:Hover {background-color: rgb(159, 159, 159);border-color: rgb(159, 159, 159);}"); // Remove border for a cleaner look
    returnButton->move(10, 10); // Place it in the top-left corner with padding
    returnButton->hide(); // Initially hidden
    connect(returnButton, &QPushButton::clicked, this, &MainWindow::showSidebar);

    //locaux modifier
    connect(ui->tableViewlocmod, &QTableView::clicked, this, &MainWindow::tableViewlocmod_clicked);
    // Initialize animations
    sidebarAnimation = new QPropertyAnimation(ui->widget, "geometry");
    frameAnimation = new QPropertyAnimation(ui->frame, "geometry");

    // Save the return button for later use
    this->setProperty("returnButton", QVariant::fromValue<QPushButton *>(returnButton));
    loadtabser();

    proxyModelloc->setSourceModel(modelloc);
    ui->tableViewloc->setModel(proxyModelloc);
    proxyModellocdel->setSourceModel(modellocdel);
    ui->tableViewlocdel->setModel(proxyModellocdel);
    proxyModellocmod->setSourceModel(modellocmod);
    ui->tableViewlocmod->setModel(proxyModellocmod);
    proxyModellochis->setSourceModel(modellochis);
    ui->tablelochistory->setModel(proxyModellochis);
    //employee
    proxyModelemp->setSourceModel(modelemp);
    ui->tableView_emp->setModel(proxyModelemp);
    ui->tableView_emp->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_emp->setSelectionMode(QAbstractItemView::SingleSelection);
    //service
    proxyModelemp->setSourceModel(modelser);
    ui->tableView_emp->setModel(proxyModelser);
    proxyModelemp->setSourceModel(modelsertools);
    ui->tableView_emp->setModel(proxyModelsertools);
    proxyModelemp->setSourceModel(modelsertask);
    ui->tableView_emp->setModel(proxyModelsertask);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete sidebarAnimation;
    delete frameAnimation;
}

//sidebar
void MainWindow::toggleSidebar()
{
    QRect sidebarStart = ui->widget->geometry();
    QRect frameStart = ui->frame->geometry();

    QRect sidebarEnd = sidebarStart;
    QRect frameEnd = frameStart;

    QPushButton *returnButton = this->property("returnButton").value<QPushButton *>();

    if (isSidebarVisible) {
        // Slide sidebar out (left)
        sidebarEnd.setLeft(-sidebarStart.width());
        sidebarEnd.setRight(0);

        // Expand frame
        frameEnd.setLeft(0);

        // Show the return button
        returnButton->show();
    } else {
        // Slide sidebar in (visible)
        sidebarEnd.setLeft(0);
        sidebarEnd.setRight(sidebarStart.width());

        // Shrink frame
        frameEnd.setLeft(sidebarStart.width());

        // Hide the return button
        returnButton->hide();
    }

    // Animate sidebar
    sidebarAnimation->setDuration(300);
    sidebarAnimation->setStartValue(sidebarStart);
    sidebarAnimation->setEndValue(sidebarEnd);
    sidebarAnimation->start();

    // Animate frame
    frameAnimation->setDuration(300);
    frameAnimation->setStartValue(frameStart);
    frameAnimation->setEndValue(frameEnd);
    frameAnimation->start();

    // Toggle visibility state
    isSidebarVisible = !isSidebarVisible;
}
void MainWindow::showSidebar()
{
    // Trigger sidebar toggle only if it’s hidden
    if (!isSidebarVisible) {
        toggleSidebar();
    }
}

//clear line edit
//locaux
void MainWindow::locaddclearline(){
    ui->lineEditLNomlocale->clear();
    ui->lineEditLAdresse->clear();
    ui->lineEditLNommanager->clear();
    ui->lineEditLCapacitevehicule->clear();
    ui->lineEditLCIN->clear();
    ui->lineEditLNombreemployees->clear();
    ui->lineEditLNumerotelephone->clear();
    ui->lineEditLServices->clear();
}
void MainWindow::locmodclearline(){
    ui->lineEdit_locmod_nomlocale->clear();
    ui->lineEdit_locmod_adresse->clear();
    ui->lineEdit_locmod_nommanager->clear();
    ui->lineEdit_locmod_capacite->clear();
    ui->lineEdit_locmod_cin->clear();
    ui->lineEdit_locmod_nombre->clear();
    ui->lineEdit_locmod_numero->clear();
    ui->lineEdit_locmod_service->clear();
}

//load tableview
//locaux
void MainWindow::loadtabloc(){
    locaux l;
    modelloc=l.afficher();
    proxyModelloc->setSourceModel(modelloc);  // Set model for proxy
    ui->tableViewloc->setModel(proxyModelloc);
}
void MainWindow::loadtabser(){
    service l;
    modelser=l.afficher();
    proxyModelser->setSourceModel(modelser);  // Set model for proxy
    ui->tableViewser->setModel(proxyModelser);
}
/*void MainWindow::loadtabsertask(){
    service l;
    modelsertask=l.afficher();
    proxyModelsertask->setSourceModel(modelsertask);  // Set model for proxy
    ui->tableViewsertask->setModel(proxyModelsertask);
}*/
void MainWindow::loadtabsertools(){
    service l;
    modelsertools=l.afficher();
    proxyModelsertools->setSourceModel(modelsertools);  // Set model for proxy
    ui->tableViewsertools->setModel(proxyModelsertools);
}
void MainWindow::loadtabemp(){
    Employees e;
    modelemp=e.afficher();
    proxyModelemp->setSourceModel(modelemp);  // Set model for proxy
    ui->tableView_emp->setModel(proxyModelemp);
}
void MainWindow::loadtablocdel(){
    modellocdel->setQuery("SELECT NOM_LOCALE, NOM_MANAGER_LOCALE, SERVICE_DISPONIBLE, ADRESSE, STATUT, CAPACITE_VEHICULE, NUMERO_TELEPHONE, NOMBRE_EMPLOYEES, CIN_EMPLOYEES FROM locaux");
    // Set headers if needed
    modellocdel->setHeaderData(0, Qt::Horizontal, "Locale Name");
    modellocdel->setHeaderData(1, Qt::Horizontal, "Manager Name");
    ui->tableViewlocdel->setModel(modellocdel);
    ui->tableViewlocdel->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewlocdel->setSelectionMode(QAbstractItemView::SingleSelection);
}
void MainWindow::loadtablocmod(){
    modellocmod->setQuery("SELECT * FROM locaux");
    modellocmod->setHeaderData(0, Qt::Horizontal, QObject::tr("NUMERO_TELEPHONE"));
    modellocmod->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_LOCALE"));
    modellocmod->setHeaderData(6, Qt::Horizontal, QObject::tr("SERVICE_DISPONIBLE"));
    modellocmod->setHeaderData(2, Qt::Horizontal, QObject::tr("ADRESSE"));
    modellocmod->setHeaderData(4, Qt::Horizontal, QObject::tr("NOM_MANAGER_LOCALE"));
    modellocmod->setHeaderData(5, Qt::Horizontal, QObject::tr("STATUT"));
    modellocmod->setHeaderData(3, Qt::Horizontal, QObject::tr("CAPACITE_VEHICULE"));
    modellocmod->setHeaderData(7, Qt::Horizontal, QObject::tr("NOMBRE_EMPLOYEES"));
    modellocmod->setHeaderData(8, Qt::Horizontal, QObject::tr("CIN_EMPLOYEES"));

    // Set model to the table view
    ui->tableViewlocmod->setModel(modellocmod);
}

//locaux modifier
void MainWindow::tableViewlocmod_clicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    // Retrieve record data from the selected row
    int row = index.row();
    currentLocal.setNOM_LOCALE(modellocmod->record(row).value("NOM_LOCALE").toString());
    currentLocal.setNOM_MANAGER_LOCALE(modellocmod->record(row).value("NOM_MANAGER_LOCALE").toString());
    currentLocal.setSERVICE_DISPONIBLE(modellocmod->record(row).value("SERVICE_DISPONIBLE").toString());
    currentLocal.setADRESSE(modellocmod->record(row).value("ADRESSE").toString());
    currentLocal.setSTATUT(modellocmod->record(row).value("STATUT").toString());
    currentLocal.setCAPACITE_VEHICULE(modellocmod->record(row).value("CAPACITE_VEHICULE").toInt());
    currentLocal.setNUMERO_TELEPHONE(modellocmod->record(row).value("NUMERO_TELEPHONE").toInt());
    currentLocal.setNOMBRE_EMPLOYEES(modellocmod->record(row).value("NOMBRE_EMPLOYEES").toInt());
    currentLocal.setCIN_EMPLOYEES(modellocmod->record(row).value("CIN_EMPLOYEES").toInt());

    // Populate line edits with selected row data
    populateLineEditsloc();
}
void MainWindow::populateLineEditsloc()
{
    ui->lineEdit_locmod_nomlocale->setText(currentLocal.getNOM_LOCALE());
    ui->lineEdit_locmod_nommanager->setText(currentLocal.getNOM_MANAGER_LOCALE());
    ui->lineEdit_locmod_service->setText(currentLocal.getSERVICE_DISPONIBLE());
    ui->lineEdit_locmod_adresse->setText(currentLocal.getADRESSE());
    ui->comboBox_locmod->setCurrentText(currentLocal.getSTATUT());
    ui->lineEdit_locmod_capacite->setText(QString::number(currentLocal.getCAPACITE_VEHICULE()));
    ui->lineEdit_locmod_numero->setText(QString::number(currentLocal.getNUMERO_TELEPHONE()));
    ui->lineEdit_locmod_nombre->setText(QString::number(currentLocal.getNOMBRE_EMPLOYEES()));
    ui->lineEdit_locmod_cin->setText(QString::number(currentLocal.getCIN_EMPLOYEES()));
}

//trier locaux
void MainWindow::sortlocTable()
{
    QString triloc=ui->comboBox_loctri->currentText();
    int tri;
    if(triloc=="Nombre_employees")tri=7;
    else if(triloc=="Capacite_vehicule")tri=3;
    else if(triloc=="CIN")tri=8;
    proxyModelloc->sort(tri, Qt::AscendingOrder);
}
//exporter PDF
void MainWindow::exportToPDF() {
    // Open a file dialog to specify the output PDF file location
    QString filePath = QFileDialog::getSaveFileName(this, "Save as PDF", "", "*.pdf");
    if (filePath.isEmpty()) {
        return; // Exit if no file path is specified
    }

    // Add the ".pdf" extension if the user did not provide it
    if (QFileInfo(filePath).suffix().isEmpty()) {
        filePath += ".pdf";
    }

    // Create a QPrinter object to configure the PDF output
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    // Get the size of the printable area
    QSizeF printerSize = printer.pageLayout().paintRect(QPageLayout::Point).size();

    // Get the size of the table view
    QSize tableSize = ui->tableViewloc->size();

    // Calculate the scale factors
    qreal xScale = printerSize.width() / tableSize.width();
    qreal yScale = printerSize.height() / tableSize.height();
    qreal scale = qMin(xScale, yScale); // Maintain aspect ratio

    // Adjust scale to make the table larger
    scale *= 15; // Increase by 50% (adjust as needed)

    // Create a QPainter to draw content on the printer
    QPainter painter(&printer);
    painter.scale(scale, scale);

    // Render the table view onto the printer
    ui->tableViewloc->render(&painter);

    painter.end(); // End the painter

    // Confirm export success
    QMessageBox::information(this, "Export Successful", "The table has been successfully exported to PDF.");
}

//recherche locaux

void MainWindow::searchNomLocale(int columnIndex) {
    QString searchText = ui->lineEdit_locrecherche->text().trimmed();

    if (searchText.isEmpty()) {
        //QMessageBox::warning(this, "Erreur", "Veuillez entrer un locale pour rechercher.");
        loadtabloc();
        return;
    }

    QAbstractItemModel *originalModel = ui->tableViewloc->model(); // Get the current model
    QStandardItemModel *filteredModel = new QStandardItemModel(this); // Create a new model for matching rows

    // Set headers for the new model (assuming the original model has headers)
    for (int i = 0; i < originalModel->columnCount(); ++i) {
        filteredModel->setHorizontalHeaderItem(i, new QStandardItem(originalModel->headerData(i, Qt::Horizontal).toString()));
    }

    bool found = false;

    // Loop through the original model and add matching rows to the new model
    for (int row = 0; row < originalModel->rowCount(); ++row) {
        QModelIndex index = originalModel->index(row, columnIndex);
        QString cellText = originalModel->data(index).toString();

        if (cellText.compare(searchText, Qt::CaseInsensitive) == 0) {
            found = true;

            // Create a new row for the filtered model
            QList<QStandardItem *> items;
            for (int col = 0; col < originalModel->columnCount(); ++col) {
                items.append(new QStandardItem(originalModel->data(originalModel->index(row, col)).toString()));
            }
            filteredModel->appendRow(items);
        }
    }

    if (!found) {
        QMessageBox::information(this, "Résultat", "Aucun résultat trouvé pour le locale spécifié.");
    } else {
        // Load the filtered model into the table view
        ui->tableViewloc->setModel(filteredModel);

    }
}
void MainWindow::showEmployeeChartloc()
{
    QSqlQuery query;
    query.exec("SELECT NOM_LOCALE, NOMBRE_EMPLOYEES FROM locaux");

    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Number of Employees");

    QStringList categories;
    int maxEmployees = 0;

    while (query.next()) {
        QString localeName = query.value(0).toString();
        int employeeCount = query.value(1).toInt();
        *set << employeeCount;
        categories << localeName;
        if (employeeCount > maxEmployees) {
            maxEmployees = employeeCount;
        }
    }

    series->append(set);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, maxEmployees + 10); // Add some padding to the maximum value

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Difference in Number of Employees Between Locales");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(800,600);
    // Display the chart in a new window or a widget in your main window
    chartView->show();
}
void MainWindow::exportlocToExcel()
{
    // Get the file path from the user
    QString filePath = QFileDialog::getSaveFileName(this, "Save as Excel", "", "Excel Files (*.xlsx)");
    if (filePath.isEmpty()) {
        return; // Exit if no file path is specified
    }

    // Initialize Excel application
    QAxObject *excel = new QAxObject("Excel.Application", this);
    excel->setProperty("Visible", true);
    QAxObject *workbooks = excel->querySubObject("Workbooks");
    workbooks->dynamicCall("Add");
    QAxObject *worksheet = excel->querySubObject("ActiveSheet");

    // Set headers
    QStringList headers = {"NUMERO_TELEPHONE", "NOM_LOCALE", "ADRESSE", "CAPACITE_VEHICULE", "NOM_MANAGER_LOCALE", "STATUT", "SERVICE_DISPONIBLE", "NOMBRE_EMPLOYEES", "CIN_EMPLOYEES"};
    for (int i = 0; i < headers.size(); ++i) {
        worksheet->querySubObject("Cells(int,int)", 1, i + 1)->setProperty("Value", headers[i]);
    }

    // Fetch data from the database
    QSqlQuery query("SELECT * FROM locaux");
    int row = 2; // Start from the second row
    while (query.next()) {
        worksheet->querySubObject("Cells(int,int)", row, 1)->setProperty("Value", query.value(0).toInt());
        worksheet->querySubObject("Cells(int,int)", row, 2)->setProperty("Value", query.value(1).toString());
        worksheet->querySubObject("Cells(int,int)", row, 3)->setProperty("Value", query.value(2).toString());
        worksheet->querySubObject("Cells(int,int)", row, 4)->setProperty("Value", query.value(3).toInt());
        worksheet->querySubObject("Cells(int,int)", row, 5)->setProperty("Value", query.value(4).toString());
        worksheet->querySubObject("Cells(int,int)", row, 6)->setProperty("Value", query.value(5).toString());
        worksheet->querySubObject("Cells(int,int)", row, 7)->setProperty("Value", query.value(6).toString());
        worksheet->querySubObject("Cells(int,int)", row, 8)->setProperty("Value", query.value(7).toInt());
        worksheet->querySubObject("Cells(int,int)", row, 9)->setProperty("Value", query.value(8).toInt());
        row++;
    }

    // Save the file
    workbooks->querySubObject("Item(int)", 1)->dynamicCall("SaveAs(const QString&)", filePath);

    // Close Excel
    excel->dynamicCall("Quit()");
    delete excel;
}
void MainWindow::loadlocHistory()
{
    modellochis->setQuery("SELECT action_type, timestamp, details FROM history ORDER BY timestamp DESC");
    modellochis->setHeaderData(0, Qt::Horizontal, "Action");
    modellochis->setHeaderData(1, Qt::Horizontal, "Timestamp");
    modellochis->setHeaderData(2, Qt::Horizontal, "Details");

    ui->tablelochistory->setModel(modellochis);
    ui->tablelochistory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void MainWindow::showMap()
{
    /*// Create a QMapControl widget
    QMapControl *mapControl = new QMapControl(this);

    // Set the map provider (e.g., OpenStreetMap)
    mapControl->setMapProvider(QMapControl::MapProvider::OpenStreetMap);

    // Set the initial position and zoom level
    mapControl->setPosition(QGeoCoordinate(37.7749, -122.4194)); // San Francisco
    mapControl->setZoomLevel(10);

    // Set the map control as the central widget or add it to a layout
    setCentralWidget(mapControl);*/
}


//employees
void MainWindow::sortempTable()
{
    QString triloc=ui->comboBox_emp->currentText();
    int tri;
    if(triloc=="CIN_EMPLOYE")tri=0;
    else if(triloc=="NUMERO_TELEPHONE")tri=6;
    proxyModelemp->sort(tri, Qt::AscendingOrder);
}
void MainWindow::exportToPDFemp() {
    // Open a file dialog to specify the output PDF file location
    QString filePath = QFileDialog::getSaveFileName(this, "Save as PDF", "", "*.pdf");
    if (filePath.isEmpty()) {
        return; // Exit if no file path is specified
    }

    // Add the ".pdf" extension if the user did not provide it
    if (QFileInfo(filePath).suffix().isEmpty()) {
        filePath += ".pdf";
    }

    // Create a QPrinter object to configure the PDF output
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    // Get the size of the printable area
    QSizeF printerSize = printer.pageLayout().paintRect(QPageLayout::Point).size();

    // Get the size of the table view
    QSize tableSize = ui->tableViewloc->size();

    // Calculate the scale factors
    qreal xScale = printerSize.width() / tableSize.width();
    qreal yScale = printerSize.height() / tableSize.height();
    qreal scale = qMin(xScale, yScale); // Maintain aspect ratio

    // Adjust scale to make the table larger
    scale *= 1; // Increase by 50% (adjust as needed)

    // Create a QPainter to draw content on the printer
    QPainter painter(&printer);
    painter.scale(scale, scale);

    // Render the table view onto the printer
    ui->tableView_emp->render(&painter);

    painter.end(); // End the painter

    // Confirm export success
    QMessageBox::information(this, "Export Successful", "The table has been successfully exported to PDF.");
}





























//on pushbutton
void MainWindow::on_pushButtonlocadd_ajouter_clicked()
{
    QString NOM_LOCALE=ui->lineEditLNomlocale->text();
    QString NOM_MANAGER_LOCALE=ui->lineEditLNommanager->text();
    QString SERVICE_DISPONIBLE=ui->lineEditLServices->text();
    QString ADRESSE=ui->lineEditLAdresse->text();
    QString STATUT=ui->comboBoxLStatut->currentText();
    int CAPACITE_VEHICULE=ui->lineEditLCapacitevehicule->text().toInt();
    int NUMERO_TELEPHONE=ui->lineEditLNumerotelephone->text().toInt();
    int NOMBRE_EMPLOYEES=ui->lineEditLNombreemployees->text().toInt();
    int CIN_EMPLOYEES=ui->lineEditLCIN->text().toInt();
    if (NOM_MANAGER_LOCALE.isEmpty() || NOM_LOCALE.isEmpty() || ADRESSE.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }
    else if (CAPACITE_VEHICULE <= 0 || NOMBRE_EMPLOYEES <= 0 || CIN_EMPLOYEES <= 0) {
        QMessageBox::warning(nullptr, "Erreur", "Capacite, nombre des employees, and CIN doivent être des nombres positifs.");
        return;
    }
    else if (NUMERO_TELEPHONE <= 0 || QString::number(NUMERO_TELEPHONE).length() != 8) {
        QMessageBox::warning(this, "Erreur", "Le numéro de téléphone doit être un nombre valide de 8 chiffres.");
        return;
    }
    locaux l(NOM_MANAGER_LOCALE, NOM_LOCALE, SERVICE_DISPONIBLE, ADRESSE, STATUT, CAPACITE_VEHICULE, NUMERO_TELEPHONE, NOMBRE_EMPLOYEES, CIN_EMPLOYEES);
    bool test=l.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("Ajout effectue\n"
                                             "Click Sortir to exit"),QMessageBox::Cancel);
        locaddclearline();
        loadtabloc();
        loadtablocmod();
        loadtablocdel();
        ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("locaux"));
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                              QObject::tr("Ajout Non effectue\n"
                                          "Click Sortir to exit"),QMessageBox::Cancel);
}

void MainWindow::on_loc_addButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("locadd"));
}
void MainWindow::on_pushButtonlocadd_sortir_clicked()
{
    locaddclearline();
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("locaux"));
}


void MainWindow::on_pushButtonhome_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("home"));
}


void MainWindow::on_pushButtonclient_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("client"));
}


void MainWindow::on_pushButtonpartenaire_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("partenaire"));
}


void MainWindow::on_pushButtonemploye_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("employe"));
    loadtabemp();
}


void MainWindow::on_pushButtonservice_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("service"));
    loadtabser();
}


void MainWindow::on_pushButtonvehicule_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("vehicule"));
}


void MainWindow::on_pushButtonlocaux_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("locaux"));
    loadtabloc();
}


void MainWindow::on_pushButton_locdel_sortir_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("locaux"));
}


void MainWindow::on_loc_delButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("locdel"));
    loadtablocdel();
}


void MainWindow::on_pushButton_locdel_supprimer_clicked()
{
    QModelIndexList selectedRows = ui->tableViewlocdel->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un locale à supprimer.");
        return;
    }

    // Get NOM_LOCALE from the selected row
    QModelIndex index = selectedRows.first();
    QString nomLocale = modellocdel->data(modellocdel->index(index.row(), 0)).toString();

    // Confirm deletion
    int ret = QMessageBox::question(this, "Confirmer la suppression",
                                    QString("Êtes-vous sûr de vouloir supprimer ce locale '%1'?").arg(nomLocale),
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::No) return;

    // Attempt deletion using the `supprimer` method in `locaux`
    if (Etmp.supprimer(nomLocale)) {
        loadtabloc();
        loadtablocmod();
        QMessageBox::information(this, "Suppression réussie", "Locale supprimé avec succès.");
        loadtablocdel();  // Reload the table data after deletion
    } else {
        QMessageBox::critical(this, "Échec de la suppression", "Échec de la suppression du locale sélectionné.");
    }
}


void MainWindow::on_pushButton_locmod_sortir_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("locaux"));
    locmodclearline();
}



void MainWindow::on_pushButton_locmod_modifier_clicked()
{
    // Update currentLocal object with new data from input fields
    currentLocal.setNOM_LOCALE(ui->lineEdit_locmod_nomlocale->text());
    currentLocal.setNOM_MANAGER_LOCALE(ui->lineEdit_locmod_nommanager->text());
    currentLocal.setSERVICE_DISPONIBLE(ui->lineEdit_locmod_service->text());
    currentLocal.setADRESSE(ui->lineEdit_locmod_adresse->text());
    currentLocal.setSTATUT(ui->comboBox_locmod->currentText());
    currentLocal.setCAPACITE_VEHICULE(ui->lineEdit_locmod_capacite->text().toInt());
    currentLocal.setNUMERO_TELEPHONE(ui->lineEdit_locmod_numero->text().toInt());
    currentLocal.setNOMBRE_EMPLOYEES(ui->lineEdit_locmod_nombre->text().toInt());
    currentLocal.setCIN_EMPLOYEES(ui->lineEdit_locmod_cin->text().toInt());

    QString NOM_LOCALE=ui->lineEdit_locmod_nomlocale->text();
    QString NOM_MANAGER_LOCALE=ui->lineEdit_locmod_nommanager->text();
    QString SERVICE_DISPONIBLE=ui->lineEdit_locmod_service->text();
    QString ADRESSE=ui->lineEdit_locmod_adresse->text();
    QString STATUT=ui->comboBox_locmod->currentText();
    int CAPACITE_VEHICULE=ui->lineEdit_locmod_capacite->text().toInt();
    int NUMERO_TELEPHONE=ui->lineEdit_locmod_numero->text().toInt();
    int NOMBRE_EMPLOYEES=ui->lineEdit_locmod_nombre->text().toInt();
    int CIN_EMPLOYEES=ui->lineEdit_locmod_cin->text().toInt();
    if (NOM_MANAGER_LOCALE.isEmpty() || NOM_LOCALE.isEmpty() || ADRESSE.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }
    else if (CAPACITE_VEHICULE <= 0 || NOMBRE_EMPLOYEES <= 0 || CIN_EMPLOYEES <= 0) {
        QMessageBox::warning(nullptr, "Erreur", "Capacite, nombre des employees, and CIN doivent être des nombres positifs.");
        return;
    }
    else if (NUMERO_TELEPHONE <= 0 || QString::number(NUMERO_TELEPHONE).length() != 8) {
        QMessageBox::warning(this, "Erreur", "Le numéro de téléphone doit être un nombre valide de 8 chiffres.");
        return;
    }
    // Update the record in the database
    if (currentLocal.modifier()) {
        loadtabloc();
        loadtablocmod();
        loadtablocdel();
        ui->tableViewlocmod->setModel(modellocmod);
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("Modifier effectue\n"
                                             "Click Sortir to exit"),QMessageBox::Cancel);
        locmodclearline();
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                              QObject::tr("Modifier Non effectue\n"
                                          "Click Sortir to exit"),QMessageBox::Cancel);
}


void MainWindow::on_loc_modButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("locmod"));
    loadtablocmod();
}


void MainWindow::on_pushButton_loctri_clicked()
{
    sortlocTable();
}


void MainWindow::on_pushButton_locPDF_clicked()
{
    exportToPDF();
}


void MainWindow::on_pushButton_locrecherche_clicked()
{
    loadtabloc();
    QString nomentre=ui->comboBox_locrecherche->currentText();
    int i;
    if(nomentre=="Nom_locale")i=1;
    else if(nomentre=="Nom_manager")i=4;
    else if(nomentre=="Adresse")i=2;
    searchNomLocale(i);
    ui->lineEdit_locrecherche->clear();
}





void MainWindow::on_pushButton_locstat_clicked()
{
    showEmployeeChartloc();
}


void MainWindow::on_pushButton_locexel_clicked()
{
    exportlocToExcel();
}


void MainWindow::on_pushButton_lochistory_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("lochistory"));
    loadlocHistory();
}


void MainWindow::on_pushButton_lochis_sortir_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("locaux"));
}


void MainWindow::on_pushButton_maps_clicked()
{
    showMap();
}








//employe

void MainWindow::on_pushButton_emp_ajouter_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("addemp"));
}


void MainWindow::on_pushButton_emp_modifier_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("modemp"));
}


void MainWindow::on_pushButton_emp_tri_clicked()
{
    sortempTable();
}



void MainWindow::on_pushButton_empajoutersortir_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("employe"));
}


void MainWindow::on_pushButton_empmodsortir_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("employe"));
}


void MainWindow::on_pushButton_emp_edit_clicked()
{
    QModelIndexList selectedRows = ui->tableView_emp->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "No Selection", "Please select a row to delete.");
        return;
    }

    int row = selectedRows.first().row();
    QAbstractItemModel *modelemp = ui->tableView_emp->model();

    int CIN_EMPLOYEES = modelemp->data(modelemp->index(row, 0)).toInt();
    QString NOM_EMP = modelemp->data(modelemp->index(row, 1)).toString();
    QString PRENOM_EMP = modelemp->data(modelemp->index(row, 2)).toString();
    QDate DATE_NS_EMP = modelemp->data(modelemp->index(row, 4)).toDate();
    QString ADRESSE_EMP = modelemp->data(modelemp->index(row, 5)).toString();
    QString EMAIL_EMP = modelemp->data(modelemp->index(row, 3)).toString();
    QString NUM_TEL_EMP = modelemp->data(modelemp->index(row, 6)).toString();
    QString POSTE_EMP = modelemp->data(modelemp->index(row, 7)).toString();
    QString MDP_EMP = modelemp->data(modelemp->index(row, 9)).toString();
    QString SEX_EMP = modelemp->data(modelemp->index(row, 8)).toString();


    ui->lineEditempmodcin->setText(QString::number(CIN_EMPLOYEES));
    ui->lineEditempmodnom->setText(NOM_EMP);
    ui->lineEditempmodprenom->setText(PRENOM_EMP);
    ui->dateEditempmod->setDate(DATE_NS_EMP);
    ui->lineEditempmodadresse->setText(ADRESSE_EMP);
    ui->lineEditempmodemail->setText(EMAIL_EMP);
    ui->lineEditempmodnum->setText(NUM_TEL_EMP);
    ui->lineEditempmodposte->setText(POSTE_EMP);
    ui->lineEditempmodmdp->setText(MDP_EMP);
    ui->comboBoxempmod->setCurrentText(SEX_EMP);
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("modemp"));
}






void MainWindow::on_pushButtonempaddajouter_clicked()
{
    // Récupérer les données des QLineEdit
    QString cinText = ui->lineEditempaddcin->text();
    QString NOM_EMP = ui->lineEditempaddnom->text();
    QString PRENOM_EMP = ui->lineEditempaddprenom->text();
    QDate DATE_NS_EMP = ui->dateEditempadd->date();
    QString ADRESSE_EMP = ui->lineEditempaddadresse->text();
    QString EMAIL_EMP = ui->lineEditempaddemail->text();
    QString NUM_TEL_EMP = ui->lineEditempaddnum->text();
    QString POSTE_EMP = ui->lineEditempaddposte->text();
    QString MDP_EMP = ui->lineEditempaddmdp->text();
    QString SEX_EMP = ui->comboBoxempadd->currentText();

    // Contrôle du CIN (8 chiffres)
    QRegularExpression cinRegex("^\\d{8}$");
    if (!cinRegex.match(cinText).hasMatch()) {
        QMessageBox::warning(this, "Erreur de saisie", "Le CIN doit contenir exactement 8 chiffres.");
        return;
    }

    // Contrôle de l'email (format valide)
    QRegularExpression emailRegex("^[\\w\\.-]+@[\\w\\.-]+\\.[a-zA-Z]{2,}$");
    if (!emailRegex.match(EMAIL_EMP).hasMatch()) {
        QMessageBox::warning(this, "Erreur de saisie", "L'adresse email n'est pas valide.");
        return;
    }

    // Contrôle des autres champs (non vides)
    if (NOM_EMP.isEmpty() || PRENOM_EMP.isEmpty() || ADRESSE_EMP.isEmpty() || NUM_TEL_EMP.isEmpty() || POSTE_EMP.isEmpty() || MDP_EMP.isEmpty() || SEX_EMP.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    // Contrôle de la longueur du mot de passe (au moins 6 caractères)
    if (MDP_EMP.length() < 6) {
        QMessageBox::warning(this, "Erreur de saisie", "Le mot de passe doit contenir au moins 6 caractères.");
        return;
    }

    // Contrôle du numéro de téléphone (chiffres uniquement, par exemple 10 chiffres)
    QRegularExpression phoneRegex("^\\d{8,10}$");
    if (!phoneRegex.match(NUM_TEL_EMP).hasMatch()) {
        QMessageBox::warning(this, "Erreur de saisie", "Le numéro de téléphone doit contenir entre 8 et 10 chiffres.");
        return;
    }

    // Contrôle de la date de naissance (optionnel, exemple : l'utilisateur doit avoir au moins 18 ans)
    if (DATE_NS_EMP > QDate::currentDate().addYears(-18)) {
        QMessageBox::warning(this, "Erreur de saisie", "L'employé doit avoir au moins 18 ans.");
        return;
    }

    // Tous les contrôles sont passés
    QMessageBox::information(this, "Succès", "Les données saisies sont valides.");


    Employees E(cinText.toInt(), NOM_EMP, PRENOM_EMP, SEX_EMP, DATE_NS_EMP, ADRESSE_EMP, EMAIL_EMP, NUM_TEL_EMP, POSTE_EMP, MDP_EMP);
    bool ajout = E.ajouter();
    if (ajout) {
        loadtabemp();

        QMessageBox::information(this, "Succès", "L'employé a été ajouté avec succès.");
        // Nettoyage des champs après l'ajout

    } else {
        QMessageBox::critical(this, "Erreur", "L'ajout de l'employé a échoué.");
        qDebug() << "Erreur SQL:" << QSqlDatabase::database().lastError().text();
    }

    if (ajout) {
        QMessageBox::information(this, "Succès", "L'employé a été ajouté avec succès.");
        ui->lineEditempaddcin->clear();
        ui->lineEditempaddnom->clear();
        ui->lineEditempaddprenom->clear();
        ui->dateEditempadd->clear();
        ui->lineEditempaddadresse->clear();
        ui->lineEditempaddemail->clear();
        ui->lineEditempaddnum->clear();
        ui->lineEditempaddposte->clear();
        ui->lineEditempaddmdp->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "L'ajout de l'employé a échoué.");
    }

}


void MainWindow::on_pushButton_emp_delete_clicked()
{
    QModelIndexList selectedRows = ui->tableView_emp->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "No Selection", "Please select a row to delete.");
        return;
    }

    int row = selectedRows.first().row();
    int CIN_EMPLOYEES = ui->tableView_emp->model()->index(row, 0).data().toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete this employee?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) return;
    else{
    Employees E;
    bool success = E.supprimer(CIN_EMPLOYEES);
    if (success) {
        QMessageBox::information(this, "Success", "Employee deleted successfully.");
        loadtabemp();
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete employee.");
    }}
}


void MainWindow::on_pushButton_empmodmod_clicked()
{
    int CIN_EMPLOYEES = ui->lineEditempmodcin->text().toInt();
    QString NOM_EMP = ui->lineEditempmodnom->text();
    QString PRENOM_EMP = ui->lineEditempmodprenom->text();
    QDate DATE_NS_EMP = ui->dateEditempmod->date();
    QString ADRESSE_EMP = ui->lineEditempmodadresse->text();
    QString EMAIL_EMP = ui->lineEditempmodemail->text();
    QString NUM_TEL_EMP = ui->lineEditempmodnum->text();
    QString POSTE_EMP = ui->lineEditempmodposte->text();
    QString MDP_EMP = ui->lineEditempmodmdp->text();
    QString SEX_EMP = ui->comboBoxempmod->currentText();


    if (CIN_EMPLOYEES == 0 || NOM_EMP.isEmpty() || PRENOM_EMP.isEmpty() || SEX_EMP.isEmpty() || ADRESSE_EMP.isEmpty() || EMAIL_EMP.isEmpty() || NUM_TEL_EMP.isEmpty() || POSTE_EMP.isEmpty() || MDP_EMP.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs.");
        return;
    }

    Employees E(CIN_EMPLOYEES, NOM_EMP, PRENOM_EMP, SEX_EMP, DATE_NS_EMP, ADRESSE_EMP, EMAIL_EMP, NUM_TEL_EMP, POSTE_EMP, MDP_EMP);
    bool edit = E.modifier();
    if (edit) {
        loadtabemp();
        QMessageBox::information(this, "Succès", "L'employé a été modifié avec succès.");
        ui->lineEditempmodcin->clear();
        ui->lineEditempmodnom->clear();
        ui->lineEditempmodprenom->clear();
        ui->dateEditempmod->clear();
        ui->lineEditempmodadresse->clear();
        ui->lineEditempmodemail->clear();
        ui->lineEditempmodnum->clear();
        ui->lineEditempmodmdp->clear();
        ui->lineEditempmodposte->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "La modification de l'employé a échoué.");
    }
}

void MainWindow::on_researchcinemp_textChanged(const QString &arg1)
{
    Employees e;
    if(arg1.toInt()){
        ui->tableView_emp->setModel(e.search(arg1.toInt()));}
    else if(arg1.isEmpty()){
        ui->tableView_emp->setModel(e.afficher());}


    else{
        QMessageBox::information(nullptr, QObject::tr("Not OK"), QObject::tr("Inserer une valeur nemurique"), QMessageBox::Cancel);

    }
}

void MainWindow::on_pushButton__pdf_clicked()
{
    exportToPDFemp();
}


void MainWindow::on_pushButtonstatempsortir_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("employe"));
}


void MainWindow::on_pushButton_emp_stat_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("statemp"));
    Employees emp;
    QMap<QString, int> stats = emp.statistiquesParSexe();

    QPieSeries *series = new QPieSeries();
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        series->append(it.key(), it.value());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des Employées par Sex");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(881, 431);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addWidget(chartView);
    ui->graphicsView->setScene(scene);
}


//service


void MainWindow::on_pushButtonserviceavancesortir_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("service"));
    loadtabser();
}


void MainWindow::on_pushButtonservicetool_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("serviceadvanced"));
    loadtabsertools();
}


void MainWindow::on_pushButton_serajouter_clicked()
{
    QString id_service = ui->lineEditserid->text();
    QString Nom_Employe = ui->lineEditsernom->text();
    QString Date_entrée = ui->dateEditsersortir->date().toString("dd-MM-yyyy");
    QString Date_sortie = ui->dateEditserentree->date().toString("dd-MM-yyyy");
    QString Etat_service = ui->comboBoxser->currentText();  // Get the value from the ComboBox

    // Check if all fields are filled
    if (id_service.isEmpty() || Nom_Employe.isEmpty() || Date_entrée.isEmpty() || Date_sortie.isEmpty() || Etat_service.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs.");
        return;
    }
    // ID validation: Check if ID format is correct (e.g., XXX_123)
    if (id_service.length() < 5 || id_service[3] != '_') {
        QMessageBox::warning(this, "Format invalide", "L'ID de service doit être de la forme XXX_123 (3 lettres majuscules, un underscore et des chiffres).");
        return;
    }
    for (int i = 0; i < 3; ++i) {
        if (!id_service[i].isUpper()) {
            QMessageBox::warning(this, "Format invalide", "Les 3 premiers caractères de l'ID doivent être des lettres majuscules.");
            return;
        }
    }
    for (int i = 4; i < id_service.length(); ++i) {
        if (!id_service[i].isDigit()) {
            QMessageBox::warning(this, "Format invalide", "L'ID doit se terminer par des chiffres après l'underscore.");
            return;
        }
    }

    // Name validation: Ensure the name contains only alphabetic characters (no numbers or special characters)
    QRegularExpression namePattern("^[A-Za-z]+$");  // Regular expression for alphabetic characters
    QRegularExpressionMatch match = namePattern.match(Nom_Employe);
    if (!match.hasMatch()) {
        QMessageBox::warning(this, "Nom invalide", "Le nom de l'employé doit uniquement contenir des lettres.");
        return;
    }

    // Date validation: Ensure the end date is later than the start date
    QDate startDate = ui->dateEditserentree->date();
    QDate endDate = ui->dateEditsersortir->date();
    if (endDate < startDate) {
        QMessageBox::warning(this, "Date invalide", "La date de sortie doit être postérieure à la date d'entrée.");
        return;
    }


    // ComboBox validation: Ensure that the ComboBox item is selected
    if (ui->comboBoxser->currentIndex() == -1) {
        QMessageBox::warning(this, "Sélection invalide", "Veuillez sélectionner un état de service.");
        return;
    }

    // Service object creation
    service E(id_service, Nom_Employe, Date_entrée, Date_sortie, Etat_service);

    // Check if the service ID is unique
    if (!E.isIdServiceUnique(id_service)) {
        QMessageBox::warning(this, "Erreur", "L'ID de service existe déjà.");
        return;
    } else {
        // Add the service if the validation passes
        if (E.ajouter()) {
            QMessageBox::information(this, "Succès", "L'ajout des informations est effectué.");
            loadtabser();  // Reload the list after adding the new service
        } else {
            QMessageBox::warning(this, "Erreur", "L'ajout n'a pas été effectué.");
        }

        // Clear the fields
        ui->lineEditserid->clear();
        ui->lineEditsernom->clear();
        ui->comboBoxser->setCurrentIndex(0);  // Reset the combo box to the first item
        ui->tableViewser->setModel(E.afficher());  // Update the view with the new list of services
    }
}


void MainWindow::on_tableViewser_clicked(const QModelIndex &index1)
{
    if (index1.isValid()) {
        // Only process the ID_SERVICE column (assuming it's the first column, index 0)
        if (index1.column() == 0) {  // column 0 is assumed to be ID_SERVICE
            // Get the data from the clicked cell (ID_SERVICE)
            QString idService = index1.data().toString();

            // Set the ID_SERVICE into the lineEdit_9
            ui->lineEditserid->setText(idService);
        }
    }
}




void MainWindow::on_pushButtonsermodif_clicked()
{
    QString id_service = ui->lineEditserid->text();
    QString Nom_Employe = ui->lineEditsernom->text();
    QString Date_entrée = ui->dateEditsersortir->date().toString("dd-MM-yyyy");
    QString Date_sortie = ui->dateEditserentree->date().toString("dd-MM-yyyy");
    QString Etat_service = ui->comboBoxser->currentText();

    // Step 1: Validate input fields with detailed messages
    if (id_service.isEmpty() || Nom_Employe.isEmpty() || Date_entrée.isEmpty() || Date_sortie.isEmpty() || Etat_service.isEmpty()) {
        QMessageBox::warning(this, "Champs Manquants", "Veuillez remplir tous les champs avant de continuer.");
        return;
    }

    if (id_service.length() < 5 || id_service[3] != '_') {
        QMessageBox::warning(this, "Format d'ID de Service Invalide", "L'ID doit être de la forme XXX_123 (3 lettres majuscules, un underscore et des chiffres).");
        return;
    }

    for (int i = 0; i < 3; ++i) {
        if (!id_service[i].isUpper()) {
            QMessageBox::warning(this, "Format d'ID de Service Invalide", "Les 3 premiers caractères de l'ID doivent être des lettres majuscules.");
            return;
        }
    }
    for (int i = 4; i < id_service.length(); ++i) {
        if (!id_service[i].isDigit()) {
            QMessageBox::warning(this, "Format d'ID de Service Invalide", "L'ID doit se terminer par des chiffres après l'underscore.");
            return;
        }
    }

    // Step 2: Confirm update action with user
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmer la Modification", "Êtes-vous sûr de vouloir modifier les informations du service ?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
        return;
    }


    // Step 3: Create service object and update details
    service E(id_service, Nom_Employe, Date_entrée, Date_sortie, Etat_service);
    bool updateSuccess = E.updateServiceDetails(id_service);

    // Step 4: Show success or failure message and update the UI
    if (updateSuccess) {
        QMessageBox::information(this, "Succès", "Les détails du service ont été mis à jour avec succès.");

        // Clear input fields after successful update
        ui->lineEditserid->clear();
        ui->lineEditsernom->clear();
        ui->dateEditserentree->clear();
        ui->dateEditsersortir->clear();
        ui->comboBoxser->setCurrentIndex(0);

        // Refresh table view to reflect updated data

        loadtabser();

    } else {
        QMessageBox::warning(this, "Erreur", "Une erreur est survenue lors de la mise à jour des informations du service.");
    }
}


void MainWindow::on_pushButtonsersup_clicked()
{
    // Get the selected index from the table view
    QModelIndex index = ui->tableViewser->currentIndex();

    if (index.isValid()) {
        // Get the service ID from the selected row (assuming the ID is in the first column)
        QString id_service = ui->tableViewser->model()->data(ui->tableViewser->model()->index(index.row(), 0)).toString();

        if (id_service.isEmpty()) {
            QMessageBox::warning(this, "Champs manquants", "Veuillez entrer l'ID du service à supprimer.");
            return;
        }

        // Confirm deletion
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Êtes-vous sûr de vouloir supprimer ce service ?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            service E;  // Create service object

            // Call the supprimer function from your service class
            bool success = E.supprimer(id_service);

            if (success) {
                // If deletion is successful, remove the row from the model
                QAbstractItemModel *model = ui->tableViewser->model();
                model->removeRow(index.row());

                // Optionally, if needed, you can reset the model to ensure proper refresh
                ui->tableViewser->setModel(E.afficher());
                ui->tableViewser->reset(); // Use this if necessary

                // Show success message
                QMessageBox::information(this, "Succès", "Le service a été supprimé avec succès.");
            } else {
                // Show error message if deletion fails
                QMessageBox::warning(this, "Erreur", "Une erreur est survenue lors de la suppression.");
            }
        }
    } else {
        // If no row is selected, show a warning
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un service à supprimer.");
    }
}


void MainWindow::on_pushButtonserrecherche_clicked()
{
    service E;
    QString searchid = ui->lineEditserrecherche->text();


    if (searchid.isEmpty()) {
        loadtabsertools();
    }


    QSqlQueryModel* model = E.search(searchid);

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "No Results", "No services found matching the search criteria.");
        return;
    }


    ui->tableViewsertools->setModel(model);

    bool itemFound = false;


    for (int row = 0; row < model->rowCount(); ++row) {
        QString id_service = model->data(model->index(row, 0)).toString(); // Get the `id_service` value from the first column


        if (id_service.contains(searchid, Qt::CaseInsensitive)) {

            itemFound = true;
            break;  // Exit the loop once we find the matching item
        }
    }


    if (itemFound) {
        QMessageBox::information(this, "Item Found", "The item was found and has been added to the first row.");
        ui->lineEditserrecherche->clear();
    } else {
        QMessageBox::information(this, "Item Not Found", "No matching item was found.");
    }
}


void MainWindow::on_pushButtonserpdf_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Save PDF",
                                                    "",
                                                    "PDF files (*.pdf);;All Files (*)");

    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Save PDF", "No file path specified.");
        return;
    }

    // Ensure file path ends with .pdf
    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
        filePath += ".pdf";
    }

    service s;
    // Generate PDFs for both table views
    bool pdfCreated1 = s.generatePDF(filePath, ui->tableViewser);
    bool pdfCreated2 = s.generatePDF(filePath, ui->tableViewsertools);

    if (pdfCreated1 || pdfCreated2) {
        QMessageBox::information(this, "PDF Saved", "PDF file has been saved successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to create PDF.");
    }
}



void MainWindow::on_pushButtonserexel_clicked()
{
    service s;
    if (s.generateExcel(ui->tableViewser)) {
        QMessageBox::information(this, "Excel Export", "Excel file exported successfully.");
    } else {
        QMessageBox::warning(this, "Excel Export", "Failed to export Excel file.");
    }
}


void MainWindow::on_pushButtontridate_clicked()
{
    service E;
    // Sort by Date_entrée and display it in the table view
    ui->tableViewsertools->setModel(E.sortByDateEntree());
}


void MainWindow::on_pushButtonsertrinom_clicked()
{
    service E;
    // Sort by Date_entrée and display it in the table view
    ui->tableViewsertools->setModel(E.sortByName());
}


void MainWindow::on_pushButtonserstatsortir_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("serviceadvanced"));
}


void MainWindow::on_pushButtonserstat_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("serstat"));
    setupStatisticsPage();
}

void MainWindow::setupStatisticsPage()
{
    qDebug() << "Setting up statistics page";

    if (!ui->diagrme) {
        qDebug() << "Error: ui->diagrme is null!";
        return;
    }

    // Prepare and execute the SQL query
    QSqlQuery query;
    query.prepare("SELECT Etat_service, COUNT(*) FROM service GROUP BY Etat_service");

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    // Variables to store data
    QMap<QString, int> statusCounts;
    int totalServices = 0;

    // Process the query results
    while (query.next()) {
        QString status = query.value(0).toString();
        int count = query.value(1).toInt();

        statusCounts[status] = count;
        totalServices += count;
    }

    // Create a pie series
    QPieSeries *series = new QPieSeries();

    // Add data to the pie series
    for (auto it = statusCounts.begin(); it != statusCounts.end(); ++it) {
        double percentage = (static_cast<double>(it.value()) / totalServices) * 100;
        QPieSlice *slice = series->append(it.key(), percentage);

        // Customize slice appearance
        slice->setLabel(QString("%1: %2%").arg(it.key()).arg(percentage, 0, 'f', 1));
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelOutside);

        // Random color generation
        int hue = QRandomGenerator::global()->bounded(360);
        QColor sliceColor = QColor::fromHsv(hue, 255, 200);

        // Apply a radial gradient
        QRadialGradient gradient(0.5, 0.5, 0.8);
        gradient.setColorAt(0, sliceColor.darker(150));
        gradient.setColorAt(1, sliceColor);
        slice->setBrush(gradient);
    }

    // Create and configure the chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des services par état");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Add the chart to the `diagrme` widget
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Clear existing layout if present
    if (ui->diagrme->layout()) {
        QLayoutItem *child;
        while ((child = ui->diagrme->layout()->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
    }

    // Set a new layout if needed and add the chart view
    if (!ui->diagrme->layout()) {
        QVBoxLayout *layout = new QVBoxLayout(ui->diagrme);
        ui->diagrme->setLayout(layout);
    }
    ui->diagrme->layout()->addWidget(chartView);
}

void MainWindow::on_pushButtontodosortir_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("serviceadvanced"));
}


void MainWindow::on_pushButtonsertodo_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("sertodo"));
    QString currentTime = getCurrentDateTime();

    // Show current time in a QMessageBox
    QMessageBox::information(this, "Current System Time", "The current date and time is:\n" + currentTime);
}

QString MainWindow::getCurrentDateTime() {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    return currentDateTime.toString("yyyy-MM-dd HH:mm:ss"); // Format the date and time
}



void MainWindow::on_pushButtontodoajouter_clicked()
{
    QString id_service = ui->lineEdittodoid->text();  // QLineEdit for ID_SERVICE
    QString client = ui->lineEdittodonom->text();  // QLineEdit for Client
    QString modele = ui->lineEdittodomodel->text();  // QLineEdit for Modele
    QString service = ui->comboBoxtodoservice->currentText();  // QLineEdit for Service
    QDate date = ui->dateEdittodo->date();  // QDateEdit for Date
    QString prix = ui->comboBoxtodopriorite->currentText();  // QComboBox for Priority

    // Get the progress value from the QProgressBar
    int prog = ui->progressBartodo->value();  // Use QProgressBar value
    // Check if the ID_SERVICE exists in the SERVICE table
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM SERVICE WHERE ID_SERVICE = :id_service");
    query.bindValue(":id_service", id_service);
    if (!query.exec() || !query.next() || query.value(0).toInt() == 0) {
        QMessageBox::warning(this, "Error", "Invalid ID_SERVICE. Please enter a valid service ID.");
        return;
    }

    // Create the task object with the data
    task newTask(id_service, client, modele, service, date, prix, prog);

    // Try to add the task to the database
    if (newTask.ajouterTask()) {
        QMessageBox::information(this, "Task Added", "The task was added successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to add the task. Please check your input.");
    }
}


void MainWindow::on_tableViewtodo_clicked(const QModelIndex &index)
{
    // Assuming the first column contains the ID_SERVICE
    QString id_service = ui->tableViewtodo->model()->data(index.siblingAtColumn(0)).toString();

    // Assuming the fourth column contains Priority and fifth contains Progress
    QString priority = ui->tableViewtodo->model()->data(index.siblingAtColumn(4)).toString();
    int progress = ui->tableViewtodo->model()->data(index.siblingAtColumn(5)).toInt();

    // Populate the input fields
    ui->lineEdittodoid->setText(id_service);
    ui->comboBoxtodopriorite->setCurrentText(priority);
    ui->progressBartodo->setValue(progress);
}


void MainWindow::on_pushButtontodoafficher_clicked()
{
    // Create the task object
    task t;

    // Get the model returned by afficher() method
    QSqlQueryModel *model = t.afficher();  // Assuming this method returns a valid model

    // Set the model to the table view
    ui->tableViewtodo->setModel(model);

    // Create and set the custom delegate to highlight the rows
    /*DateHighlightDelegate *delegate = new DateHighlightDelegate(this);
    ui->tableViewtodo->setItemDelegate(delegate);
*/
    // Refresh the table view to ensure the delegate is applied
    ui->tableViewtodo->update();

    // Now check the tasks and notify if any task is for today
    QSqlQuery query;
    query.prepare("SELECT ID_SERVICE, DATE_TASK FROM TASK");
    if (query.exec()) {
        while (query.next()) {
            QString id_service = query.value(0).toString();  // Get service ID
            QString dateString = query.value(1).toString();  // Get the task date string

            // Convert the date string to QDate
            QDate dateFromDb = QDate::fromString(dateString, "dd-MM-yyyy");

            // Get current date
            QDate currentDate = QDate::currentDate();

            // If the task date matches the current date, show a message box
            if (dateFromDb.isValid() && dateFromDb == currentDate) {
                QMessageBox::information(this, "Task Due Today",
                                         "You have a task to be done today. Service ID: " + id_service);
            }
        }
    } else {
        qDebug() << "Error querying tasks: " << query.lastError().text();
    }
}


void MainWindow::on_pushButtontodosup_clicked()
{
    // Get the selected index from the table view
    QModelIndex index = ui->tableViewtodo->currentIndex();

    if (index.isValid()) {
        // Get the service ID from the selected row (assuming the ID is in the first column)
        QString id_service = ui->tableViewtodo->model()->data(ui->tableViewtodo->model()->index(index.row(), 0)).toString();

        if (id_service.isEmpty()) {
            QMessageBox::warning(this, "Champs manquants", "Veuillez entrer l'ID du service à supprimer.");
            return;
        }

        // Confirm deletion
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Êtes-vous sûr de vouloir supprimer ce service ?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            task E;  // Create service object

            // Call the supprimer function from your service class
            bool success = E.supprimerTask(id_service);

            if (success) {
                // If deletion is successful, remove the row from the model
                QAbstractItemModel *model = ui->tableViewtodo->model();
                model->removeRow(index.row());

                // Optionally, if needed, you can reset the model to ensure proper refresh
                ui->tableViewtodo->setModel(E.afficher());
                ui->tableViewtodo->reset(); // Use this if necessary

                // Show success message
                QMessageBox::information(this, "Succès", "Le service a été supprimé avec succès.");
            } else {
                // Show error message if deletion fails
                QMessageBox::warning(this, "Erreur", "Une erreur est survenue lors de la suppression.");
            }
        }
    } else {
        // If no row is selected, show a warning
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un service à supprimer.");
    }
}


void MainWindow::on_pushButtonserphototelecharger_clicked()
{
    // Open file dialog to select an image
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp *.jpeg)");

    if (fileName.isEmpty()) {
        return; // No file selected, exit
    }

    // Check if the file is in the allowed directory
    QString allowedPath = "C:/Users/USER/Desktop/service_image";
    QFileInfo fileInfo(fileName);
    QString fileDir = fileInfo.absolutePath();

    if (fileDir != allowedPath) {
        QMessageBox::warning(this, "Invalid Upload", "This image cannot be uploaded because it is not from our data base and is not realted to the car items or any other suggestion vehicule item .");
        return; // Exit if the file is not in the allowed directory
    }

    // Read the image file into QByteArray
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open image file:" << fileName;
        return; // Failed to open file
    }
    QByteArray imageData = file.readAll();
    file.close();

    // Retrieve the service ID from the line edit
    QString id_service = ui->lineEditserphotoid->text();
    if (id_service.isEmpty()) {
        QMessageBox::warning(this, "Missing Service ID", "Please provide a valid Service ID.");
        return; // Ensure the ID is not empty
    }

    // Upload image to database
    service serviceObj; // Assuming `service` is the class handling your database
    if (!serviceObj.uploadImage(id_service, imageData)) {
        QMessageBox::critical(this, "Upload Failed", "Failed to upload image to database.");
        return; // Image upload failed
    }

    QMessageBox::information(this, "Success", "Image uploaded successfully to the database.");
    loadtabser(); // Optionally refresh the UI
}
bool service::uploadImage(const QString &id_service, const QByteArray &imageData)
{
    if (imageData.isEmpty()) {
        qDebug() << "Image data is empty. Cannot upload.";
        return false; // Image data must not be empty
    }

    // Prepare SQL query to update the image in the database
    QSqlQuery query;
    query.prepare("UPDATE SERVICE SET image = :imageData WHERE ID_SERVICE = :id");
    query.bindValue(":imageData", imageData);
    query.bindValue(":id", id_service);

    // Execute the query and handle any errors
    if (!query.exec()) {
        qDebug() << "Failed to update image in database:" << query.lastError().text();
        return false; // Query execution failed
    }

    return true; // Successfully uploaded image
}

void MainWindow::on_pushButtonserphotoafficher_clicked()
{
    QString id_service = ui->lineEditserphotoid->text();
    if (id_service.isEmpty()) {
        qDebug() << "Service ID is empty. Please provide a valid ID.";
        return; // Ensure the ID is not empty
    }

    // Prepare SQL query to retrieve image data based on the service ID
    QSqlQuery query;
    query.prepare("SELECT image FROM SERVICE WHERE ID_SERVICE = :id");
    query.bindValue(":id", id_service);

    // Execute the query and handle errors
    if (!query.exec()) {
        qDebug() << "Failed to retrieve image data from database:" << query.lastError().text();
        return; // Query execution failed
    }

    // Check if the query returned any data
    if (!query.next()) {
        qDebug() << "No image found for the given service ID.";
        return; // No image found for the provided ID
    }

    // Retrieve the image data from the query result
    QByteArray imageData = query.value("image").toByteArray();

    // Load the image from the data
    QPixmap pixmap;
    if (!pixmap.loadFromData(imageData)) {
        qDebug() << "Failed to load image from database data.";
        return; // Failed to load the image
    }

    // Display the image in the QTableView
    displayImageInTable(pixmap);
}
void MainWindow::displayImageInTable(const QPixmap &pixmap)
{
    // Ensure the widget (where the image will be displayed) exists
    if (!ui->widgetph) {
        qDebug() << "Widget not found!";
        return;
    }

    // Create or find the QLabel where the image will be displayed
    QLabel *imageLabel = ui->widgetph->findChild<QLabel*>("imageLabel");

    // If no QLabel exists, create one
    if (!imageLabel) {
        imageLabel = new QLabel(ui->widgetph);
        imageLabel->setObjectName("imageLabel"); // Assign an object name for future references
        imageLabel->setAlignment(Qt::AlignCenter);
        imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored); // Ensure it resizes with the widget
    }

    // Set the pixmap to the QLabel
    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true); // Ensure the image scales to fit the label's size
}


void MainWindow::on_pushButtonserphotopropose_clicked()
{
    QString id_service = ui->lineEditserphotoid->text();  // Get the ID_SERVICE input
    if (id_service.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a valid ID_SERVICE.");
        return;
    }

    // Fetch the SERVICE type from the TASK table using ID_SERVICE
    QSqlQuery query;
    query.prepare("SELECT SERVICE FROM TASK WHERE ID_SERVICE = :id_service");
    query.bindValue(":id_service", id_service);

    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Error", "No task found for the given ID_SERVICE.");
        return;
    }

    QString serviceType = query.value("SERVICE").toString();

    // Map the SERVICE type to predefined image file paths
    QMap<QString, QStringList> serviceToImages = {
        {"Vidange", {"C:/Users/USER/Desktop/service_image/vidange1.png",
                     "C:/Users/USER/Desktop/service_image/vidange.png"}},
        {"Chagement d'huile", {"C:/Users/USER/Desktop/service_image/oil change1.png",
                        "C:/Users/USER/Desktop/service_image/oil change.png"}},
        {"Diagnostique", {"C:/Users/USER/Desktop/service_image/diag1.png",
                          "C:/Users/USER/Desktop/service_image/diag.png"}},
        {"Verification_du_batterie", {"C:/Users/USER/Desktop/service_image/bateery1.png",
                           "C:/Users/USER/Desktop/service_image/batery.png"}},
        {"Verification_du_moteur", {"C:/Users/USER/Desktop/service_image/engine1.png",
                          "C:/Users/USER/Desktop/service_image/engine.png"}}
    };

    // Check if predefined images exist for the service type
    if (!serviceToImages.contains(serviceType)) {
        QMessageBox::warning(this, "Error", "No predefined images found for this service type.");
        return;
    }

    QStringList imagePaths = serviceToImages[serviceType];

    // Load the first image and display it in label_20
    QPixmap pixmap1(imagePaths[0]);
    if (pixmap1.isNull()) {
        QMessageBox::warning(this, "Error", "Failed to load the first image.");
    } else {
        ui->label_61->setPixmap(pixmap1.scaled(ui->label_61->size(), Qt::KeepAspectRatio));
    }

    // Load the second image and display it in label_21
    QPixmap pixmap2(imagePaths[1]);
    if (pixmap2.isNull()) {
        QMessageBox::warning(this, "Error", "Failed to load the second image.");
    } else {
        ui->label_62->setPixmap(pixmap2.scaled(ui->label_62->size(), Qt::KeepAspectRatio));
    }
}



void MainWindow::on_pushButtonserphoto_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("serphoto"));
}


void MainWindow::on_pushButtonserphotosortir_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("serviceadvanced"));
}


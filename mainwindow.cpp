#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "locaux.h"
#include <QStackedWidget>
#include <QMessageBox>
#include <QObject>
#include <QTableView>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlQuery>
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

{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<QWidget*>("employe"));
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
    loadtabemp();

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


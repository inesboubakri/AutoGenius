
#include "mainwindow.h"
#include "qpushbutton.h"
#include "qsqlerror.h"
#include "qsqltablemodel.h"
#include "service.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QRegularExpression>
#include <QRandomGenerator>
#include <QSqlQuery>
#include <QComboBox>
#include <QVariant>
#include <QTimer>
#include <QStandardItemModel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    service E;
    ui->stackedWidget->setCurrentIndex(0);
       connect(ui->ADD, &QPushButton::clicked, this, &MainWindow::on_ADD_clicked);
       connect(ui->upd, &QPushButton::clicked, this, &MainWindow::on_upd_clicked);
       connect(ui->dlet, &QPushButton::clicked, this, &MainWindow::on_dlet_clicked);


       connect(ui->display, &QPushButton::clicked, this, &MainWindow::on_display_clicked);
       connect(ui->display_2, &QPushButton::clicked, this, &MainWindow::on_display_2_clicked);

       connect(ui->pdf, &QPushButton::clicked, this, &MainWindow::on_Pdf_Clicked);
       connect(ui->serch, &QPushButton::clicked, this, &MainWindow::on_serch_clicked);

       connect(ui->change, &QPushButton::clicked, this, &MainWindow::on_change_clicked);
       connect(ui->ser, &QPushButton::clicked, this, &::MainWindow::on_ser_Clicked);
       connect(ui->ExportToExcel, &QPushButton::clicked, this, &::MainWindow::on_ExportToExcel_Clicked);
       connect(ui->sortByDateEntree, &QPushButton::clicked, this, &MainWindow::on_sortByDateEntree_clicked);
       connect(ui->stat, &QPushButton::clicked, this, &MainWindow::on_stat_clicked);

       connect(ui->pic, &QPushButton::clicked, this, &MainWindow::on_pic_clicked);

       connect(ui->addtsk_2, &QPushButton::clicked, this, &::MainWindow::on_addtask_clicked);

      connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow:: on_pushButton_5_clicked);
      connect(ui->dis, &QPushButton::clicked, this, &MainWindow::on_dis_clicked);

      setupTableView();
       connect(ui->pic_2, &QPushButton::clicked, this, &::MainWindow::on_pic_2_clicked);
       connect(ui->disimage, &QPushButton::clicked, this, &::MainWindow::on_disimage_clicked);

       connect(ui->delettask, &QPushButton::clicked, this, &::MainWindow::on_delettask_clicked);

       connect(ui->suggestPhoto, &QPushButton::clicked, this, &::MainWindow:: on_suggestPhoto_clicked);
       connect(ui->sortByDateEntree_2, &QPushButton::clicked, this, &::MainWindow::on_sortByDateEntree_2_clicked);
       connect(ui->tableView_5, &QTableView::clicked, this, &MainWindow::on_tableView_5_clicked);
       connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::on_updateButton_clicked);




}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_ser_Clicked(){
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_display_clicked() {
    service E;
    ui->tableView->setModel(E.afficher());
}
void MainWindow::on_display_2_clicked() {
    service E;
    ui->tableView_4->setModel(E.afficher());
}
void MainWindow::on_ADD_clicked()
{
    QString id_service = ui->lineEdit_2->text();
    QString Nom_Employe = ui->lineEdit_3->text();
    QString Date_entrée = ui->dateEdit_2->date().toString("dd-MM-yyyy");
    QString Date_sortie = ui->dateEdit->date().toString("dd-MM-yyyy");
    QString Etat_service = ui->comboBox->currentText();  // Get the value from the ComboBox

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
    QDate startDate = ui->dateEdit->date();
    QDate endDate = ui->dateEdit_2->date();
    if (endDate < startDate) {
        QMessageBox::warning(this, "Date invalide", "La date de sortie doit être postérieure à la date d'entrée.");
        return;
    }


    // ComboBox validation: Ensure that the ComboBox item is selected
    if (ui->comboBox->currentIndex() == -1) {
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
            on_ADD_clicked();  // Reload the list after adding the new service
        } else {
            QMessageBox::warning(this, "Erreur", "L'ajout n'a pas été effectué.");
        }

        // Clear the fields
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->comboBox->setCurrentIndex(0);  // Reset the combo box to the first item
        ui->tableView->setModel(E.afficher());  // Update the view with the new list of services
    }
}
void MainWindow::on_upd_clicked()
{

    QString id_service = ui->lineEdit_2->text();
    QString Nom_Employe = ui->lineEdit_3->text();
    QString Date_entrée = ui->dateEdit->date().toString("dd-MM-yyyy");
    QString Date_sortie = ui->dateEdit_2->date().toString("dd-MM-yyyy");
    QString Etat_service = ui->comboBox->currentText();

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
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->dateEdit->clear();
        ui->dateEdit_2->clear();
        ui->comboBox->setCurrentIndex(0);

        // Refresh table view to reflect updated data
        QSqlTableModel *model = static_cast<QSqlTableModel *>(ui->tableView->model());
        if (model) {
            model->select(); // Refresh table data
        }
        service s;
        ui->tableView->setModel(s.afficher());
        ui->tableView->reset();
        // Focus the first field for smoother workflow
        ui->lineEdit_2->setFocus();
    } else {
        QMessageBox::warning(this, "Erreur", "Une erreur est survenue lors de la mise à jour des informations du service.");
    }
}



void MainWindow::on_dlet_clicked()
{
    // Get the selected index from the table view
    QModelIndex index = ui->tableView->currentIndex();

    if (index.isValid()) {
        // Get the service ID from the selected row (assuming the ID is in the first column)
        QString id_service = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toString();

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
                QAbstractItemModel *model = ui->tableView->model();
                model->removeRow(index.row());

                // Optionally, if needed, you can reset the model to ensure proper refresh
                 ui->tableView->setModel(E.afficher());
                 ui->tableView->reset(); // Use this if necessary

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


void MainWindow::on_change_clicked(){

ui->stackedWidget->setCurrentIndex(3);
}



void MainWindow::on_serch_clicked() {

    service E;
    QString searchid = ui->srch->text();


    if (searchid.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a search term.");
        return;
    }


    QSqlQueryModel* model = E.search(searchid);

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "No Results", "No services found matching the search criteria.");
        return;
    }


    ui->tableView_4->setModel(model);

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
    } else {
        QMessageBox::information(this, "Item Not Found", "No matching item was found.");
    }
}
void MainWindow::on_Pdf_Clicked() {
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
    bool pdfCreated1 = s.generatePDF(filePath, ui->tableView);
    bool pdfCreated2 = s.generatePDF(filePath, ui->tableView_4);

    if (pdfCreated1 || pdfCreated2) {
        QMessageBox::information(this, "PDF Saved", "PDF file has been saved successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to create PDF.");
    }
}

void MainWindow::on_ExportToExcel_Clicked() {
    service s;
    if (s.generateExcel(ui->tableView_4)) {
        QMessageBox::information(this, "Excel Export", "Excel file exported successfully.");
    } else {
        QMessageBox::warning(this, "Excel Export", "Failed to export Excel file.");
    }
}
void MainWindow::on_sortByDateEntree_clicked() {
    service E;
    // Sort by Date_entrée and display it in the table view
    ui->tableView_4->setModel(E.sortByDateEntree());
}
void MainWindow::on_sortByDateEntree_2_clicked() {
    service E;
    // Sort by Date_entrée and display it in the table view
    ui->tableView_4->setModel(E.sortByName());
}
void MainWindow::on_stat_clicked()
{
    // Debug message to ensure the function is executed
    qDebug() << "Setting up statistics page";

    setupStatisticsPage();

    qDebug() << "Switching to statistics page";
    ui->stackedWidget->setCurrentIndex(2); // Switch to the statistics page
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
void MainWindow::on_pic_clicked(){
    ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::on_pushButton_5_clicked(){
    ui->stackedWidget->setCurrentIndex(5);
    QString currentTime = getCurrentDateTime();

       // Show current time in a QMessageBox
       QMessageBox::information(this, "Current System Time", "The current date and time is:\n" + currentTime);
}
/*
void MainWindow::populateServiceComboBox() {
    // Create an instance of the Service class to access its method
    service s;

    // Retrieve the list of service IDs
    QStringList serviceIds = s.getServiceIds();

    // Debug log to show the retrieved IDs
    qDebug() << "Service IDs retrieved:" << serviceIds;

    // If the list is empty, show a warning message
    if (serviceIds.isEmpty()) {
        QMessageBox::warning(this, "Database Error", "Failed to retrieve service IDs from the database.");
        return;  // Exit the function if no data was retrieved
    }

    // Clear the combo box before adding new items
    ui->id_ser->clear();

    // Add each service ID to the combo box
    for (const QString &id : serviceIds) {
        ui->id_ser->addItem(id);
    }
}
*/
void MainWindow::on_addtask_clicked() {
    QString id_service = ui->id_ser->text();  // QLineEdit for ID_SERVICE
    QString client = ui->lineEdit_6->text();  // QLineEdit for Client
    QString modele = ui->modele_2->text();  // QLineEdit for Modele
    QString service = ui->comboBox_2->currentText();  // QLineEdit for Service
    QDate date = ui->dateEdit_6->date();  // QDateEdit for Date
    QString prix = ui->prit_2->currentText();  // QComboBox for Priority

    // Get the progress value from the QProgressBar
    int prog = ui->progressBar_2->value();  // Use QProgressBar value
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

void MainWindow::on_tableView_5_clicked(const QModelIndex &index) {
    // Assuming the first column contains the ID_SERVICE
    QString id_service = ui->tableView_5->model()->data(index.siblingAtColumn(0)).toString();

    // Assuming the fourth column contains Priority and fifth contains Progress
    QString priority = ui->tableView_5->model()->data(index.siblingAtColumn(4)).toString();
    int progress = ui->tableView_5->model()->data(index.siblingAtColumn(5)).toInt();

    // Populate the input fields
    ui->id_ser->setText(id_service);
    ui->prit_2->setCurrentText(priority);
    ui->progressBar_2->setValue(progress);
}
void MainWindow::on_updateButton_clicked() {
    QString id_service = ui->id_ser->text();
    QString priority = ui->prit_2->currentText();
    int progress = ui->progressBar_2->value();

    if (id_service.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a service from the table first.");
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE SERVICE SET PRIX = :priority, PROGRESS = :progress WHERE ID_SERVICE = :id_service");
    query.bindValue(":priority", priority);
    query.bindValue(":progress", progress);
    query.bindValue(":id_service", id_service);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "The service has been updated successfully.");
        on_display_clicked();  // Refresh the table view
    } else {
        QMessageBox::warning(this, "Error", "Failed to update the service: " + query.lastError().text());
    }
}

void MainWindow::on_dis_clicked() {
    // Create the task object
    task t;

    // Get the model returned by afficher() method
    QSqlQueryModel *model = t.afficher();  // Assuming this method returns a valid model

    // Set the model to the table view
    ui->tableView_5->setModel(model);

    // Create and set the custom delegate to highlight the rows
    DateHighlightDelegate *delegate = new DateHighlightDelegate(this);
    ui->tableView_5->setItemDelegate(delegate);

    // Refresh the table view to ensure the delegate is applied
    ui->tableView_5->update();

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

void MainWindow::on_delettask_clicked()
{
    // Get the selected index from the table view
    QModelIndex index = ui->tableView_5->currentIndex();

    if (index.isValid()) {
        // Get the service ID from the selected row (assuming the ID is in the first column)
        QString id_service = ui->tableView_5->model()->data(ui->tableView_5->model()->index(index.row(), 0)).toString();

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
                QAbstractItemModel *model = ui->tableView_5->model();
                model->removeRow(index.row());

                // Optionally, if needed, you can reset the model to ensure proper refresh
                 ui->tableView_5->setModel(E.afficher());
                 ui->tableView_5->reset(); // Use this if necessary

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

QString MainWindow::getCurrentDateTime() {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    return currentDateTime.toString("yyyy-MM-dd HH:mm:ss"); // Format the date and time
}
void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);

    // Apply the delegate after the window is shown
    setupTableView();
}
void MainWindow::setupTableView() {
    // Assuming you want to apply the delegate to the 4th column (index 3)
    DateHighlightDelegate *delegate = new DateHighlightDelegate(this);
    ui->tableView_5->setItemDelegateForColumn(3, delegate);  // Apply to the 4th column (index 3)
}
void MainWindow::on_pic_2_clicked()
{
    // Open file dialog to select an image
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp *.jpeg)");

    if (fileName.isEmpty()) {
        return; // No file selected, exit
    }

    // Check if the file is in the allowed directory
    QString allowedPath = "C:/Users/azizm/OneDrive/Desktop/service_image";
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
    QString id_service = ui->lineEdit_5->text();
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
    on_display_clicked(); // Optionally refresh the UI
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

void MainWindow::on_disimage_clicked()
{
    QString id_service = ui->lineEdit_5->text();
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
void MainWindow::on_suggestPhoto_clicked() {
    QString id_service = ui->lineEdit_5->text();  // Get the ID_SERVICE input
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
        {"vidange", {"C:/Users/azizm/OneDrive/Desktop/service_image/vidange1.png",
                     "C:/Users/azizm/OneDrive/Desktop/service_image/vidange.png"}},
        {"oil change", {"C:/Users/azizm/OneDrive/Desktop/service_image/oil change1.png",
                        "C:/Users/azizm/OneDrive/Desktop/service_image/oil change.png"}},
        {"diagnostique", {"C:/Users/azizm/OneDrive/Desktop/service_image/diag1.png",
                          "C:/Users/azizm/OneDrive/Desktop/service_image/diag.png"}},
        {"battery check", {"C:/Users/azizm/OneDrive/Desktop/service_image/bateery1.png",
                           "C:/Users/azizm/OneDrive/Desktop/service_image/batery.png"}},
        {"engine check", {"C:/Users/azizm/OneDrive/Desktop/service_image/engine1.png",
                          "C:/Users/azizm/OneDrive/Desktop/service_image/engine.png"}}
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
        ui->label_20->setPixmap(pixmap1.scaled(ui->label_20->size(), Qt::KeepAspectRatio));
    }

    // Load the second image and display it in label_21
    QPixmap pixmap2(imagePaths[1]);
    if (pixmap2.isNull()) {
        QMessageBox::warning(this, "Error", "Failed to load the second image.");
    } else {
        ui->label_21->setPixmap(pixmap2.scaled(ui->label_21->size(), Qt::KeepAspectRatio));
    }
}

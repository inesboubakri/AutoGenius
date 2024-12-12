#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include "service.h"
#include <QSqlTableModel>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileDialog>
#include <QTextDocument>
#include <QPrinter>
#include <QPainter>
#include <QAxObject>
#include <QFileDialog>
#include <QTableView>
#include <QAbstractItemModel>
#include <QTableWidget>
#include <QSqlRecord>
#include <QPixmap>
#include <QSqlQuery>
#include <QByteArray>
#include <QImage>
#include <QBuffer>
service::service(QString id_service, QString Nom_Employe, QString Date_sortie, QString Date_entrée, QString Etat_service)
{
    this->id_service = id_service;
    this->Nom_Employe = Nom_Employe;
    this->Date_sortie = Date_sortie;
    this->Date_entrée = Date_entrée;
    this->Etat_service = Etat_service;
}


service::service(QString id_service)
{
    this->id_service = id_service;
}
bool service::ajouter()
{

    QSqlQuery query;
    query.prepare("INSERT INTO SERVICE (ID_SERVICE, NOM_EMPLOYE, DATE_ENTRÉE, DATE_SORTIE, ETAT_SERVICE) "
                  "VALUES (:id_service, :nom_employe, :date_entree, :date_sortie, :etat_service)");

    query.bindValue(":id_service", id_service);
    query.bindValue(":nom_employe", Nom_Employe);
    query.bindValue(":date_entree", Date_entrée);
    query.bindValue(":date_sortie", Date_sortie);
    query.bindValue(":etat_service", Etat_service);
    return query.exec();

}

QSqlQueryModel* service::afficher(){

    QSqlQueryModel* model=new
        QSqlQueryModel();
    model->setQuery("select ID_SERVICE,NOM_EMPLOYE,DATE_ENTRÉE,DATE_SORTIE,ETAT_SERVICE from SERVICE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_service"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom_Employe"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date_entrée"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_sortie"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Etat_service"));
    return model;

}
bool service::supprimer(QString id_service)
{
    QSqlQuery query;
    query.prepare("DELETE FROM SERVICE WHERE ID_SERVICE = :id_service");
    query.bindValue(":id_service", id_service);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Error deleting service: " << query.lastError().text();
        return false;
    }
}

bool service::isIdServiceUnique( QString& id_service) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM SERVICE WHERE ID_SERVICE = :id_service");
    query.bindValue(":id_service", id_service);


    if (!query.exec()) {

        QSqlError error = query.lastError();
        qDebug() << "Error executing query:" << error.text();
        return false;
    }


    query.next();
    int count = query.value(0).toInt();


    return count == 0;
}
bool service::updateServiceDetails(QString id_service)
{
    QSqlQuery query;

    // Prepare the SQL query to update multiple fields including dates
    query.prepare("UPDATE SERVICE SET NOM_EMPLOYE = :nom_employe, ETAT_SERVICE = :etat_service, "
                  "DATE_ENTRÉE = :date_entree, DATE_SORTIE = :date_sortie WHERE ID_SERVICE = :id_service");

    // Bind the values to the placeholders in the SQL query
    query.bindValue(":nom_employe", Nom_Employe);  // Employee name
    query.bindValue(":etat_service", Etat_service);  // Service status
    query.bindValue(":date_entree", Date_entrée);  // The new entry date (ensure this is a valid QDate or QString)
    query.bindValue(":date_sortie", Date_sortie);  // The new exit date (ensure this is a valid QDate or QString)
    query.bindValue(":id_service", id_service);  // The ID of the service to update

    // Log the query for debugging purposes
    qDebug() << "Executing query:" << query.executedQuery();

    // Execute the query and check for success
    bool success = query.exec();

    // Check for query execution failure
    if (!success) {
        qDebug() << "Update failed:" << query.lastError().text();  // Log the error if update fails
        return false;
    }

    // Check if any rows were updated
    if (query.numRowsAffected() == 0) {
        qDebug() << "No rows updated. Check if the ID exists or the values are the same.";
        return false;
    }

    // Return true if update was successful
    return true;
}




QSqlQueryModel* service::search( QString &searchid) {
    QSqlQueryModel* model = new QSqlQueryModel();


    QString queryStr = QString("SELECT ID_SERVICE,NOM_EMPLOYE,DATE_ENTRÉE,DATE_SORTIE,ETAT_SERVICE FROM SERVICE WHERE ID_SERVICE LIKE '%%1%'").arg(searchid);
    model->setQuery(queryStr);


    if (model->rowCount() == 0) {
        qDebug() << "No results found for:" << searchid;
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_service"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom_Employe"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date_entrée"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_sortie"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Etat_service"));

    return model;
}

bool service::generatePDF(const QString &filePath, QTableView *tableView) {
    // Set up the printer
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    QPainter painter;
    if (!painter.begin(&printer)) {
        qDebug() << "Failed to start the painter";
        return false;
    }

    // Prepare the document content
    QTextDocument document;
    QAbstractItemModel *model = tableView->model();
    if (!model) {
        qDebug() << "No model found in QTableView";
        painter.end();
        return false;
    }

    QString content = "<h1 style='text-align: center; font-size:24px;'>Service Details</h1><br><table border='1' cellspacing='0' cellpadding='6' width='100%'>";
    content += "<tr style='font-size:16px; font-weight:bold; background-color: #f0f0f0;'>";

    for (int column = 0; column < model->columnCount(); ++column) {
        content += "<th>" + model->headerData(column, Qt::Horizontal).toString() + "</th>";
    }
    content += "</tr>";

    // Set the cell font size
    for (int row = 0; row < model->rowCount(); ++row) {
        content += "<tr style='font-size:14px;'>";
        for (int column = 0; column < model->columnCount(); ++column) {
            content += "<td>" + model->data(model->index(row, column)).toString() + "</td>";
        }
        content += "</tr>";
    }
    content += "</table>";

    document.setHtml(content);
    document.setPageSize(printer.pageRect(QPrinter::DevicePixel).size()); // Set page size correctly

    // Draw the document contents onto the painter
    document.drawContents(&painter);

    // Finish up and close the painter
    painter.end();
    qDebug() << "PDF created successfully at " << filePath;

    return true;
}

bool service::generateExcel(QTableView *tableView) {
    QAbstractItemModel *model = tableView->model();
    if (!model) {
        qDebug() << "No model found in QTableView";
        return false;
    }

    // File path selection
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Save Excel File", "", "Excel Files (*.xlsx);;All Files (*)");
    if (filePath.isEmpty()) {
        return false;
    }
    if (!filePath.endsWith(".xlsx", Qt::CaseInsensitive)) {
        filePath += ".xlsx";
    }

    // Create Excel application
    QAxObject *excel = new QAxObject("Excel.Application");
    excel->setProperty("Visible", false);
    QAxObject *workbook = excel->querySubObject("Workbooks")->querySubObject("Add");
    QAxObject *sheet = workbook->querySubObject("Sheets")->querySubObject("Item(int)", 1);
    sheet->setProperty("Name", "Service Data");

    // Export headers
    for (int col = 0; col < model->columnCount(); ++col) {
        QString header = model->headerData(col, Qt::Horizontal).toString();
        QAxObject *cell = sheet->querySubObject("Cells(int,int)", 1, col + 1);
        cell->setProperty("Value", header);
        cell->setProperty("Font", QVariant(QFont("Arial", 12, QFont::Bold)));
        cell->setProperty("HorizontalAlignment", -4108);  // Center alignment
    }

    // Export data
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString cellValue = model->data(model->index(row, col)).toString();
            QAxObject *cell = sheet->querySubObject("Cells(int,int)", row + 2, col + 1);
            cell->setProperty("Value", cellValue);
            cell->setProperty("Font", QVariant(QFont("Arial", 10)));
        }
    }

    // Auto-fit columns and save
    QAxObject *columns = sheet->querySubObject("Columns");
    columns->dynamicCall("AutoFit()");
    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(filePath));
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");

    delete excel;
    return true;
}
QSqlQueryModel* service::sortByDateEntree() {
    QSqlQueryModel *model = new QSqlQueryModel();
    // Sort by Date_entrée in ascending order
    QString query = "SELECT ID_SERVICE,NOM_EMPLOYE,DATE_ENTRÉE,DATE_SORTIE,ETAT_SERVICE FROM SERVICE ORDER BY DATE_ENTRÉE ASC";
    model->setQuery(query);
    return model;
}
QSqlQueryModel* service::sortByName() {
    QSqlQueryModel *model = new QSqlQueryModel();

    // Sort by NOM_EMPLOYE in ascending order
    QString query = "SELECT ID_SERVICE,NOM_EMPLOYE,DATE_ENTRÉE,DATE_SORTIE,ETAT_SERVICE FROM SERVICE ORDER BY NOM_EMPLOYE ASC";
    model->setQuery(query);

    if (model->lastError().isValid()) {
        qDebug() << "Error sorting by name:" << model->lastError().text();
    }

    return model;
}

QMap<QString, double> service::fetchStatusPercentages()
{
    QMap<QString, double> statusPercentages;
    statusPercentages["in the beginning"] = 0.0;
    statusPercentages["in process"] = 0.0;
    statusPercentages["done"] = 0.0;

    QSqlQuery query;
    query.prepare("SELECT Etat_service, COUNT(*) FROM service GROUP BY Etat_service");

    int totalCount = 0;

    if (query.exec()) {
        QMap<QString, int> statusCounts;

        while (query.next()) {
            QString status = query.value(0).toString();
            int count = query.value(1).toInt();
            if (statusCounts.contains(status)) {
                statusCounts[status] = count;
                totalCount += count; // Accumulate total count
            }
        }

        // Compute percentages
        for (auto it = statusCounts.begin(); it != statusCounts.end(); ++it) {
            if (totalCount > 0) {
                statusPercentages[it.key()] = (it.value() * 100.0) / totalCount;
            }
        }

    } else {
        qDebug() << "Database error: " << query.lastError().text();
    }

    return statusPercentages;
}

task::task(QString id_service, QString nom_client, QString modele, QString service, QDate date_task, QString priority, int prog) {
    this->id_service = id_service;
    this->nom_client = nom_client;
    this->modele = modele;
    this->service = service;  // Initialize the 'service' attribute
    this->date_task = date_task;
    this->priority = priority;
    this->prog = prog;
}




// Method to add a task
bool task::ajouterTask() {
    QSqlQuery query;

    // Prepare the SQL query
    query.prepare("INSERT INTO TASK (ID_SERVICE, NOM_CLIENT, MODELE, DATE_TASK, PRIORITY, PROGRESSE,SERVICE) "
                  "VALUES (:id_service, :nom_client, :modele, TO_DATE(:date_task, 'MM-DD-YYYY'), :priority, :prog,:service)");

    // Bind values to the placeholders
    query.bindValue(":id_service", id_service);
    query.bindValue(":nom_client", nom_client);
    query.bindValue(":modele", modele);

    // Convert QDate to string in MM-DD-YYYY format and bind it
    QString dateString = date_task.toString("MM-dd-yyyy");
    query.bindValue(":date_task", dateString);

    query.bindValue(":priority", priority);
    query.bindValue(":prog", prog);
    query.bindValue(":service", service);
    // Execute the query
    if (!query.exec()) {
        qDebug() << "SQL Error:" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQueryModel* task::afficher(){

    QSqlQueryModel* model=new
        QSqlQueryModel();
    model->setQuery("SELECT * FROM TASK");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_service"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_client"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("modele"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_task"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("priority"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("prog"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("service"));

    return model;

}



// Method to delete a task by ID
bool task::supprimerTask(QString id_service) {
    QSqlQuery query;
    query.prepare("DELETE FROM TASK WHERE ID_SERVICE = :id_service");
    query.bindValue(":id_service", id_service);

    if (query.exec()) {
        qDebug() << "Task deleted successfully.";
        return true;
    } else {
        qDebug() << "Error deleting task: " << query.lastError().text();
        return false;
    }
}

bool service::insertImage(const QString &id_service, const QPixmap &pixmap) {
    // Ensure pixmap is valid
    if (pixmap.isNull()) {
        qWarning() << "Error: Provided pixmap is null.";
        return false;
    }

    // Convert QPixmap to QByteArray
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    if (!pixmap.save(&buffer, "PNG")) {  // Save the pixmap as PNG (change the format if needed)
        qWarning() << "Error: Unable to save pixmap as PNG.";
        return false;
    }

    // Prepare the query to insert the image into the database
    QSqlQuery query;
    query.prepare("INSERT INTO SERVICE (ID_SERVICE, IMAGE) VALUES (:id_service, :image)");
    query.bindValue(":id_service", id_service); // Bind the service ID
    query.bindValue(":image", byteArray);       // Bind the image data as a BLOB

    // Execute the query and check for errors
    if (!query.exec()) {
        qWarning() << "Error inserting image into SERVICE table: " << query.lastError().text();
        return false;
    }

    return true;
}

/*bool service::uploadImage(const QString &id_service, const QByteArray &imageData)
{
    // Ensure image data is not empty
    if (imageData.isEmpty()) {
        qDebug() << "Error: Provided image data is empty.";
        return false;
    }

    // Check if the service ID exists in the database (if needed)
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM SERVICE WHERE id_service = :id_service");
    checkQuery.bindValue(":id_service", id_service);
    if (!checkQuery.exec()) {
        qDebug() << "Error checking service ID existence: " << checkQuery.lastError().text();
        return false;
    }

    checkQuery.next();
    if (checkQuery.value(0).toInt() == 0) {
        qDebug() << "Error: Service ID not found in the database.";
        return false;
    }

    // Prepare the query to insert the image into the database
    QSqlQuery query;
    query.prepare("UPDATE SERVICE SET IMAGE = :image WHERE id_service = :id_service");
    query.bindValue(":id_service", id_service);   // Bind the service ID
    query.bindValue(":image", imageData);         // Bind the image data as a BLOB

    // Execute the query and check for errors
    if (!query.exec()) {
        qDebug() << "Error uploading image: " << query.lastError().text();
        return false;
    }

    return true;
}*/

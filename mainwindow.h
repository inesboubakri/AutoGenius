#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QDateTime>
#include <QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
#include <QSerialPort>
namespace Ui {
class MainWindow;
}
class Arduino {
public:
    Arduino();
    ~Arduino(); // Destructor to handle cleanup

    int connect_arduino();                // Connect to Arduino
    void close_arduino();                  // Close the connection
    void write_to_arduino(const QByteArray &command); // Write data to Arduino
    QByteArray read_from_arduino();        // Read data from Arduino
    QSerialPort* getserial();              // Access the serial port object
    QString getarduino_port_name();        // Get the port name

private:
    QSerialPort *serial;                   // Serial port object
    static const quint16 arduino_uno_vendor_id = 9025;  // Vendor ID for Arduino Uno
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;             // Port name
    bool arduino_is_available;             // Whether Arduino is available
    QByteArray data;                       // Data buffer
    //void write_to_arduino(const QByteArray &command);
    bool is_available();                   // Check Arduino availability

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
protected:
    void showEvent(QShowEvent *event) override; // Declare showEvent
    void setupTableView(); // Declare setupTableView

private slots:
   // void on_on_clicked();

private:
    Ui::MainWindow *ui;

    void on_ADD_clicked();

    void on_dlet_clicked();


    void on_upd_clicked();

    void on_serch_clicked();

     void on_display_clicked();
     void on_display_2_clicked();

     void on_change_clicked();
     void on_Pdf_Clicked();
     void on_ser_Clicked();
     void on_ExportToExcel_Clicked();
     void on_sortByDateEntree_clicked();
     void setupStatisticsPage();
     void on_stat_clicked();
     void on_pic_clicked();

    void on_addtask_clicked();
    void on_pushButton_5_clicked();
    void  populateServiceComboBox();
    void on_dis_clicked();

   QString getCurrentDateTime();
   void on_pic_2_clicked();
   void on_disimage_clicked();
    void  displayImageInTable(const QPixmap &pixmap);
    void on_delettask_clicked();
    void  on_suggestPhoto_clicked();
    void on_sortByDateEntree_2_clicked();
    void on_tableView_5_clicked(const QModelIndex &index);
    void  on_updateButton_clicked();
    void on_ard_clicked();
    void loadServicesToTableView();
    void on_tableView_3_clicked(const QModelIndex &index);
    void setupProgressPage();
    QByteArray data;
    Arduino A;
    void  connectArduino();
    void on_onButton_clicked();
    void on_offButton_clicked();
    bool motorOn = false;  // Track motor state
    Arduino myArduino;     // Declare Arduino as a member of MainWindow
    QSerialPort *serial;
    QSerialPort *serialPort;
    void on_submitButton_clicked();
    void ensureSerialPortOpen();
     void readSerialData();
     QString receivedData;
     void  incrementTapisValue();
     void addIncrementedTapisValue();

};
#include <QStyledItemDelegate>
#include <QDateTime>
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QDebug>  // For debugging purposes

class DateHighlightDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    DateHighlightDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        // Ensure we're working with the correct column (assuming 4th column is the date column)
        QStyleOptionViewItem optionWithColor = option;

        // Get the date from the model
        QString dateString = index.model()->data(index).toString();
        QDate dateFromDb = QDate::fromString(dateString, "dd-MM-yyyy");

        // For debugging purposes, print the date
        qDebug() << "Date from DB: " << dateString << "Parsed Date: " << dateFromDb;

        // Get current date
        QDate currentDate = QDate::currentDate();

        // If the date from the database is older than the current date, set the background color to red
        if (dateFromDb.isValid() && dateFromDb < currentDate) {
            // Apply the red background color for all cells in the row
            optionWithColor.backgroundBrush = QBrush(QColor(255, 0, 0)); // Red background for expired dates
        }

        // Paint the item with the modified option
        QStyledItemDelegate::paint(painter, optionWithColor, index);
    }
};

#endif // MAINWINDOW_H

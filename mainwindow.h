#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QDateTime>
namespace Ui {
class MainWindow;
}

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

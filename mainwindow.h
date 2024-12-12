#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "locaux.h"
#include "employee.h"
#include "service.h"
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QDateTime>

/*#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineSettings>*/
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void toggleSidebar();
    void showSidebar();
    void on_loc_addButton_clicked();

    void on_pushButtonlocadd_sortir_clicked();

    void on_pushButtonlocadd_ajouter_clicked();

    void on_pushButtonhome_clicked();

    void on_pushButtonclient_clicked();

    void on_pushButtonpartenaire_clicked();

    void on_pushButtonemploye_clicked();

    void on_pushButtonservice_clicked();

    void on_pushButtonvehicule_clicked();

    void on_pushButtonlocaux_clicked();

    void on_pushButton_locdel_sortir_clicked();

    void on_loc_delButton_clicked();

    void on_pushButton_locdel_supprimer_clicked();

    void on_pushButton_locmod_sortir_clicked();

    void on_pushButton_locmod_modifier_clicked();

    void on_loc_modButton_clicked();
private slots:
    //locaux modifier
    void tableViewlocmod_clicked(const QModelIndex &index);
    void on_pushButton_loctri_clicked();

    void on_pushButton_locPDF_clicked();

    void on_pushButton_locrecherche_clicked();

    void on_pushButton_locstat_clicked();
    void on_pushButton_locexel_clicked();

    void on_pushButton_lochistory_clicked();

    void on_pushButton_lochis_sortir_clicked();

    void on_pushButton_maps_clicked();

    void on_pushButton_emp_ajouter_clicked();

    void on_pushButton_emp_modifier_clicked();

    void on_pushButton_emp_tri_clicked();

    void on_pushButton_empajoutersortir_clicked();

    void on_pushButton_empmodsortir_clicked();

    void on_pushButton_emp_edit_clicked();

    void on_pushButtonempaddajouter_clicked();

    void on_pushButton_emp_delete_clicked();

    void on_pushButton_empmodmod_clicked();

    void on_researchcinemp_textChanged(const QString &arg1);

    void on_pushButton__pdf_clicked();

    void on_pushButtonstatempsortir_clicked();

    void on_pushButton_emp_stat_clicked();

    void on_pushButtonserviceavancesortir_clicked();

    void on_pushButtonservicetool_clicked();

    void on_pushButton_serajouter_clicked();

    void on_tableViewser_clicked(const QModelIndex &index1);


    void on_pushButtonsermodif_clicked();

    void on_pushButtonsersup_clicked();

    void on_pushButtonserrecherche_clicked();

    void on_pushButtonserpdf_clicked();

    void on_pushButtonserexel_clicked();

    void on_pushButtontridate_clicked();

    void on_pushButtonsertrinom_clicked();

    void on_pushButtonserstatsortir_clicked();

    void on_pushButtonserstat_clicked();

    void on_pushButtontodosortir_clicked();

    void on_pushButtonsertodo_clicked();

    void on_pushButtontodoajouter_clicked();

    void on_tableViewtodo_clicked(const QModelIndex &index);

    void on_pushButtontodoafficher_clicked();

    void on_pushButtontodosup_clicked();

    void on_pushButtonserphototelecharger_clicked();

    void on_pushButtonserphotoafficher_clicked();

    void on_pushButtonserphotopropose_clicked();

    void on_pushButtonserphoto_clicked();

    void on_pushButtonserphotosortir_clicked();

private:
    Ui::MainWindow *ui;


    //locaux
    QPropertyAnimation *sidebarAnimation;
    QPropertyAnimation *frameAnimation;
    bool isSidebarVisible;
    locaux Etmp;
    //locaux modifier

    void populateLineEditsloc();
    locaux currentLocal;
    //load tableview
    QSqlQueryModel *modelloc;
    QSortFilterProxyModel *proxyModelloc;
    void loadtabloc();
    QSqlQueryModel *modellocdel;
    QSortFilterProxyModel *proxyModellocdel;
    void loadtablocdel();
    QSqlQueryModel *modellocmod;
    QSortFilterProxyModel *proxyModellocmod;

    void loadtablocmod();
    //clear line edit
    void locaddclearline();
    void locmodclearline();

    void sortlocTable();
    void exportToPDF();
    void searchNomLocale(int columnIndex);
    void showEmployeeChartloc();
    void exportlocToExcel();
    QSqlQueryModel *modellochis;
    QSortFilterProxyModel *proxyModellochis;
    void loadlocHistory();
    void showMap();




    //employee
    QSqlQueryModel *modelemp;
    QSortFilterProxyModel *proxyModelemp;
    void loadtabemp();
    void sortempTable();
    void exportToPDFemp();




    //service
    QSqlQueryModel *modelser;
    QSortFilterProxyModel *proxyModelser;
    QSqlQueryModel *modelsertools;
    QSortFilterProxyModel *proxyModelsertools;
    QSqlQueryModel *modelsertask;
    QSortFilterProxyModel *proxyModelsertask;
    void loadtabser();
    void loadtabsertools();
    void loadtabsertask();
    void setupStatisticsPage();
    QString getCurrentDateTime();
    void displayImageInTable(const QPixmap &pixmap);

};
#endif // MAINWINDOW_H

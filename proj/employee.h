#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QDate>

class Employees
{
    int CIN_EMPLOYEES;
    QString NOM_EMP;
    QString PRENOM_EMP;
    QString SEX_EMP;
    QDate DATE_NS_EMP;
    QString ADRESSE_EMP;
    QString EMAIL_EMP;
    QString NUM_TEL_EMP;
    QString POSTE_EMP;
    QString MDP_EMP;

public:
    Employees() {}
    Employees(int, QString, QString, QString, QDate, QString, QString, QString, QString, QString);

    int getCIN_EMPLOYEES() { return CIN_EMPLOYEES; }
    QString getNOM_EMP() { return NOM_EMP; }
    QString getPRENOM_EMP() { return PRENOM_EMP; }
    QString getSEX_EMP() { return SEX_EMP; }
    QDate getDATE_NS_EMP() { return DATE_NS_EMP; }
    QString getADRESSE_EMP() { return ADRESSE_EMP; }
    QString getEMAIL_EMP() { return EMAIL_EMP; }
    QString getNUM_TEL_EMP() { return NUM_TEL_EMP; }
    QString getPOSTE_EMP() { return POSTE_EMP; }
    QString getMDP_EMP() { return MDP_EMP; }

    void setCIN_EMPLOYEES(int cin) { CIN_EMPLOYEES = cin; }
    void setNOM_EMP(QString nom) { NOM_EMP = nom; }
    void setPRENOM_EMP(QString prenom) { PRENOM_EMP = prenom; }
    void setSEX_EMP(QString sex) { SEX_EMP = sex; }
    void setDATE_NS_EMP(QDate date_ns) { DATE_NS_EMP = date_ns; }
    void setADRESSE_EMP(QString adresse) { ADRESSE_EMP = adresse; }
    void setEMAIL_EMP(QString email) { EMAIL_EMP = email; }
    void setNUM_TEL_EMP(QString tel) { NUM_TEL_EMP = tel; }
    void setPOSTE_EMP(QString poste) { POSTE_EMP = poste; }
    void setMDP_EMP(QString mdp) { MDP_EMP = mdp; }

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* search(int);
    void getByCIN(const int& cin);
    QSqlQueryModel* trierParCIN();
    QMap<QString, int> statistiquesParSexe();
    bool connexion(int cin, QString motDePasse);
    bool genererCodeParCIN(int cin_employee);
    bool verifierEtSupprimerCode(int code_verification);
    bool modifierMotDePasse(int cin_employee, const QString& nouveau_mot_de_passe);
};

#endif // EMPLOYEE_H

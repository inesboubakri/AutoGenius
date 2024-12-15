#include <QSqlError>
#include <iostream>
#include <typeinfo>
#include <string>
#include <QMessageBox>
#include "employee.h"
#include<QDebug>
#include <QRandomGenerator>
#include<mailer.h>


using namespace std;

Employees::Employees(int cin_employee, QString nom, QString prenom, QString gender, QDate date, QString adresse, QString email, QString tel, QString poste, QString mdp)
{
    CIN_EMPLOYEES = cin_employee;
    NOM_EMP = nom;
    PRENOM_EMP = prenom;
    SEX_EMP = gender;
    DATE_NS_EMP = date;
    ADRESSE_EMP = adresse;
    EMAIL_EMP = email;
    NUM_TEL_EMP = tel;
    POSTE_EMP = poste;
    MDP_EMP = mdp;
}

bool Employees::ajouter()
{

    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYEES (CIN_EMPLOYEES, NOM_EMP, PRENOM_EMP, EMAIL_EMP, DATE_NS_EMP, ADRESSE_EMP, NUM_TEL_EMP, POSTE_EMP, SEX_EMP, MDP_EMP) "
                  "VALUES (:cin_emp, :nom_emp, :prenom_emp, :email_emp, :DATE_NS_EMP, :adresse_emp, :tel_emp, :poste_emp, :sex_emp, :mdp_emp)");


    query.bindValue(":cin_emp", CIN_EMPLOYEES);
    query.bindValue(":nom_emp", NOM_EMP);
    query.bindValue(":prenom_emp", PRENOM_EMP);
    query.bindValue(":DATE_NS_EMP", DATE_NS_EMP);
    query.bindValue(":adresse_emp", ADRESSE_EMP);
    query.bindValue(":email_emp", EMAIL_EMP);
    query.bindValue(":tel_emp", NUM_TEL_EMP);
    query.bindValue(":poste_emp", POSTE_EMP);
    query.bindValue(":mdp_emp", MDP_EMP);
    query.bindValue(":sex_emp", SEX_EMP);

    qDebug() << "Query: " << query.lastQuery();
    bool res = query.exec();

    if (!res) {
        qDebug() << "Error adding employee:" << query.lastError().text();
    }

    return res;
}

QSqlQueryModel* Employees::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYEES ");
    if (!query.exec()) {
        qDebug() << "Erreur lors de la recherche :" << query.lastError().text();
        delete model;
        return nullptr;
    }


    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN_EMPLOYEES"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_EMP"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_EMP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL_EMP"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_NS_EMP"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ADRESSE_EMP"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("NUM_TEL_EMP"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("POSTE_EMP"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("SEX_EMP"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("MDP_EMP"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("CARD_NUMBER"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("ACCESS_STATUS"));


    qDebug() <<"cccc"<<model ;
    return model;
}

bool Employees::modifier()
{
    QSqlQuery query;

    query.prepare("UPDATE EMPLOYEES SET  NOM_EMP = :nom_emp, PRENOM_EMP = :prenom_emp, DATE_NS_EMP = :DATE_NS_EMP, ADRESSE_EMP = :adresse_emp, EMAIL_EMP = :email_emp, NUM_TEL_EMP = :tel_emp, POSTE_EMP = :poste_emp, MDP_EMP = :mdp_emp, SEX_EMP = :sex_emp WHERE CIN_EMPLOYEES = :cin_emp");
    query.bindValue(":cin_emp", CIN_EMPLOYEES);
    query.bindValue(":nom_emp", NOM_EMP);
    query.bindValue(":prenom_emp", PRENOM_EMP);
    query.bindValue(":sex_emp", SEX_EMP);
    query.bindValue(":DATE_NS_EMP", DATE_NS_EMP);
    query.bindValue(":adresse_emp", ADRESSE_EMP);
    query.bindValue(":email_emp", EMAIL_EMP);
    query.bindValue(":tel_emp", NUM_TEL_EMP);
    query.bindValue(":poste_emp", POSTE_EMP);
    query.bindValue(":mdp_emp", MDP_EMP);

    qDebug() << "Query: " << query.lastQuery();
    bool res = query.exec();

    if (!res) {
        qDebug() << "Error editing employee:" << query.lastError().text();
    }

    return res;
}

bool Employees::supprimer(int cin_employee)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYEES WHERE CIN_EMPLOYEES = :cin_emp");
    query.bindValue(":cin_emp", cin_employee);
    return query.exec();
}

QSqlQueryModel* Employees::search(int cin_employee)
{
    QSqlQuery query;
    QSqlQueryModel* model = new QSqlQueryModel();

    query.prepare("SELECT * FROM EMPLOYEES WHERE CIN_EMPLOYEES LIKE :valeur");
    query.bindValue(":valeur", "%" + QString::number(cin_employee) + "%");


    if (query.exec()) {
        if (query.next()) {
            model->setQuery(query);
        } else {
            QMessageBox::warning(nullptr, "No Result", "No employee found with the entered CIN.");
        }
    } else {
        QMessageBox::critical(nullptr, "Database Error", "Failed to execute query.");
    }

    return model;
}
void Employees::getByCIN(const int& cin) {
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYEES WHERE CIN_EMPLOYEES = :CIN");
    query.bindValue(":CIN", cin);

    if (query.exec() && query.next()) {
        this->CIN_EMPLOYEES=query.value("CIN_EMPLOYEES").toInt();
        this->NOM_EMP = query.value("NOM_EMP").toString();
        this->PRENOM_EMP = query.value("PRENOM_EMP").toString();
        this->EMAIL_EMP = query.value("EMAIL_EMP").toString();
        this->DATE_NS_EMP = query.value("DATE_NS_EMP").toDate();
        this->ADRESSE_EMP = query.value("ADRESSE_EMP").toString();
        this->NUM_TEL_EMP = query.value("NUM_TEL_EMP").toString();
        this->POSTE_EMP = query.value("POSTE_EMP").toString();
        this->SEX_EMP = query.value("SEX_EMP").toString();
        this->MDP_EMP = query.value("MDP_EMP").toString();
    }
}


QSqlQueryModel* Employees::trierParCIN() {
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYEES ORDER BY CIN_EMPLOYEES ASC");

    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Error sorting by CIN:" << query.lastError().text();
    }

    return model;
}

QMap<QString, int> Employees::statistiquesParSexe() {
    QMap<QString, int> stats;
    QSqlQuery query("SELECT SEX_EMP, COUNT(*) FROM EMPLOYEES GROUP BY SEX_EMP");

    while (query.next()) {
        QString sexe = query.value(0).toString();
        int count = query.value(1).toInt();
        stats[sexe] = count;
    }

    return stats;
}
bool Employees::connexion(int cin, QString motDePasse) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYEES WHERE CIN_EMPLOYEES = :cin AND MDP_EMP = :mdp");
    query.bindValue(":cin", cin);
    query.bindValue(":mdp", motDePasse);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la connexion :" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }
}

bool Employees::genererCodeParCIN(int cin_employee) {
    QSqlQuery query;

    query.prepare("SELECT EMAIL_EMP FROM EMPLOYEES WHERE CIN_EMPLOYEES = :cin_emp");
    query.bindValue(":cin_emp", cin_employee);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la recherche de l'employé :" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur", "Une erreur est survenue lors de la recherche de l'employé. Veuillez réessayer plus tard.");
        return false;
    }

    if (query.next()) {
        QString email = query.value(0).toString();

        int code = QRandomGenerator::global()->bounded(1000000, 10000000);

        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE EMPLOYEES SET CODE_VERIFICATION = :code WHERE CIN_EMPLOYEES = :cin_emp");
        updateQuery.bindValue(":code", code);
        updateQuery.bindValue(":cin_emp", cin_employee);

        if (!updateQuery.exec()) {
            qDebug() << "Erreur lors de l'enregistrement du code :" << updateQuery.lastError().text();
            QMessageBox::critical(nullptr, "Erreur", "Une erreur est survenue lors de l'enregistrement du code. Veuillez réessayer plus tard.");
            return false;
        }

        QString sujet = "Réinitialisation de mot de passe";
        QString contenu = QString(
                              "Bonjour,\n\n"
                              "Nous avons reçu une demande de réinitialisation de votre mot de passe.\n"
                              "Voici votre code de récupération : **%1**.\n\n"
                              "Veuillez noter que ce code est valide pour une seule utilisation et doit être utilisé immédiatement.\n\n"
                              "Si vous n'êtes pas à l'origine de cette demande, veuillez ignorer cet email.\n\n"
                              "Cordialement,\n"
                              "L'équipe de support."
                              ).arg(QString::number(code));

        mailer mail;
        int reponse = mail.sendEmail(email, sujet, contenu);

        if (reponse > 0) {
            QMessageBox::information(nullptr, "Succès", "Un email contenant le code de récupération a été envoyé avec succès.");
            return true;
        } else {
            QMessageBox::critical(nullptr, "Erreur", "Une erreur est survenue lors de l'envoi de l'email. Veuillez réessayer plus tard.");
            return false;
        }
    } else {
        QMessageBox::warning(nullptr, "Recherche", "Aucun employé trouvé avec ce CIN. Veuillez vérifier les informations saisies.");
        return false;
    }
}
bool Employees::verifierEtSupprimerCode(int code_verification) {
    QSqlQuery query;

    // Préparer la requête pour vérifier l'existence de l'employé avec le code de vérification
    query.prepare("SELECT COUNT(*) FROM EMPLOYEES WHERE CODE_VERIFICATION = :code_verif");
    query.bindValue(":code_verif", code_verification);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la vérification du code de vérification :" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur", "Une erreur est survenue lors de la vérification. Veuillez réessayer plus tard.");
        return false;
    }

    if (query.next() && query.value(0).toInt() > 0) {
        QSqlQuery deleteQuery;
        deleteQuery.prepare("UPDATE EMPLOYEES SET CODE_VERIFICATION = NULL WHERE CODE_VERIFICATION = :code_verif");
        deleteQuery.bindValue(":code_verif", code_verification);

        if (deleteQuery.exec()) {
            qDebug() << "Code de vérification supprimé avec succès.";
            return true; // Succès
        } else {
            qDebug() << "Erreur lors de la suppression du code de vérification :" << deleteQuery.lastError().text();
            QMessageBox::critical(nullptr, "Erreur", "Une erreur est survenue lors de la vérification. Veuillez réessayer plus tard.");
            return false;
        }
    } else {
        qDebug() << "Aucun employé trouvé avec ce code de vérification.";
        QMessageBox::warning(nullptr, "Code invalide", "Aucun employé trouvé avec ce code de vérification. Veuillez vérifier les informations saisies.");
        return false;
    }
}
bool Employees::modifierMotDePasse(int cin_employee, const QString& nouveau_mot_de_passe) {
    QSqlQuery query;

    query.prepare("SELECT COUNT(*) FROM EMPLOYEES WHERE CIN_EMPLOYEES = :cin_emp");
    query.bindValue(":cin_emp", cin_employee);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la vérification de l'employé :" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur", "Une erreur est survenue lors de la vérification. Veuillez réessayer plus tard.");
        return false;
    }

    if (query.next() && query.value(0).toInt() > 0) {
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE EMPLOYEES SET MDP_EMP = :password WHERE CIN_EMPLOYEES = :cin_emp");
        updateQuery.bindValue(":password", nouveau_mot_de_passe);
        updateQuery.bindValue(":cin_emp", cin_employee);

        if (updateQuery.exec()) {
            qDebug() << "Mot de passe modifié avec succès pour CIN :" << cin_employee;
            QMessageBox::information(nullptr, "Succès", "Le mot de passe a été modifié avec succès.");
            return true;
        } else {
            qDebug() << "Erreur lors de la modification du mot de passe :" << updateQuery.lastError().text();
            QMessageBox::critical(nullptr, "Erreur", "Impossible de modifier le mot de passe. Veuillez réessayer.");
            return false;
        }
    } else {
        qDebug() << "Aucun employé trouvé avec ce CIN.";
        QMessageBox::critical(nullptr, "Erreur", "Une erreur est survenue lors de la vérification. Veuillez réessayer plus tard.");
        return false;
    }
}

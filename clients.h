#ifndef CLIENTS_H
#define CLIENTS_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>

class CLIENTS
{
    QString NOM,PRENOM,POSTE,SEXE,MATRICULE;
    int CIN_CLIENT,TELEPHONE;
    QDate DATE_NAISSANCE;


public:

  CLIENTS  (){}
     CLIENTS(QString NOM, QString PRENOM, QString POSTE, QString SEXE,QString MATRICULE, int CIN_CLIENT,int TELEPHONE, QDate DATE_NAISSANCE);
     QString getNom(){return NOM;  }
      QString getPRENOM(){return PRENOM;  }
       QString getPOSTE(){return POSTE;  }
         QString getSEXE(){return SEXE;  }
           QString getMATRICULE(){return MATRICULE;  }
             int getCIN_CLIENT(){return CIN_CLIENT;  }
                 int getTELEPHONE(){return TELEPHONE;  }
                   QDate  getDATE_NAISSANCE(){return DATE_NAISSANCE;  }



      void setNom(QString nvNOM){NOM=nvNOM;}

       void setPRENOM(QString nvPRENOM){PRENOM=nvPRENOM;}
         void setPOSTE(QString nvPOSTE){POSTE=nvPOSTE;}

              void setSEXE(QString nvSEXE){SEXE=nvSEXE;}
                void setMATRICULE(QString nvMATRICULE){MATRICULE=nvMATRICULE;}
                  void setCIN_CLIENT(int nvCIN_CLIENT){CIN_CLIENT=nvCIN_CLIENT;}
                 void setTELEPHONE(int nvTELEPHONE){TELEPHONE=nvTELEPHONE;}
        void setDATE_NAISSANCE(QDate nvDATE_NAISSANCE){DATE_NAISSANCE=nvDATE_NAISSANCE;}


         bool ajouter();
      QSqlQueryModel *afficher();
      bool supprimer (int);
      bool   modifier(int CIN_CLIENT);
      QSqlQuery rechercher(int cin);
      QSqlQueryModel *trier1();
      QSqlQueryModel *trier2();
      QSqlQuery prendre(int cin);
      QSqlQueryModel *affichercalendar();
      QSqlQuery recherchepardate(QString date);
      QSqlQuery prendrefromvehicule(QString id);
      QSqlQuery prendrefromclient(QString cin);
      QSqlQuery getQR(QString QR);
      void updateetat(QString mat);

};

#endif // CLIENTS_H

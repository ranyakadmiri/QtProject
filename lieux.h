#ifndef LIEUX_H
#define LIEUX_H
#include<QString>
#include<QSqlQueryModel>

class Lieux
{
public:

    Lieux();

  Lieux(QString,QString,QString,QString,QString);
  QString getid_lieux();
      QString getadresse();
       QString getcapacite();
        QString getprix_location();
        QString getnbr_reservation();

        void setid_lieux(QString);
      void setadresse(QString);
      void setcapacite(QString);
      void setprix_location(QString);
      void setnbr_reservation(QString);
      bool ajouter();
        bool supprimer(QString);
        bool modifier();
      QSqlQueryModel* afficher();
      QSqlQueryModel *trie_NBR_Reservation(QString croissance,QString critere);
      bool rech(int);
      QSqlQueryModel* rechercher(QString);



      private:
          QString id_lieux;
          QString nbr_reservation;
          QString adresse,capacite,prix_location;


};

#endif // LIEUX_H

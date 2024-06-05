#include "lieux.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QString>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlQueryModel>
Lieux::Lieux()
{

}

Lieux::Lieux(QString id_lieux,QString adresse,QString capacite,QString prix_location,QString nbr_reservation)
{
    this->id_lieux=id_lieux;
      this->adresse=adresse;
    this->capacite=capacite;
       this->prix_location=prix_location;
    this->nbr_reservation=nbr_reservation;

}
QString Lieux::getid_lieux(){return id_lieux;}
QString Lieux::getadresse(){return adresse;}
QString Lieux::getcapacite(){return capacite ;}
QString Lieux::getprix_location(){return prix_location;}
QString Lieux::getnbr_reservation(){return nbr_reservation;}
void Lieux::setid_lieux(QString id_lieux) { this->id_lieux=id_lieux; }
void Lieux::setadresse(QString adresee){ this->adresse=adresee;}
void Lieux::setcapacite(QString capacite){ this->capacite=capacite;}
void Lieux::setprix_location(QString prix_location){ this->prix_location=prix_location;}
void Lieux::setnbr_reservation(QString nbr_reservation) { this->nbr_reservation=nbr_reservation; }

bool Lieux::ajouter()
{

    QSqlQuery query;


        query.prepare("INSERT INTO lieux (id_lieux,adresse,capacite,prix_location,nbr_reservation,etat) VALUES ( :id_lieux, :adresse, :capacite, :prix_location, :nbr_reservation, :etat)");
        query.bindValue(":id_lieux",id_lieux);
        query.bindValue(":adresse",adresse);
        query.bindValue(":capacite",capacite);
        query.bindValue(":prix_location",prix_location);
        query.bindValue(":etat","Accessible");
        query.bindValue(":nbr_reservation",nbr_reservation);
          return  query.exec();


}
bool Lieux::supprimer(QString id)
{
    QSqlQuery query;
         query.prepare("Delete from lieux where id_lieux= :id");
         query.bindValue(":id",id);

    return query.exec();


}
QSqlQueryModel *Lieux::afficher(){

    QSqlQueryModel * model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM lieux");
  model->setHeaderData(0,Qt::Horizontal, QObject::tr("id_lieux"));
  model->setHeaderData(1,Qt::Horizontal, QObject::tr("adresse"));
  model->setHeaderData(2,Qt::Horizontal, QObject::tr("capacite"));
  model->setHeaderData(3,Qt::Horizontal, QObject::tr("prix_location"));
  model->setHeaderData(4,Qt::Horizontal, QObject::tr("nbr_reservation"));
  model->setHeaderData(5,Qt::Horizontal, QObject::tr("etat"));
   return model;
}


bool Lieux::modifier()
{

    QSqlQuery query;


         query.prepare("UPDATE  lieux SET id_lieux='"+id_lieux+"',adresse='"+adresse+"',capacite='"+capacite+"',prix_location='"+prix_location+"',nbr_reservation='"+nbr_reservation+"'");
         query.bindValue(0, id_lieux);
         query.bindValue(1,adresse);
         query.bindValue(2,capacite);
         query.bindValue(3, prix_location);
         query.bindValue(4, nbr_reservation);

    return query.exec();
}
QSqlQueryModel *Lieux::trie_NBR_Reservation(QString croissance,QString critere)
{
    QSqlQueryModel *modal=new QSqlQueryModel();

    if(critere == "NBR_Reservation" && croissance == "ASC")
        modal->setQuery("select * from lieux order by nbr_reservation ASC ");
    else if(critere == "NBR_Reservation" && croissance == "DESC")
        modal->setQuery("select * from lieux order by nbr_reservation DESC ");

    return  modal;
}
bool Lieux::rech(int x){
    QSqlQuery query;
    query.prepare("select * from lieux where id_lieux=:id_lieux;");
    query.bindValue(":id_lieux", x);
    return query.exec();
}

QSqlQueryModel* Lieux::rechercher(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from lieux where id_lieux='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_lieux"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("adresse"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("capacite"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix_location"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("nbr_reservation"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("etat"));


            return model;
    }









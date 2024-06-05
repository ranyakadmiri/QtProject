#include "client.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>
#include <QDate>

Client::Client()
{
    this->cin="";
    this->nom="";
    this->prenom ="";
    this->adresse="";
    this->tel="";



}
Client::Client(QString cin,QString nom,QString prenom,QString adresse,QString tel)
{
    this->cin=cin;
     this->nom=nom;
     this->prenom=prenom;
     this->adresse=adresse;
    this->tel=tel;



}
bool Client::ajouter_Cl()
{
    QSqlQuery query;
    query.prepare("INSERT INTO client (cin,nom,prenom,adresse,tel) VALUES (:cin,:nom,:prenom,:adresse,:tel)");
    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":tel",tel);

    return query.exec();
}
QSqlQueryModel * Client::afficher_Cl()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from client");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("tel"));
        return model;
}


bool Client::modifier_Cl(QString cin,QString nom,QString prenom,QString adresse,QString tel)
{
    QSqlQuery query;
    query.prepare("UPDATE client SET cin = :cin,nom = :nom,prenom = :prenom,adresse = :adresse,tel = :tel  WHERE cin= :cin ");
    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":tel",tel);
    return    query.exec();
}


bool Client::supprimer_Cl(QString cin)
{
    QSqlQuery query;

    query.prepare("Delete from client where cin = :cin ");
    query.bindValue(":cin", cin);
    return    query.exec();
}


QSqlQueryModel* Client::recherche(QString c)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT* FROM client WHERE cin like '"+c+"' ||'%' OR nom like '"+c+"' ||'%' OR prenom like '"+c+"' ||'%' OR adresse like '"+c+"' ||'%' OR tel like '"+c+"' ||'%' OR cin like '"+c+"' ");
    query.bindValue(":cin",c);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("tel"));

    return model;
}


QSqlQueryModel* Client::tri()
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM client ORDER BY cin ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("tel"));

    return model;
}



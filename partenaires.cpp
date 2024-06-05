#include "partenaires.h"


partenaires::partenaires(int id,QString nomentr,QString nom,QString prenom,QString service,QString email,int numeros)
{
    this->id=id;
     this->nomentr=nomentr;
    this->nom=nom;
    this->prenom=prenom;
   this->service=service;
    this->email=email;
    this->numeros=numeros;
}

bool partenaires::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id);
    QString resn = QString::number(numeros);
    query.prepare("INSERT INTO PARTENAIRE(ID,NOMENTREPRISE,NOM,PRENOM,SERVICE,EMAIL,NUMEROS)"
                  "VALUES (:ID,:NOMENTREPRISE,:NOM,:PRENOM,:SERVICE,:EMAIL,:NUMEROS)");
    query.bindValue(0,res);
    query.bindValue(1,nomentr);
    query.bindValue(2,nom);
    query.bindValue(3,prenom);
    query.bindValue(4,service);
    query.bindValue(5,email);
    query.bindValue(6,resn);

    return  query.exec();
}
 QSqlQueryModel * partenaires::afficher()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("SELECT* FROM PARTENAIRE");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom d'entreprise"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("Prenom"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("Service"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("Email"));
model->setHeaderData(6, Qt::Horizontal,QObject::tr("Numero"));
return model;
 }
 QSqlQueryModel * partenaires::afficher1()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setHeaderData(0, Qt::Horizontal,QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom d'entreprise"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("Prenom"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("Service"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("Email"));
model->setHeaderData(6, Qt::Horizontal,QObject::tr("Numero"));
return model;
 }

bool partenaires::supprimer(int id)
{
QSqlQuery query;
query.prepare("delete from partenaire where id=:id");
query.bindValue(0,id);
 return query.exec();
}

bool partenaires::modifier()
{
    QSqlQuery query;
    QString res1 = QString::number(id);
    QString resn1 = QString::number(numeros);
          query.prepare("UPDATE PARTENAIRE SET NOMENTREPRISE=:NOMENTREPRISE,NOM=:NOM,PRENOM=:PRENOM,SERVICE=:SERVICE,EMAIL=:EMAIL,NUMEROS=:NUMEROS"
                        "WHERE ID=:ID");
          query.bindValue(":ID",res1);
          query.bindValue(":NOMENTREPRISE",nomentr);
          query.bindValue(":NOM",nom);
          query.bindValue(":PRENOM",prenom);
          query.bindValue(":SERVICE",service);
          query.bindValue(":EMAIL",email);
          query.bindValue(":NUMEROS",resn1);

          return query.exec();
}

QSqlQueryModel *partenaires::recherche(QString n)
{ // QSqlQuery query;
    QSqlQueryModel *model = new QSqlQueryModel();
       model->setQuery("select * from PARTENAIRE where (nom) like ('%"+n+"%')");
  // query.bindValue(0,id);
  // query.exec();
   return model;
}

QSqlQueryModel *partenaires::trier(QString croissance,QString critere)
{
    QSqlQueryModel *modal=new QSqlQueryModel();

    if(critere == "id" && croissance == "ASC")
        modal->setQuery("select * from PARTENAIRE order by ID ASC ");
    else if(critere == "id" && croissance == "DESC")
        modal->setQuery("select * from PARTENAIRE order by ID  DESC ");

    else if(critere == "nomentr" && croissance == "ASC")
        modal->setQuery("select * from PARTENAIRE order by NOMENTREPRISE ASC ");
    else if(critere == "nomentr" && croissance == "DESC")
        modal->setQuery("select * from PARTENAIRE order by NOMENTREPRISE DESC ");

    else if(critere == "nom" && croissance == "ASC")
        modal->setQuery("select * from PARTENAIRE order by NOM ASC ");
    else if(critere == "nom" && croissance == "DESC")
        modal->setQuery("select * from PARTENAIRE order by NOM DESC ");

    else if(critere == "prenom" && croissance == "ASC")
        modal->setQuery("select * from PARTENAIRE order by PRENOM ASC ");
    else if(critere == "prenom" && croissance == "DESC")
        modal->setQuery("select * from PARTENAIRE order by PRENOM DESC ");


/*
    else if(critere == "NumEvent" && croissance == "")
        modal->setQuery("select * from PARTENAIRE order by NUMEVENT");
    else if(critere == "NumEvent" && croissance == "")
        modal->setQuery("select * from PARTENAIRE order by NUMEVENT");

    else if(critere == "lieu" && croissance == "")
        modal->setQuery("select * from PARTENAIRE order by LIEU");
    else if(critere == "lieu" && croissance == "")
        modal->setQuery("select * from EVENEMENT order by LIEU");

    else if(critere == "type" && croissance == "")
        modal->setQuery("select * from PARTENAIRE order by TYPE");
    else if(critere == "Prenom" && croissance == "")
        modal->setQuery("select * from EVENEMENT order by TYPE");

    else if(critere == "nbinvit" && croissance == "")
        modal->setQuery("select * from PARTENAIRE order by NBINVIT");
    else if(critere == "nbinvit" && croissance == "")
        modal->setQuery("select * from PARTENAIRE order by NBINVIT");*/

    return  modal;
}


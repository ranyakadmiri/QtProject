#include "employe.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include <QChart>
#include <QtCharts>
#include <QIntValidator>
#include <QPieSeries>
#include <QChartView>
#include <QGraphicsView>
Employe::Employe()
{
id_employe=0;nom=" ";prenom=" ";poste=" ";num=0;password=" ";genre=" ";
}

Employe::Employe(int id_employe,QString nom,QString prenom,QString poste,int num,QString password,QString genre)

{
    this->id_employe=id_employe;
    this->nom=nom;
    this->prenom = prenom;
    this->poste = poste;
    this->num=num;
    this->password=password;
    this->genre=genre;

}
int Employe::getid_employe(){return id_employe;}
int Employe::getnum(){return num;}
QString Employe:: getnom(){return nom;}
QString Employe::getprenom(){return prenom;}
QString Employe::getposte(){return poste;}
QString Employe::getpassword(){return password;}
QString Employe::getgenre(){return genre;}
void Employe::setid_employe(int id_employe){this->id_employe=id_employe;}
void Employe::setnom(QString nom){this->nom=nom;}
void Employe::setprenom(QString prenom){this->prenom=prenom;}
void Employe::setposte(QString poste){this->poste=poste;}
void Employe::setnum(int num){this->num=num;}
void Employe::setpassword(QString password){this->password=password;}
void Employe::setgenre(QString genre){this->genre=genre;}
bool Employe::ajouter()
{

      QSqlQuery query;
      QString id_employe_string=QString::number(id_employe);
      QString num_string=QString::number(num);
      query.prepare("INSERT INTO EMPLOYES (id_employe, nom, prenom,poste,num,password,genre) "
                    "VALUES (:id_employe, :nom, :prenom, :poste, :num, :password, :genre)");
      query.bindValue(0, id_employe_string);
      query.bindValue(1, nom);
      query.bindValue(2, prenom);
      query.bindValue(3, poste);
      query.bindValue(4, num_string);
      query.bindValue(5, password);
      query.bindValue(6, genre);

      query.exec();

      return query.exec();
}
bool Employe::supprimer(int id_employe)
{
    QSqlQuery query;
          QString res=QString::number(id_employe);

          query.prepare(" Delete from EMPLOYES where id_employe=:id_employe");
          query.bindValue(0, res);

         return  query.exec();
}
QSqlQueryModel* Employe::afficher()
{
              QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM EMPLOYES");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_employe"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("poste"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("num"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("password"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("genre"));
    return model;
}


QSqlQueryModel *Employe::rechercher(const QString &E)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from EMPLOYES where (NOM LIKE '"+E+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("poste"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("num"));

    return model;


}

QSqlQueryModel *Employe::Trier_em(QString croissance,QString critere)
{
    QSqlQueryModel *modal=new QSqlQueryModel();

    if(critere == "id_employe" && croissance == "ASC")
        modal->setQuery("select * from EMPLOYES order by id_employe ASC ");
    else if(critere == "id_employe" && croissance == "DESC")
        modal->setQuery("select * from EMPLOYES order by id_employe DESC ");

    else if(critere == "nom" && croissance == "ASC")
        modal->setQuery("select * from EMPLOYES order by nom ASC ");
    else if(critere == "nom" && croissance == "DESC")
        modal->setQuery("select * from EMPLOYES order by nom DESC ");

    else if(critere == "prenom" && croissance == "ASC")
        modal->setQuery("select * from EMPLOYES order by prenom ASC ");
    else if(critere == "prenom" && croissance == "DESC")
        modal->setQuery("select * from EMPLOYES order by prenom DESC ");

    else if(critere == "poste" && croissance == "ASC")
        modal->setQuery("select * from EMPLOYES order by poste ASC ");
    else if(critere == "poste" && croissance == "DESC")
        modal->setQuery("select * from EMPLOYES order by poste DESC ");

    else if(critere == "num" && croissance == "ASC")
        modal->setQuery("select * from EMPLOYES order by num ASC ");
    else if(critere == "num" && croissance == "DESC")
        modal->setQuery("select * from EMPLOYES order by num DESC ");

    else if(critere == "prenom" && croissance == "")
        modal->setQuery("select * from EMPLOYES order by prenom");
    else if(critere == "prenom" && croissance == "")
        modal->setQuery("select * from EMPLOYES order by prenom");

    else if(critere == "num" && croissance == "")
        modal->setQuery("select * from EMPLOYES order by num");
    else if(critere == "num" && croissance == "")
        modal->setQuery("select * from EMPLOYES order by num");

    else if(critere == "poste" && croissance == "")
        modal->setQuery("select * from EMPLOYES order by poste");
    else if(critere == "poste" && croissance == "")
        modal->setQuery("select * from EMPLOYES order by poste");

    else if(critere == "id_employe" && croissance == "")
        modal->setQuery("select * from EMPLOYES order by id_employe");
    else if(critere == "id_employe" && croissance == "")
        modal->setQuery("select * from EMPLOYES order by id_employe");

    else if(critere == "nom" && croissance == "")
        modal->setQuery("select * from EMPLOYES order by nom");
    else if(critere == "nom" && croissance == "")
        modal->setQuery("select * from EMPLOYES order by nom");

    else if(critere == "prenom" && croissance == "")
        modal->setQuery("select * from EMPLOYES order by prenom");
    else if(critere == "prenom" && croissance == "")
        modal->setQuery("select * from EMPLOYES order by prenom");

    return  modal;
}



QChartView *Employe::stat_genre()
  {
      int m=0;
      int f=0;


      QSqlQuery query;
      query.prepare("select * from EMPLOYES where GENRE='male'");
      query.exec();

      while(query.next())
          m++;

      query.prepare("select * from EMPLOYES where GENRE='femelle'");
      query.exec();

      while(query.next())
          f++;



      qDebug() << m<< f ;

      QPieSeries *series = new QPieSeries();
          series->append("male", m);
          series->append("femelle", f);


          QPieSlice *slice = series->slices().at(0);
          slice->setExploded(true);
          slice->setColor("#4C6293");
          slice->setLabel("male "+QString("%1%").arg(100*slice->percentage(),1,'f',1));
          QPieSlice *slice2 = series->slices().at(1);
          slice2->setColor("#E4F0FF");
          slice2->setLabel("femelle "+QString("%1%").arg(100*slice2->percentage(),1,'f',1));


          QChart *chart = new QChart();
          chart->addSeries(series);
          chart->setTitle("Statistique du genre");


          series->setLabelsVisible();

          QChartView *chartView = new QChartView(chart);
          chartView->setRenderHint(QPainter::Antialiasing);
          chartView->chart()->setAnimationOptions(QChart::AllAnimations);
          chartView->chart()->legend()->hide();
          chartView->resize(1000,500);
          return chartView;
}

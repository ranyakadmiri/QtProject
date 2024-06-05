#include "evenement.h"
#include <QIntValidator>
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include <QDate>
#include <QBarSet>
//Constructeur
Evenement::Evenement()
{
NumEvent=0;type="";nbinvit=0;heure="";duree=0;lieu="";
}
Evenement::Evenement(int NumEvent,QString type,int nbinvit,QDate date,QString heure,int duree,QString lieu)
{
    this->NumEvent=NumEvent;
    this->type=type;
    this->nbinvit=nbinvit;
    this->date=date;
    this->heure=heure;
    this->duree=duree;
    this->lieu=lieu;

}
//getters
int Evenement::getNumEvent(){return NumEvent;}
QString Evenement::gettype(){return type;}
int Evenement::getnbinvit(){return nbinvit;}
QDate Evenement::getdate(){return date;}
QString Evenement::getheure(){return heure;}
int Evenement::getduree(){return duree;}
QString Evenement::getlieu(){return lieu;}
//Setters
void Evenement::setNumEvent(int NumEvent) { this->NumEvent=NumEvent; }
void Evenement::settype(QString type){ this->type=type;}
void Evenement::setnbinvit(int nbinvit){this->nbinvit=nbinvit;}
void Evenement::setdate(QDate date){ this->date=date;}
void Evenement::setheure(QString heure){ this->heure=heure;}
void Evenement::setduree(int duree){this->duree=duree;}
void Evenement::setlieu(QString lieu){this->lieu=lieu;}

//////////////////////CRUD//////////////////////////////

//Fonction Ajouter
bool Evenement::ajouter()
{
    QSqlQuery query;
    QString NumEvent1=QString::number(NumEvent);
      QString nbinvit1=QString::number(nbinvit);
        QString duree_string=QString::number(duree);
        query.prepare("INSERT INTO EVENEMENT (NUMEVENT,TYPE,NBINVIT,JOUR,HEURE,DUREE,LIEU) "
                      "VALUES (:numevent, :type, :nbinvit, :jour, :heure, :duree, :lieu)");


          query.bindValue(":numevent", NumEvent1);
          query.bindValue(":type",type);
          query.bindValue(":nbinvit", nbinvit1);
          query.bindValue(":jour", date);
          query.bindValue(":heure",heure);
          query.bindValue(":duree",duree_string);
          query.bindValue(":lieu", lieu);


          return query.exec();



}
//Fonction Supprimer
bool Evenement::supprimer(int NumEvent)
{QSqlQuery query;
    QString res=QString::number(NumEvent);
    query.prepare("DELETE FROM EVENEMENT where numevent=:res");
    query.bindValue(0,res);
      return query.exec();

}
//Fonction Afficher
QSqlQueryModel *Evenement::afficher(){

    QSqlQueryModel * model=new QSqlQueryModel();
  model->setQuery("SELECT* FROM EVENEMENT");
  model->setHeaderData(0,Qt::Horizontal, QObject::tr("numevent"));
  model->setHeaderData(1,Qt::Horizontal, QObject::tr("type"));
  model->setHeaderData(2,Qt::Horizontal, QObject::tr("nbinvit"));
  model->setHeaderData(3,Qt::Horizontal, QObject::tr("jour"));
  model->setHeaderData(4,Qt::Horizontal, QObject::tr("heure"));
  model->setHeaderData(5,Qt::Horizontal, QObject::tr("duree"));
  model->setHeaderData(6,Qt::Horizontal, QObject::tr("lieu"));
    return model;
  }

//Fonction Modifier
bool Evenement::modifier()
 {
    QSqlQuery query;

    QString NumEvent1=QString::number(NumEvent);
      QString nbinvit1=QString::number(nbinvit);
        QString duree_string=QString::number(duree);
        query.prepare("UPDATE EVENEMENT set  NUMEVENT=:numevent, TYPE=:type, NBINVIT=:nbinvit , JOUR=:jour,HEURE=:heure,DUREE=:duree,LIEU=:lieu WHERE NUMEVENT=:numevent ");
        query.bindValue(":numevent", NumEvent1);
        query.bindValue(":type",type);
        query.bindValue(":nbinvit", nbinvit1);
        query.bindValue(":jour", date);
        query.bindValue(":heure",heure);
        query.bindValue(":duree",duree_string);
        query.bindValue(":lieu", lieu);
        return query.exec();

 }
/////////////////////////METIERS//////////////////////
/// \brief Evenement::rechercher
/// \param NumEvent
/// \return
/////Fonction Rechercher
QSqlQueryModel* Evenement::rechercher(int NumEvent)
{

    QString res=QString::number( NumEvent);
    QSqlQueryModel* model = new QSqlQueryModel();

     model->setQuery("SELECT * FROM EVENEMENT WHERE NUMEVENT like '%"+res+"%'  ");

   return model;
}

//Fonction Rechercherlieu
QSqlQueryModel* Evenement::rechercherlieu(QString lieu)
{


    QSqlQueryModel* model = new QSqlQueryModel();

     model->setQuery("SELECT * FROM EVENEMENT WHERE LIEU like '%"+lieu+"%'  ");

   return model;
}
//Fonction Recherchertype
QSqlQueryModel* Evenement::recherchertype(QString type)
{


    QSqlQueryModel* model = new QSqlQueryModel();

     model->setQuery("SELECT * FROM EVENEMENT WHERE TYPE like '%"+type+"%'  ");

   return model;
}

//Fonction Trier
QSqlQueryModel* Evenement::Trier(QString croissance,QString critere)
{
    QSqlQueryModel *modal=new QSqlQueryModel();

    if(critere == "NumEvent" && croissance == "ASC")
        modal->setQuery("select * from EVENEMENT order by NUMEVENT ASC ");
    else if(critere == "NumEvent" && croissance == "DESC")
        modal->setQuery("select * from EVENEMENT order by NUMEVENT  DESC ");

    else if(critere == "lieu" && croissance == "ASC")
        modal->setQuery("select * from EVENEMENT order by LIEU ASC ");
    else if(critere == "lieu" && croissance == "DESC")
        modal->setQuery("select * from EVENEMENT order by LIEU DESC ");

    else if(critere == "type" && croissance == "ASC")
        modal->setQuery("select * from EVENEMENT order by TYPE ASC ");
    else if(critere == "type" && croissance == "DESC")
        modal->setQuery("select * from EVENEMENT order by TYPE DESC ");

    else if(critere == "nbinvit" && croissance == "ASC")
        modal->setQuery("select * from EVENEMENT order by NBINVIT ASC ");
    else if(critere == "nbinvit" && croissance == "DESC")
        modal->setQuery("select * from EVENEMENT order by NBINVIT DESC ");

    return  modal;
}




//Fonction statistique



QChartView *Evenement::stat_type()
{
    int ceremonie=0;
    int festival=0;
    int marriage=0;
    int conference=0;

    QSqlQuery query;
    query.prepare("select * from EVENEMENT WHERE TYPE='ceremonie'");
    query.exec();

    while(query.next())
        ceremonie++;

    query.prepare("select * from EVENEMENT WHERE TYPE='festival'");
    query.exec();

    while(query.next())
       festival++;

    query.prepare("select * from EVENEMENT WHERE TYPE='marriage'");
    query.exec();

    while(query.next())
        marriage++;
    query.prepare("select * from EVENEMENT WHERE TYPE='conference'");
    query.exec();

    while(query.next())
        conference++;

    qDebug() << ceremonie << festival << marriage << conference;

    QPieSeries *series = new QPieSeries();
        series->append("ceremonie",ceremonie);
        series->append("festival", festival);
        series->append("marriage", marriage);
        series->append("conference", conference);

        QPieSlice *slice = series->slices().at(0);
        slice->setExploded(true);
        slice->setColor("#f55d11");
        QPieSlice *slice2 = series->slices().at(1);
        slice2->setColor("#ff8b52");
       QPieSlice *slice3 = series->slices().at(2);
        slice3->setColor("#e6a88a");
        QPieSlice *slice4 = series->slices().at(3);
        slice4->setColor("#4360f0");

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistique des categories");

        series->setLabelsVisible();

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
chartView->chart()->setAnimationOptions(QChart::AllAnimations);
chartView->chart()->legend()->hide();
        return chartView;



}

QChartView *Evenement::stat_date()
{


    QSqlQuery query;
    int g1=0;
    int g2=0;
    int g3=0;


    query.prepare("select JOUR from EVENEMENT");
    if(query.exec())
    {
        while(query.next())
        {
            QString dates =query.value(0).toString();
            QDate date = QDate::fromString(dates,"dd MM yyyy");
            dates = date.toString("MM");
            int month = dates.toInt();

            if(((month) >=01) && ((month) <= 10) )
            g1++;
            if(((month) >=11) && ((month) <= 20) )
            g2++;
            if(((month) >= 21) && ((month) <=31) )
            g3++;
        }

    }

    QPieSeries *series = new QPieSeries();
        series->append("premier trimestre",g1);
        series->append("deuxieme trimestre",g2);
        series->append("troisieme trimestre",g3);

        QPieSlice *slice = series->slices().at(0);
        slice->setExploded(true);
        slice->setColor("#092cdb");
        QPieSlice *slice2 = series->slices().at(1);
        slice2->setColor("#4360f0");
        QPieSlice *slice3 = series->slices().at(2);
        slice3->setColor("#303a6e");


        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistique des mois les plus mouvementés");

        series->setLabelsVisible();

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
chartView->chart()->setAnimationOptions(QChart::AllAnimations);
chartView->chart()->legend()->hide();
        return chartView;

}
QChartView *Evenement::stat_date_type()
{

    QSqlQuery query;

    //tri par trimestre
    int c1=0;
    int c2=0;
    int c3=0;

    int f1=0;
    int f2=0;
    int f3=0;

    int m1=0;
    int m2=0;
    int m3=0;



    query.prepare("select JOUR from EVENEMENT");
    if(query.exec())
    {
        while(query.next())
        {
            QString dates =query.value(0).toString();
            QDate date = QDate::fromString(dates,"dd MM yyyy");
            dates = date.toString("MM");
            int month = dates.toInt();

            if(((month) >=01) && ((month) <= 10) )
            {
                query.prepare("select * from EVENEMENT WHERE TYPE='ceremonie'");
                query.exec();

                while(query.next())
                    c1++;

                query.prepare("select * from EVENEMENT WHERE TYPE='festival'");
                query.exec();

                while(query.next())
                   f1++;

                query.prepare("select * from EVENEMENT WHERE TYPE='marriage'");
                query.exec();

                while(query.next())
                    m1++;
            }

            if(((month) >=11) && ((month) <= 20) )
            {
                query.prepare("select * from EVENEMENT WHERE TYPE='ceremonie'");
                query.exec();

                while(query.next())
                    c2++;

                query.prepare("select * from EVENEMENT WHERE TYPE='festival'");
                query.exec();

                while(query.next())
                   f2++;

                query.prepare("select * from EVENEMENT WHERE TYPE='marriage'");
                query.exec();

                while(query.next())
                    m2++;
            }
            if(((month) >= 21) && ((month) <=31) )
            {
                query.prepare("select * from EVENEMENT WHERE TYPE='ceremonie'");
                query.exec();

                while(query.next())
                    c3++;

                query.prepare("select * from EVENEMENT WHERE TYPE='festival'");
                query.exec();

                while(query.next())
                   f3++;

                query.prepare("select * from EVENEMENT WHERE TYPE='marriage'");
                query.exec();

                while(query.next())
                    m3++;

            }
        }

    }


    QBarSet *set1 = new QBarSet("ceremonie");
    QBarSet *set2 = new QBarSet("Festival");
    QBarSet *set3 = new QBarSet("marriage");

    *set1 << c1 << c2 << c3;
    *set2 << f1 << f2 << f3;
    *set3 << m1 << m2 << m3;

    QBarSeries *series = new QBarSeries();

    series->append(set1);
    series->append(set2);
    series->append(set3);

    QChart *chart = new QChart();
    chart->addSeries(series);

    chart->setTitle("Statistique date et type");
    QStringList cate;
    cate << "1er trimestre" << "2ème trimestre" << "3 ème trimestre";

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(cate);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
chartView->chart()->setAnimationOptions(QChart::AllAnimations);
    return chartView;
}

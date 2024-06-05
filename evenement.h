#ifndef EVENEMENT_H
#define EVENEMENT_H
#include<QString>
#include<QSqlQueryModel>
#include <QDate>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QPieSlice>
class Evenement
{
public:
    Evenement();
    Evenement(int,QString,int,QDate,QString,int,QString);
    int getNumEvent();
    QString gettype();
    int getnbinvit();
    QDate getdate();
    QString getheure();
    int getduree();
    QString getlieu();
     void setNumEvent(int);
   void settype(QString);
   void setnbinvit(int);
  void setdate(QDate);
   void setheure(QString);
   void setduree(int);
  void setlieu(QString);
  bool ajouter();
  bool supprimer(int);
  bool modifier();
QSqlQueryModel* afficher();
QSqlQueryModel* rechercher(int);
QSqlQueryModel* rechercherlieu(QString);
QSqlQueryModel* recherchertype(QString);

QSqlQueryModel* Trier(QString ,QString);

QChartView *stat_type();
QChartView *stat_date();
QChartView *stat_date_type();


private:
    int NumEvent,nbinvit,duree;
    QString lieu,heure,type;
    QDate date;



};

#endif // EVENEMENT_H

#ifndef EMPLOYE_H
#define EMPLOYE_H

#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QMessageBox>
#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QString>
#include <QChart>
#include <QtCharts>
#include <QIntValidator>
#include <QPieSeries>
#include <QChartView>
#include <QGraphicsView>
class Employe
{
public:
    Employe ();
    Employe(int,QString,QString,QString,int,QString,QString);
    int getid_employe();
    QString getnom();
    QString getprenom();
    QString getposte();
    int getnum();
    QString getpassword();
    QString getgenre();

    void setid_employe(int);
    void setnom(QString);
    void setprenom(QString);
    void setposte(QString);
    void setnum(int);
    void setpassword(QString);
    void setgenre(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    QSqlQueryModel *rechercher(const QString &arg1);
    QSqlQueryModel *Trier_em(QString croissance,QString critere);
    QChartView *stat_genre();
private:
    int id_employe,num;
    QString nom,prenom,genre,poste,password;

};

#endif // EMPLOYE_H

#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>


class Client
{
private:
    QString cin;
    QString nom;
    QString prenom;
    QString adresse;
    QString tel;


public:
    Client();

    Client(QString, QString, QString, QString, QString);

    bool ajouter_Cl();

    QSqlQueryModel * afficher_Cl();

    bool supprimer_Cl(QString);

    bool modifier_Cl(QString,QString,QString,QString,QString);

    QSqlQueryModel* recherche(QString);

    QSqlQueryModel* tri();


};
#endif //

#ifndef PARTENAIRES_H
#define PARTENAIRES_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class partenaires
{
    QString nomentr ,service,nom,prenom,email;
    int id,numeros;
public:
    partenaires(){}
    partenaires(int,QString,QString,QString,QString,QString,int);

    QString getnom(){return nom;}
    int getid(){return id;}
    QString getprenom(){return prenom;}
    QString getnomentr(){return nomentr;}
    QString getemail(){return email;}
    QString getservice(){return service;}
    int getnum(){return numeros;}


    void setnom(QString n){ nom=n;}
    void setprenom(QString n){ prenom=n;}
    void setnomentr(QString n){ nomentr=n;}
    void setid(int n){ id=n;}
    void setservice(QString n){ service=n;}
    void setemail(QString n){ email=n;}
    void setnum(int n){ numeros=n;}
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher1();
    bool supprimer(int id);
    bool modifier();
    QSqlQueryModel *recherche(QString n);
    QSqlQueryModel* trier(QString ,QString);
};

#endif // PARTENAIRES_H

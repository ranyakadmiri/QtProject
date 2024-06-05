#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"evenement.h"
#include "qrcode.h"
#include "client.h"
#include "employe.h"
#include "smtp.h"
#include "arduino.h"
#include "exportexelobjet.h"
#include<QString>
#include <iostream>
#include <ostream>
#include <QMessageBox>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QSqlError>
#include <QTextStream>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <fstream>
#include <windows.h>
#include <QPixmap>
#include <QPainter>
#include <QtDebug>
#include "connection.h"
#include <QLabel>
#include <QMovie>
#include <QDebug>
#include <QRegExpValidator>
#include <QPdfWriter>
#include <QFile>
#include <QCoreApplication>
#include <QLineEdit>
#include "windows.h"
#include <QTimer>
#include <QQmlEngine>
#include <QQuickItem>
#include <QPdfWriter>
#include <QDir>
#include <QFileDialog>
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include <QtCharts>
#include <QtCharts/QBarSet>
#include <QtSql>
#include<QSystemTrayIcon>
#include <QRegExp>
#include <QDate>
#include <QDesktopServices>
#include <QUrl>
#include <QApplication>
#include <QIntValidator>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrinterInfo>
#include <QGraphicsView>
#include <QTabWidget>
#include <QProcess>
#include <QUrl>
#include <QDesktopServices>
#include <QPieSlice>
#include <QPieSeries>
#include<QValidator>
#include <QFile>
#include<QSqlError>
#include<QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //init event
      ui->leNumEvent_3->setValidator(new QIntValidator(0,9999,this));
    ui->tabEvenement_4->setModel(EV.afficher());
  EV.stat_type()->setParent(ui->stat_3);
//init client
  ui->tableView_Res->setModel(tmpres.afficher_Cl());


   ui->le_cin->setValidator( new QIntValidator(0, 99999999, this));
   ui->le_cin_2->setValidator( new QIntValidator(0, 999999999, this));
   // ui->le_nom->setValidator( new QIntValidator(0, 999999999, this));
    //ui->le_nom_2->setValidator( new QIntValidator(0, 999999999, this));
   // ui->le_prenom->setValidator( new QIntValidator(0, 999999999, this));
    //ui->le_prenom_2->setValidator( new QIntValidator(0, 999999999, this));

    //  ui->le_adresse->setValidator( new QIntValidator(0, 999999999, this));
    //  ui->le_adresse_2->setValidator( new QIntValidator(0, 999999999, this));

        ui->le_tel->setValidator( new QIntValidator(0, 999999999, this));
        ui->le_tel_2->setValidator( new QIntValidator(0, 999999999, this));

  //init employe
        ui->id_employe->setValidator(new QIntValidator(0,9999,this));
        ui->num_4->setValidator(new QIntValidator(0,99999999,this));
        ui->tab_employe->setModel(E.afficher());
  //init lieux
        ui->le_id->setValidator(new QIntValidator(100, 9999999, this));
      ui->tab_afficher->setModel(l.afficher());

      int ret =A.connect_arduino();//lancer la connection to arduino
           switch (ret) {

           case(0):qDebug()<<"arduino is available and connect to : "<<A.getarduino_port_name();
               break;
           case(1):qDebug()<<"arduino is available and not  connect to : "<<A.getarduino_port_name();
               break;
           case(-1):qDebug()<<"arduino is not available ";
               break;

           }
           QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(updatelabel()));
             QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
  //init partenaire
           ui->tableau->setModel(p.afficher());
                      ui->tablerech->setModel(p.afficher1());

                      connect(ui->sendbtn, SIGNAL(clicked()),this, SLOT(sendMail()));
                      connect(ui->browsebtn, SIGNAL(clicked()), this, SLOT(browse()));

                      //maps
                      QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                                         QCoreApplication::organizationName(), QCoreApplication::applicationName());

                      ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://accounts.google.com/v3/signin/identifier?dsh=S-855206879%3A1669964938157820&continue=https%3A%2F%2Fmail.google.com%2Fmail%2F&rip=1&sacu=1&service=mail&flowName=GlifWebSignIn&flowEntry=ServiceLogin&ifkv=ARgdvAsbUlfuPhNB15tn6ODRKk5QfH2o2DOJ_-y_PVqfpqV_tfdDWg_DVE2Nddd3Kh7_5PZexuee");
                      //maps


                      ui->axWidget->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listWidget_itemClicked()
{

    QString selectedvalue= ui->listWidget->currentItem()->text();

    if (selectedvalue == "Acceuil")
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
    if (selectedvalue == "gestion evenements")
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    if (selectedvalue == "gestion employees")
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
    if (selectedvalue == "gestion clients")
    {
        ui->stackedWidget->setCurrentIndex(3);
    }
    if (selectedvalue == "gestion lieux")
    {
        ui->stackedWidget->setCurrentIndex(4);
    }
    if (selectedvalue == "gestion partenaires")
    {
        ui->stackedWidget->setCurrentIndex(5);
    }

}
/////////////////////////////////////event/////////////////////////////////
void MainWindow::on_pb_ajouter_3_clicked()
{  int NumEvent=ui->leNumEvent_3->text().toInt();


   QString type=ui->letype_3->text();
   int  nbinvit=ui->lenbinvit_3->text().toInt();
    QDate date=ui->dateEdit_3->date();
     QString heure=ui->leheure_3->text();
    int duree=ui->leduree_3->text().toInt();
      QString lieu=ui->lelieu_3->text();
      Evenement EV(NumEvent,type,nbinvit,date,heure,duree,lieu);
      QMessageBox msgbox;
      bool test=EV.ajouter();
      if (test){   ui->tabEvenement_4->setModel(EV.afficher());
           EV.stat_type()->setParent(ui->stat_3);
          msgbox.setText("ajout avec succes");

      }
      else msgbox.setText("echec d'ajout");
      msgbox.exec();
}
void MainWindow::on_tabEvenement_4_clicked(const QModelIndex &index)
{
   QString select=ui->tabEvenement_4->model()->data(index).toString();
   QSqlQuery qry;


   qry.prepare("select * from EVENEMENT where NUMEVENT LIKE '"+select+"'");

   if(qry.exec())
   {
       while(qry.next())
       {
           //Remplir tous les champs par les données concernées

           ui->leNumEvent_3->setText(qry.value(0).toString());
           ui->letype_3->setText(qry.value(1).toString());
           ui->lenbinvit_3->setText(qry.value(2).toString());
           ui->ledate_3->setText(qry.value(3).toString());
           ui->leheure_3->setText(qry.value(4).toString());
           ui->leduree_3->setText(qry.value(5).toString());
           ui->lelieu_3->setText(qry.value(6).toString());
}
}
}
void MainWindow::on_mdf_3_clicked()
{
    int NumEvent=ui->leNumEvent_3->text().toInt();
    QString type=ui->letype_3->text();
       int  nbinvit=ui->lenbinvit_3->text().toInt();
        QDate date=ui->dateEdit_3->date();
         QString heure=ui->leheure_3->text();
        int duree=ui->leduree_3->text().toInt();
          QString lieu=ui->lelieu_3->text();
          Evenement EV(NumEvent,type,nbinvit,date,heure,duree,lieu);

          QMessageBox msgbox;
          bool test=EV.modifier();
          if (test){
              msgbox.setText("modif avec succes");

              ui->tabEvenement_4->setModel(EV.afficher());
                   EV.stat_type()->setParent(ui->stat_3);
          }
          else msgbox.setText("echec de modif");
          msgbox.exec();}

void MainWindow::on_pb_supprimer_3_clicked()
{
    int NumEvent=ui->lineEdit_8->text().toInt();
    bool test=EV.supprimer(NumEvent);
   if(test)
    {QMessageBox::information(nullptr,QObject::tr("OK"),
                              QObject::tr("suppression effectue\n click cancel to exit."),QMessageBox::Cancel);
     ui->tabEvenement_4->setModel(EV.afficher());
          EV.stat_type()->setParent(ui->stat_3);
    }
      else  {QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                      QObject::tr("suppression non effectue\n click cancel to exit."),QMessageBox::Cancel);}


}


void MainWindow::on_prechercher_4_clicked()
{
    int NumEvent=ui->rechercher_4->text().toInt();

         ui->tableView_4->setModel(EV.rechercher(NumEvent));


}




void MainWindow::on_recherchelieu_4_textChanged(const QString &arg1)
{
    QString lieu=ui->recherchelieu_4->text();

           ui->tableViewlieu_4->setModel(EV.rechercherlieu(arg1));
}



void MainWindow::on_comboBox_4_highlighted(const QString &arg1)
{

      Evenement e;
        QString type="";

        if(ui->radioButton_7->isChecked())
            type="ASC";
        else if(ui->radioButton_8->isChecked())
            type="DESC";

        if(arg1 != "Choisir")
            ui->tabletri_4->setModel(e.Trier(type,arg1));

        else  ui->tabletri_4->setModel(e.afficher());

    }

    //choisir radio button ascendant
    void MainWindow::on_radioButton_7_clicked()
    {
        Evenement e;
        QString type="";


        if(ui->radioButton_7->isChecked())
            type="ASC";
        else if(ui->radioButton_8->isChecked())
            type="DESC";

        if(ui->comboBox_4->currentText() != "Choisir")
            ui->tabletri_4->setModel(e.Trier(type,ui->comboBox_4->currentText()));

        else  ui->tabletri_4->setModel(e.afficher());
    }


    //choisir radio button descendant
    void MainWindow::on_radioButton_8_clicked()
    {
        Evenement e;
        QString type="";

        if(ui->radioButton_7->isChecked())
            type="ASC";
        else if(ui->radioButton_8->isChecked())
            type="DESC";

        if(ui->comboBox_4->currentText() != "Choisir")
            ui->tabletri_4->setModel(e.Trier(type,ui->comboBox_4->currentText()));


        else  ui->tabletri_4->setModel(e.afficher());
    }





    void MainWindow::on_recherchertype_4_textChanged(const QString &arg1)
    {
        QString type=ui->recherchelieu_4->text();

               ui->tableViewtype_4->setModel(EV.recherchertype(arg1));
    }




void MainWindow::on_pdf_3_clicked()
{

     QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
            if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
     QString strStream;
                    QTextStream out(&strStream);
                    const int rowCount = ui->tabEvenement_4->model()->rowCount();
                    const int columnCount =ui->tabEvenement_4->model()->columnCount();


                    out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("eleve")
                            <<  "</head>\n"
                            "<body bgcolor=#e2fdec link=#5000A0>\n"
                                "<h1  style='color:#1e114b'>>Liste des Evenements</h1>"

                                "<table border=1 cellspacing=0 cellpadding=2>\n";

                    // headers
                        out << "<thead><tr bgcolor=#f8fcd6>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tabEvenement_4->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tabEvenement_4->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";
                        // data table
                           for (int row = 0; row < rowCount; row++) {
                               out << "<tr>";
                               for (int column = 0; column < columnCount; column++) {
                                   if (!ui->tabEvenement_4->isColumnHidden(column)) {
                                       QString data = ui->tabEvenement_4->model()->data(ui->tabEvenement_4->model()->index(row, column)).toString().simplified();
                                       out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                   }
                               }
                               out << "</tr>\n";
                           }
                           out <<  "</table>\n"
                               "</body>\n"
                               "</html>\n";



            QTextDocument *document = new QTextDocument();
            document->setHtml(strStream);



            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fileName);
            document->print(&printer);

        }





//calendrier
void MainWindow::on_calendarWidget_3_selectionChanged()
{
    ui->dateEdit_7->setDate(ui->calendarWidget_3->selectedDate());

        QDate date=ui->dateEdit_7->date();

        /*QDate datet;
        datet=date;*/

    QSqlQueryModel * Mod=new  QSqlQueryModel();
        QSqlQuery qry;

        qry.prepare("select * from EVENEMENT ");

        if(qry.exec())
        {
            while(qry.next())
            {
                //Remplir tous les champs par les données concernées
    //datet=date;
    if(qry.value(3)==date)
    {
               ui->numevent_cal_3->setText(qry.value(0).toString());
                ui->type_cal_3->setText(qry.value(1).toString());
                ui->nbinvit_cal_3->setText(qry.value(2).toString());
                ui->date_cal_3->setText(qry.value(3).toString());
                ui->heure_cal_3->setText(qry.value(4).toString());
                ui->duree_cal_3->setText(qry.value(5).toString());
                ui->lieu_cal_3->setText(qry.value(6).toString());

                Mod->setQuery(qry);
                        ui->tabcal_3->setModel(Mod);

    }
    //fin if
    }//fin while
    }//fin if qry
    }//fin fnt



void MainWindow::on_qrcode_button_3_clicked()
{
    using namespace qrcodegen;

    ///////////////// data collecting ////////////////////////
    QTableView tabEvenement_4;
    QSqlQueryModel * Mod=new  QSqlQueryModel();
    QString value=ui->num_3->text();
           Connection c;

         QSqlQuery qry;




         qry.prepare("select * from EVENEMENT where NUMEVENT='"+value+"'");
         qry.exec();
         Mod->setQuery(qry);
         tabEvenement_4.setModel(Mod);


        /* QSqlQueryModel * model=new QSqlQueryModel();
       model->setQuery("SELECT* FROM EVENEMENT");*/

        QString NUMEVENT = tabEvenement_4.model()->data(tabEvenement_4.model()->index(0, 0)).toString().simplified();
        QString TYPE = tabEvenement_4.model()->data(tabEvenement_4.model()->index(0, 1)).toString().simplified();
        QString NBINVIT = tabEvenement_4.model()->data(tabEvenement_4.model()->index(0, 2)).toString().simplified();
        QString DATE = tabEvenement_4.model()->data(tabEvenement_4.model()->index(0, 3)).toString().simplified();
        QString HEURE = tabEvenement_4.model()->data(tabEvenement_4.model()->index(0, 4)).toString().simplified();
        QString DUREE = tabEvenement_4.model()->data(tabEvenement_4.model()->index(0, 5)).toString().simplified();
        QString LIEU = tabEvenement_4.model()->data(tabEvenement_4.model()->index(0, 6)).toString().simplified();



    QString text = NUMEVENT+"\n"+TYPE+"\n"+NBINVIT+"\n"+DATE+"\n"+HEURE+"\n"+DUREE+"\n"+LIEU+"\n";
      // Create the QR Code object
      QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );

      qint32 sz = qr.getSize();
      QImage im(sz,sz, QImage::Format_RGB32);
        QRgb black = qRgb( 191,112,105 );
        QRgb white = qRgb(255,255,255);
      for (int y = 0; y < sz; y++)
        for (int x = 0; x < sz; x++)
          im.setPixel(x,y,qr.getModule(x, y) ? black : white );
      ui->qraff_3->setPixmap( QPixmap::fromImage(im.scaled(200,200,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}
void MainWindow::update_label()
{QByteArray Myint =A.read_from_arduino();
      QString Myint1=QString (Myint);
  ui->arduinoline_3->setText(Myint1);
  //QString Myint1=ui->arduinoline->text();
     ui->arduinoline_3->setText(Myint1);
   QByteArray data=A.cherchercode(Myint1);
   ui->DATA_3->setText(data);

      if(data=="1")      {
          ui->label_msg_3->setText("unlocked");
       }
   else{ui->label_msg_3->setText("locked");
 qDebug()<<"data="<<data;

  }
}

/////////////////////////////////////Client////////////////////////////////////////
void MainWindow::on_pushButton_4_clicked()
{
    QString cin = ui->le_cin->text();
    QString nom=ui->le_nom->text();
    QString prenom = ui->le_prenom->text();
     QString adresse = ui->le_adresse->text();
      QString tel =  ui->le_tel->text();
      if(cin.size() == 8){

    Client c(cin,nom,prenom,adresse,tel);
    bool test=c.ajouter_Cl();

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ajouter"),
                          QObject::tr("client ajouté.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

    }
      }else{
          QMessageBox::critical(nullptr, QObject::tr("Ajouter"),
                            QObject::tr("Verifier Le CIN.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

      }

 ui->tableView_Res->setModel(tmpres.afficher_Cl());

 // historique
         QFile file("C:/Users/ranka/Documents/integration/historique.txt");
         if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
             return;
         QTextStream cout(&file);
         QString d_info = QDateTime::currentDateTime().toString();
         QString message2=d_info+" - Un client a été ajouté avec la référence "+cin+"\n";
         cout << message2;

}




void MainWindow::on_supp_clicked()
{
    QString cin =ui->tableView_Res->model()->index(ui->tableView_Res->currentIndex().row(),0).data().toString();
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Supprimer", "Etes vous sur de supprimer cette client ?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
          bool test=tmpres.supprimer_Cl(cin);
          if(test)
          {
              ui->tableView_Res->setModel(tmpres.afficher_Cl());
              QMessageBox::information(nullptr,"Suppression","client supprimé");

              QFile file("C:/Users/fares/Desktop/Projet_CL/historique.txt");
                      if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                          return;
                      QTextStream cout(&file);
                      QString d_info = QDateTime::currentDateTime().toString();
                      QString message2=d_info+" - Un client a été supprimée avec la référence "+cin+"\n";
                      cout << message2;
          }
      }

}

void MainWindow::on_xl_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en fichier Excel"), qApp->applicationDirPath (),
                                                                tr("Fichiers d'extension Excel (*.xls)"));
                if (fileName.isEmpty())
                    return;

                ExportExcelObject obj(fileName, "mydata", ui->tableView_Res);


                obj.addField(0, "cin", "char(20)");
                 obj.addField(2, "nom", "char(20)");
                obj.addField(1, "prenom", "char(20)");
                obj.addField(4, "adresse", "char(20)");
                obj.addField(3, "tel", "char(20)");



                int retVal = obj.export2Excel();

                if( retVal > 0)
                {
                    QMessageBox::information(this, tr("FAIS!"),
                                             QString(tr("%1 enregistrements exportés!")).arg(retVal)
                                             );
//HISTORIQUE
                    QFile file("C:/Users/ranka/Documents/integration/historique.txt");
                            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                                return;
                            QTextStream cout(&file);
                            QString d_info = QDateTime::currentDateTime().toString();
                            QString message2=d_info+" - Une fichier exel a été génerée !\n";
                            cout << message2;

                }
}

void MainWindow::on_search_textEdited(const QString &rech)
{
    ui->tableView_Res->setModel(tmpres.recherche(rech));


}

void MainWindow::on_tri_clicked()
{
    ui->tableView_Res->setModel(tmpres.tri());

}

void MainWindow::readfile(){
    QString filename="C:/Users/ranka/Documents/integration/historique.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "NO exist "<<filename;
    }else{
        qDebug() << filename<<" ...";
    }
    QString line;
    ui->Histo->clear();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            line = stream.readLine();
            ui->Histo->setText(ui->Histo->toPlainText()+line+"\n");
            qDebug() << "linea: "<<line;
        }
    }
    file.close();
}

void MainWindow::on_tabWidget_2_currentChanged(int index)
{
    readfile();

}

void MainWindow::on_pdf1_clicked()
{
    QString strStream;
            QTextStream out(&strStream);


    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }


    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);
    const int rowCount = ui->tableView_Res->model()->rowCount();
    const int columnCount = ui->tableView_Res->model()->columnCount();
    QString TT = QDate::currentDate().toString("yyyy/MM/dd");
    out <<"<html>\n"
          "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        << "<title>ERP - clients LIST<title>\n "
        << "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<h1 style=\"text-align: center;\"><strong> LISTE DES CLIENTS </strong></h1>"
        "<h5 style=\"text-align: center;\">Le : "+TT+"</h5>"
        "<br>\n"
        "<table style=\"text-align: center; font-size: 12;\" border=1>\n "
          "</br> </br>";
    // headers
    out << "<thead><tr bgcolor=#d6e5ff>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_Res->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView_Res->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView_Res->isColumnHidden(column)) {
                QString data =ui->tableView_Res->model()->data(ui->tableView_Res->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.print(&printer);


    QFile file("C:/Users/fares/Desktop/Projet_CL/historique.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                return;
            QTextStream cout(&file);
            QString d_info = QDateTime::currentDateTime().toString();
            QString message2=d_info+" - Une fichier PDF a été génerée !\n";
            cout << message2;



}



void MainWindow::on_le_date_userDateChanged(const QDate &date)
{

}

void MainWindow::on_le_nom_cursorPositionChanged(int arg1, int arg2)
{

}

void MainWindow::on_pushButton_5_clicked()
{

    QString cin = ui->le_cin_2->text();
    QString nom = ui->le_nom_2->text();
     QString prenom = ui->le_prenom_2->text();
     QString adresse = ui->le_adresse_2->text();
     QString tel = ui->le_tel_2->text();
    Client c;
    bool test=c.modifier_Cl(cin,nom,prenom,adresse,tel);

    if(test)
    {
        ui->tableView_Res->setModel(tmpres.afficher_Cl());
        QMessageBox::information(nullptr, QObject::tr("modifie un Client"),
                          QObject::tr("Client modifie.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

        QFile file("C:/Users/fares/Desktop/Projet_CL/historique.txt");
                if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                    return;
                QTextStream cout(&file);
                QString d_info = QDateTime::currentDateTime().toString();
                QString message2=d_info+" - Un client a été modifié avec la référence "+cin+"\n";
                cout << message2;
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("non modifie"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }




}


/**STATS**/

void MainWindow::renderChart1() {
  if(ui->chart1->takeAt(0)) {
    delete ui->chart1->takeAt(0);
  }
  QBarSet *set0 = new QBarSet("Ooreedo");    //QBARSET TYPE DE CHARTS
  QBarSet *set1 = new QBarSet("TTelecom");
  QBarSet *set2 = new QBarSet("Orange");

  *set0 << 4;     /******* 4 number Ooreedo********/
  *set1 << 2;     /******* 2 number TT  ********/

  *set2 << 6;   /******* 6 number ORANGE********/
  //![1]

  //![2]
  QBarSeries *series = new QBarSeries();
  series->append(set0);
  series->append(set1);
  series->append(set2);

  //![2]

  //![3]
  QChart *chart = new QChart();
  chart->addSeries(series);
  chart->setTitle("Number Charts based on Operator");
  chart->setAnimationOptions(QChart::SeriesAnimations);
  //![3]

  //![4]
  QStringList categories;
  categories << "Operator'Type";
  QBarCategoryAxis *axisX = new QBarCategoryAxis();
  axisX->append(categories);
  chart->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);

  QValueAxis *axisY = new QValueAxis();
  chart->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);
  //![4]

  //![5]
  chart->legend()->setVisible(true);
  chart->legend()->setAlignment(Qt::AlignBottom);
  //![5]

  //![6]
  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);
  if(ui->chart1->takeAt(0)) {
    delete ui->chart1->takeAt(0);
  }
  ui->chart1->addWidget(chartView);
}
void MainWindow::on_tri_2_clicked()
{
     renderChart1();
}

////////////////////////////employe/////////////////////////////
void MainWindow::on_pb_ajouter1_clicked()
{
    int id_employe=ui->id_employe->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString poste=ui->poste->text();
    int num=ui->num_4->text().toInt();
    QString password=ui->password->text();
    QString genre=ui->genre->text();

    Employe E(id_employe,nom,prenom,poste,num,password,genre);

    bool test=E.ajouter();
        QMessageBox msgBox;
        if (test)
    {
            ui->tab_employe->setModel(E.afficher());
            msgBox.setText("ajout avec succes");

            ui->id_employe->clear();
            ui->nom->clear();
            ui->prenom->clear();
            ui->poste->clear();
            ui->num_4->clear();
            ui->password->clear();
            ui->genre->clear();
    }
    else     ui->tab_employe->setModel(E.afficher());
            msgBox.setText("ajout avec succes");
            ui->id_employe->clear();
            ui->nom->clear();
            ui->prenom->clear();
            ui->poste->clear();
            ui->num_4->clear();
            ui->password->clear();
            ui->genre->clear();
        msgBox.exec();
}

void MainWindow::on_pb_supprimer1_clicked()
{
    ui->id_employe->setValidator(new QIntValidator(0,9999,this));
    Employe E1;E1.setid_employe(ui->le_id_supp->text().toInt());
    bool test=E1.supprimer(E1.getid_employe());
    QMessageBox msgBox;

    if(test)
       {

        ui->tab_employe->setModel(E.afficher());
        msgBox.setText("suppression avec succes.");

        ui->le_id_supp->clear();


    }
    else
        msgBox.setText("echec de suppression.");
    msgBox.exec();
}

void MainWindow::on_tab_employe_activated(const QModelIndex &index)
{
 QString val=ui->tab_employe->model()->data(index).toString();
 QSqlQuery qry;
 qry.prepare("select * from EMPLOYES where id_employe='"+val+"'");
 if(qry.exec())
 {
  while(qry.next())
  {
   ui->id_employe->setText(qry.value(0).toString());
   ui->nom->setText(qry.value(1).toString());
   ui->prenom->setText(qry.value(2).toString());
   ui->poste->setText(qry.value(3).toString());
   ui->num_4->setText(qry.value(4).toString());
   ui->password->setText(qry.value(5).toString());
   ui->genre->setText(qry.value(6).toString());
  }
 }
 else
 {
  QMessageBox::critical(this,tr("error::"),qry.lastError().text());
 }
}



void MainWindow::on_pb_modifier_clicked()
{
        QString id_employe=ui->id_employe->text();
        QString nom=ui->nom->text();
        QString prenom=ui->prenom->text();
        QString poste=ui->poste->text();
        int num=ui->num_4->text().toInt();
        QString password=ui->password->text();
        //QString res1 = QString::number(id_employe);
        QString res = QString::number(num);


        QSqlQuery quer;
        quer.prepare("update EMPLOYES set  id_employe='"+id_employe+"', nom='"+nom+"', prenom='"+prenom+"', poste='"+poste+"',num='"+res+"' where id_employe='"+id_employe+"'");
          if(quer.exec())
          {

              ui->tab_employe->setModel(E.afficher());
           QMessageBox::information(nullptr,QObject::tr("OK"),
                                    QObject::tr("modification effectué \n"
                                                "Click Cancel to exit."),QMessageBox::Cancel);

           ui->id_employe->clear();
           ui->nom->clear();
           ui->prenom->clear();
           ui->poste->clear();
           ui->num_4->clear();
           ui->password->clear();
          }
          else
              QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                    QObject::tr("modification non effectué \n"
                                                "Click Cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_lineEditRecherche_textChanged(const QString &)
{
    QString str=ui->lineEditRecherche->text();
    ui->tab_employe->setModel(E.rechercher(str));
}

void MainWindow::on_comboBox1_highlighted(const QString &arg1)
{
    Employe E;
        QString type="";

        if(ui->radioButton_5->isChecked())
            type="ASC";
        else if(ui->radioButton_6->isChecked())
            type="DESC";

        if(arg1 != "Choisir")
             ui->tab_employe->setModel(E.Trier_em(type,arg1));

        else  ui->tab_employe->setModel(E.afficher());
}

void MainWindow::on_radioButton_5_clicked()
{
    Employe E;
        QString type="";

        if(ui->radioButton_5->isChecked())
            type="ASC";
        else if(ui->radioButton_6->isChecked())
            type="DESC";

        if(ui->comboBox1->currentText() != "Choisir")
             ui->tab_employe->setModel(E.Trier_em(type,ui->comboBox1->currentText()));

        else  ui->tab_employe->setModel(E.afficher());
}

void MainWindow::on_radioButton_6_clicked()
{
    Employe E;
        QString type="";

        if(ui->radioButton_5->isChecked())
            type="ASC";
        else if(ui->radioButton_6->isChecked())
            type="DESC";

        if(ui->comboBox1->currentText() != "Choisir")
             ui->tab_employe->setModel(E.Trier_em(type,ui->comboBox1->currentText()));

        else  ui->tab_employe->setModel(E.afficher());
}





void MainWindow::on_pdf2_clicked()
{
        QString strStream;
          QTextStream out(&strStream);

       const int rowCount = ui->tab_employe->model()->rowCount();
       const int columnCount = ui->tab_employe->model()->columnCount();
       out <<  "<html>\n"
               "<head>\n"
       "<meta Content=\"Text/html; charset=Windows-1251\">\n"
       <<  QString("<title>%1</title>\n").arg("strTitle")
       <<  "</head>\n"
      "<body bgcolor=#ffffff link=#5000A0>\n"

      //     "<align='right'> " << datefich << "</align>"
         "<center> <H1>Liste Des Employes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                 // headers
        out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
       for (int column = 0; column < columnCount; column++)
       if (!ui->tab_employe->isColumnHidden(column))
           out << QString("<th>%1</th>").arg(ui->tab_employe->model()->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";

                                               // data table
               for (int row = 0; row < rowCount; row++) {
                out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                  for (int column = 0; column < columnCount; column++) {
                if (!ui->tab_employe->isColumnHidden(column)) {
         QString data = ui->tab_employe->model()->data(ui->tab_employe->model()->index(row, column)).toString().simplified();
         out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                                       }
                                                   }
                          out << "</tr>\n";
                                               }
                                out <<  "</table> </center>\n"
                                        "</body>\n"
                                      "</html>\n";
          QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                        if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                       QPrinter printer (QPrinter::PrinterResolution);
                        printer.setOutputFormat(QPrinter::PdfFormat);
                       printer.setPaperSize(QPrinter::A4);
                      printer.setOutputFileName(fileName);

                       QTextDocument doc;
                        doc.setHtml(strStream);
                        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                        doc.print(&printer);

}




void MainWindow::on_stats_clicked()
{
    QChartView *chartView = E.stat_genre();
    chartView->show();
}


   void MainWindow::on_pushButton_login_clicked()
{
    QSqlDatabase db;
    QSqlQuery quer;
    QString nom=ui->nom_2->text();
    QString password=ui->password_login->text();

    quer.prepare(QString ("SELECT * FROM EMPLOYES WHERE nom= :nom AND password= :password"));

    quer.bindValue(":nom", nom);
    quer.bindValue(":password", password);

quer.exec();
    if(quer.next())
    {

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("login effectué \n"
                                             "Click Cancel to exit."),QMessageBox::Cancel);
    }

    else
    {
        QMessageBox::critical(nullptr,QObject::tr("not OK"),
                              QObject::tr("failed to execute \n"
                                          "Click Cancel to exit."),QMessageBox::Cancel);
    }


}

void MainWindow::on_pushButton_mailing_clicked()
{

  QString link="https://mail.google.com/mail/u/0/#inbox?compose=new";
        QDesktopServices::openUrl(link);

}


/////////////////////////////Lieux/////////////////////////////////////////
void MainWindow::updatelabel()
{
    data=A.read_from_arduino();
    if(data!="0"){
       //
     if (data=="3"){
 QMessageBox::information(this,"NOTIFICATIONS","S'IL VOUS PLAIT CONSULTER VOTRE BOITE DE NOTIFICATIONS.");
        ui->label_11->setText("Il y a du gaz dans la salle activer le sonor");//afficher on si les données reçues par arduino est 1
}
    else if(data=="2")

           ui->label_11->setText("il y a plus de gaz dans la salle deactiver le sonor !");
}
}

void MainWindow::on_leajouter_clicked()
{
    QString id_lieux=ui->le_id->text();
    QString adresee=ui->leadresee->text();
    QString capacite=ui->lecapacite->text();
    QString prix_location=ui->leprix->text();
    QString nbr_reservation=ui->le_nbr_reservation->text();
    Lieux l(id_lieux,adresee,capacite,prix_location,nbr_reservation);
QMessageBox msgbox;
    bool test=l.ajouter();
    if(test)
    {
        ui->tab_afficher->setModel(l.afficher());

        msgbox.setText("ajout avc succes.");
        ui->tab_afficher->setModel(l.afficher());

    }
      else   msgbox.setText("echec d'ajout");
    msgbox.exec();


}



void MainWindow::on_supprimer_clicked()
{
    {
     Lieux l1;
     l1.setid_lieux(ui->le_supprid->text());
    bool test=l1.supprimer(l1.getid_lieux());
    QMessageBox msgBox;
    if(test)
    {
     msgBox.setText("Suppression avec succes.");
    ui->tab_afficher->setModel(l.afficher());
    }
    else
        msgBox.setText("Echec de suppression");
    msgBox.exec();

    }


    }


void MainWindow::on_modifier_clicked()
{

    QString id_lieux=ui->le_id->text();
        QString adresse=ui->leadresee->text();
        QString capacite=ui->lecapacite->text();
        QString prix_location=ui->leprix->text();
        QString nbr_reservation=ui->le_nbr_reservation->text();


         Lieux l(id_lieux,adresse,capacite,prix_location,nbr_reservation);
         bool test=l.modifier();
         QMessageBox msgBox;

         if(test)
         {
  ui->tab_afficher->setModel(l.afficher());



              msgBox.setText("modification avec succes.");

             msgBox.exec();
         }
         else
            {
             msgBox.setText("Echec de modification");
         msgBox.exec();

  }
}



void MainWindow::on_pushButton_clicked()
{
    QString program = "C:/Bureau/map/debug.exe";

            QStringList arguments;
            QProcess *chromeProcess = new QProcess(this);
            chromeProcess->start(program);

}

void MainWindow::on_pushButton_2_clicked()
{
    QString adresse=ui->ad->text();
    QString degre=ui->Degres->text();
    if (degre.toInt()<15)
    {
        QSqlQuery query;
        query.prepare("update lieux set etat = :etat where adresse = :ad ");
        query.bindValue(":ad",adresse);
        query.bindValue(":etat","Inaccessible");
        query.exec();
        QMessageBox::information(nullptr, QObject::tr(""),
                    QObject::tr("Mise à jour reussit\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
}

void MainWindow::on_pushButton_3_clicked()
{ QString adresse=ui->ad_2->text();


    {
        QSqlQuery query;
        query.prepare("update lieux set etat = :etat where adresse = :ad ");
        query.bindValue(":ad",adresse);
        query.bindValue(":etat","Accessible");
        query.exec();
        QMessageBox::information(nullptr, QObject::tr(""),
                    QObject::tr("Mise à jour reussit"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

}

void MainWindow::on_chercher_clicked()
{


    QString str=ui->lineEdit->text();
        ui->tab_afficher->setModel(l.rechercher(str));



}



void MainWindow::on_radioButton_a_clicked()
{
    Lieux l;
     QString type="";

     if(ui->radioButton_a->isChecked())
         type="ASC";
     else if(ui->radioButton_d->isChecked())
         type="DESC";

     if(ui->comboBox_trie->currentText() != "Choisir")
         ui->tab_afficher->setModel(l.trie_NBR_Reservation(type,ui->comboBox_trie->currentText()));


     else  ui->tab_afficher->setModel(l.afficher());
}

void MainWindow::on_radioButton_d_clicked()
{
    Lieux l;
     QString type="";

     if(ui->radioButton_a->isChecked())
         type="ASC";
     else if(ui->radioButton_d->isChecked())
         type="DESC";

     if(ui->comboBox_trie->currentText() != "Choisir")
         ui->tab_afficher->setModel(l.trie_NBR_Reservation(type,ui->comboBox_trie->currentText()));


     else  ui->tab_afficher->setModel(l.afficher());
}

void MainWindow::on_pushButton_10_clicked()
{
    QString x=ui->ad->text();
    QString link = "https://meteofrance.com/meteo-"+x;
    QDesktopServices::openUrl(QUrl(link));


}



void MainWindow::on_pushButton_11_clicked()

    {


    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                       "/home",
                                                       QFileDialog::ShowDirsOnly
                                                       | QFileDialog::DontResolveSymlinks);
           qDebug()<<dir;
           QPdfWriter pdf(dir+"/PdfList.pdf");
                                  QPainter painter(&pdf);
                                 int i = 4000;

                                      painter.drawPixmap(QRect(100,100,2500,2500),QPixmap("C:/Users/rank/Documents/integration/LOGO.jpg"));
                                      painter.drawText(400,700,"E-Planner");
                                      painter.setPen(Qt::red);
                                      painter.setFont(QFont("Time New Roman", 25));
                                      painter.drawText(3000,1400,"Liste Des Lieux");
                                      painter.setPen(Qt::black);
                                      painter.setFont(QFont("Time New Roman", 15));
                                      painter.drawRect(100,100,9400,2500); // dimension taa rectangle li fih liste
                                      painter.drawRect(100,3000,9400,500);
                                      painter.setFont(QFont("Time New Roman", 9));
                                      painter.drawText(300,3300,"ID");
                                      painter.drawText(2000,3300,"Adresse");
                                      painter.drawText(4000,3300,"Capacite");
                                      painter.drawText(5600,3300,"prix location");
                                      painter.drawText(7000,3300,"Nombre de reservation");
                                      painter.drawRect(100,3000,9400,10700);
                                      QTextDocument previewDoc;
                                      //QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
                                      QTextCursor cursor(&previewDoc);
                                      QSqlQuery query;
                                      query.prepare("select * from LIEUX");
                                      query.exec();
                                      while (query.next())
                                      {
                                          painter.drawText(300,i,query.value(0).toString());
                                          painter.drawText(2000,i,query.value(1).toString());
                                          painter.drawText(4000,i,query.value(2).toString());
                                          painter.drawText(5600,i,query.value(3).toString());
                                          painter.drawText(7000,i,query.value(4).toString());
                                         i = i +500;
                                      }
                                      int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                          QMessageBox::Yes|QMessageBox::No);
                                          if (reponse == QMessageBox::Yes)
                                          {
                                              QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                              painter.end();
                                          }
                                          else
                                          {
                                               painter.end();

}


       }



void MainWindow::on_label_11_linkActivated(const QString &link)
{


   // QChartView *Lieux::stat_type()
      {
          int leadresee1=0;
          int leadresee2=0;
          int leadresee3=0;
          int leadresee4=0;

          QSqlQuery query;
          query.prepare("select * from lieux where TYPE='leadresee1'");
          query.exec();

          while(query.next())
              leadresee1++;

          query.prepare("select * from lieux where TYPE='leadresee2'");
          query.exec();

          while(query.next())
              leadresee2++;

          query.prepare("select * from lieux where TYPE='leadresee3'");
          query.exec();

          while(query.next())
              leadresee3++;

          query.prepare("select * from lieux where TYPE='leadresee4'");
          query.exec();

          while(query.next())
              leadresee4++;

          qDebug() << leadresee1 << leadresee2 << leadresee3 << leadresee4 ;

          QPieSeries *series = new QPieSeries();
              series->append("leadresee1", leadresee1);
              series->append("leadresee2", leadresee2);
              series->append("leadresee3", leadresee3);
              series->append("leadresee4", leadresee4);

              QPieSlice *slice = series->slices().at(0);
              slice->setExploded(true);
              slice->setColor("#4C6293");
              slice->setLabel("leadresee1 "+QString("%1%").arg(100*slice->percentage(),1,'f',1));
              QPieSlice *slice2 = series->slices().at(1);
              slice2->setColor("#E4F0FF");
              slice2->setLabel("leadresee2 "+QString("%1%").arg(100*slice2->percentage(),1,'f',1));
              QPieSlice *slice3 = series->slices().at(2);
              slice3->setColor("#7D83D6");
              slice3->setLabel("leadresee3 "+QString("%1%").arg(100*slice3->percentage(),1,'f',1));
              QPieSlice *slice4 = series->slices().at(3);
              slice4->setColor("#6495ed");
              slice4->setLabel("leadresee4 "+QString("%1%").arg(100*slice4->percentage(),1,'f',1));

              QChart *chart = new QChart();
              chart->addSeries(series);
              chart->setTitle("Statistique du leadresee");


              series->setLabelsVisible();

              QChartView *chartView = new QChartView(chart);
              chartView->setRenderHint(QPainter::Antialiasing);
              chartView->chart()->setAnimationOptions(QChart::AllAnimations);
              chartView->chart()->legend()->hide();
              chartView->resize(1000,500);
             // return chartView;



        }
}

void MainWindow::on_pushButtonactiver_clicked()
{
    ui->pushButtonactiver->setStyleSheet("QPushButton:pressed { background-color: green}");
        A.write_to_arduino("1");
}


void MainWindow::on_pushButtondeactiver_clicked()
{

    ui->pushButtondeactiver->setStyleSheet("QPushButton:pressed { background-color: green}");
        A.write_to_arduino("0");
}

////////////////////////////////////////////Partenaire//////////////////////////////////////////////
void MainWindow::on_addpart_2_clicked()
{
    int id=ui->edid->text().toInt();
    QString nomentr=ui->edentremprise->text();
    QString nom=ui->ednom->text();
    QString prenom=ui->edprenom->text();
    QString service=ui->edservice->text();
    QString email=ui->edemail->text();
        int numeros=ui->ednumeros->text().toInt();
        partenaires p (id,nomentr,nom,prenom,service,email,numeros);
        bool test=p.ajouter();
        QMessageBox msgbox;
        if(test)
        {   msgbox.setText("ajout avec succes");


           ui->tableau->setModel(p.afficher());

        }
        else
        {msgbox.setText("echec d'ajout ");
            msgbox.exec();
        }

}


void MainWindow::on_supp_2_clicked()
{
    partenaires p;
    p.setid(ui->supid->text().toInt());
    bool test=p.supprimer(p.getid());
QMessageBox msgbox;
    if(test)
    {
        msgbox.setText("sup avc succe");
       ui->tableau->setModel(p.afficher());

    }
    else
      msgbox.setText("echec de supp");
    msgbox.exec();

}


void MainWindow::on_pushButton_12_clicked()
{

    int id=ui->edid->text().toInt();
              QString nomentr=ui->edentremprise->text();
              QString nom=ui->ednom->text();
              QString prenom=ui->edprenom->text();
              QString service=ui->edservice->text();
              QString email=ui->edemail->text();
                  int numeros=ui->ednumeros->text().toInt();
           partenaires p (id,nomentr,nom,prenom,service,email,numeros);
                  QString res = QString::number(id);
                  QString resn1 = QString::number(numeros);
            QSqlQuery quer;

            quer.prepare("update PARTENAIRE set NOMENTREPRISE='"+nomentr+"' ,nom='"+nom+"', prenom='"+prenom+"', service='"+service+"', email='"+email+"', numeros='"+resn1+"' where id='"+res+"'");
              if(quer.exec())
              {

                  ui->tableau->setModel(p.afficher());

               QMessageBox::information(nullptr,QObject::tr("OK"),
                                        QObject::tr("modification effectué \n"
                                                    "Click Cancel to exit."),QMessageBox::Cancel);
              }
              else
                  QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                        QObject::tr("modification non effectué \n"
                                                    "Click Cancel to exit."),QMessageBox::Cancel);
    /*  int id=ui->edid->text().toInt();
          QString nomentr=ui->edentremprise->text();
          QString nom=ui->ednom->text();
          QString prenom=ui->edprenom->text();
          QString service=ui->edservice->text();
          QString email=ui->edemail->text();
              int numeros=ui->ednumeros->text().toInt();
              partenaires p (id,nomentr,nom,prenom,service,email,numeros);

              QMessageBox msgbox;
              bool test=p.modifier();
              if (test){
                  msgbox.setText("modif avec succes");
                  ui->tableau->setModel(p.afficher());
              }
              else msgbox.setText("echec de modif");
              msgbox.exec();




    * int id=ui->edid->text().toInt();
    QString nomentr=ui->edentremprise->text();
    QString nom=ui->ednom->text();
    QString prenom=ui->edprenom->text();
    QString service=ui->edservice->text();
    QString email=ui->edemail->text();
        int numeros=ui->ednumeros->text().toInt();
        partenaires p (id,nomentr,nom,prenom,service,email,numeros);
    *
    * QItemSelectionModel *select = ui->tableau->selectionModel();
              ui->edid->setText(select->selectedRows(0).value(0).data().toString());
               ui->edentremprise->setText(select->selectedRows(1).value(0).data().toString());
               ui->ednom->setText(select->selectedRows(2).value(0).data().toString());
              ui->edprenom->setText(select->selectedRows(3).value(0).data().toString());
              ui->edservice->setText(select->selectedRows(4).value(0).data().toString());
              ui->edemail->setText(select->selectedRows(4).value(0).data().toString());
              ui->ednumeros->setText(select->selectedRows(4).value(0).data().toString());*/
            //  p.modifier();
    /*partenaires p;
    p.setid(ui->edid->text().toInt());
    p.setemail(ui->edemail->text());
    bool test=p.modemail(p.getemail(),p.getid());
QMessageBox msgbox;
    if(test)
    {
        msgbox.setText("mod avc succe");
       ui->tableau->setModel(p.afficher());

    }
    else
      msgbox.setText("echec de mod");
    msgbox.exec();


   QSqlQuery q;
    QString m=ui->edemail->text();
    int res=ui->edid->text().toInt();
    //Marqueurs ?
    q.exec("UPDATE PARTENAIRE SET email=? WHERE id =?");
    q.addBindValue(m);
    q.addBindValue(res);
    ui->tableau->setModel(p.afficher());*/

}

void MainWindow::on_btnrecherche_clicked()
{
    partenaires p;
           QString n=ui->edrecherche->text();
           ui->tablerech->setModel(p.recherche(n));
}

void MainWindow::on_comboBox_highlighted(const QString &arg1)
{

          partenaires p;
            QString type="";

            if(ui->radioButton->isChecked())
                type="ASC";
            else if(ui->radioButton_2->isChecked())
                type="DESC";

            if(arg1 != "Choisir")
                ui->tableau->setModel(p.trier(type,arg1));

            else  ui->tableau->setModel(p.afficher());


}

void MainWindow::on_radioButton_clicked()
{
    partenaires p;
            QString type="";


            if(ui->radioButton->isChecked())
                type="ASC";
            else if(ui->radioButton_2->isChecked())
                type="DESC";

            if(ui->comboBox->currentText() != "Choisir")
                ui->tableau->setModel(p.trier(type,ui->comboBox->currentText()));

            else  ui->tableau->setModel(p.afficher());
}

void MainWindow::on_radioButton_2_clicked()
{
    partenaires p;
            QString type="";

            if(ui->radioButton->isChecked())
                type="ASC";
            else if(ui->radioButton_2->isChecked())
                type="DESC";

            if(ui->comboBox->currentText() != "Choisir")
                ui->tableau->setModel(p.trier(type,ui->comboBox->currentText()));


            else  ui->tableau->setModel(p.afficher());
}

void MainWindow::on_pdf_clicked()
{

    QString strStream;
      QTextStream out(&strStream);

   const int rowCount = ui->tableau->model()->rowCount();
   const int columnCount = ui->tableau->model()->columnCount();
   out <<  "<html>\n"
           "<head>\n"
   "<meta Content=\"Text/html; charset=Windows-1251\">\n"
   <<  QString("<title>%1</title>\n").arg("strTitle")
   <<  "</head>\n"
  "<body bgcolor=#ffffff link=#5000A0>\n"

  //     "<align='right'> " << datefich << "</align>"
     "<center> <H1>Liste Des Partenaires  </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

             // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
   for (int column = 0; column < columnCount; column++)
   if (!ui->tableau->isColumnHidden(column))
       out << QString("<th>%1</th>").arg(ui->tableau->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

                                           // data table
           for (int row = 0; row < rowCount; row++) {
            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
              for (int column = 0; column < columnCount; column++) {
            if (!ui->tableau->isColumnHidden(column)) {
     QString data = ui->tableau->model()->data(ui->tableau->model()->index(row, column)).toString().simplified();
     out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                                   }
                                               }
                      out << "</tr>\n";
                                           }
                            out <<  "</table> </center>\n"
                                    "</body>\n"
                                  "</html>\n";
      QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                   QPrinter printer (QPrinter::PrinterResolution);
                    printer.setOutputFormat(QPrinter::PdfFormat);
                   printer.setPaperSize(QPrinter::A4);
                  printer.setOutputFileName(fileName);

                   QTextDocument doc;
                    doc.setHtml(strStream);
                    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                    doc.print(&printer);
}


//mailing
void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("agbemavoharold@gmail.com",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("agbemavoharold@gmail.com", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("agbemavoharold@gmail.com", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}


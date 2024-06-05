#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"evenement.h"
#include "client.h"
#include "employe.h"
#include"lieux.h"
#include "arduino.h"
#include "partenaires.h"
#include "smtp.h"
#include <QMainWindow>
#include <QMainWindow>
#include <QStackedWidget>
#include <QAbstractItemView>
#include <QString>
#include <QDebug>
#include <QListWidget>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


void on_listWidget_itemClicked();
void on_listWidget_itemSelectionChanged();
void on_pb_ajouter_3_clicked();
void on_pb_supprimer_3_clicked();
void on_prechercher_4_clicked();
void on_recherchelieu_4_textChanged(const QString &arg1);
void on_comboBox_4_highlighted(const QString &arg1); void on_radioButton_7_clicked();
void on_radioButton_8_clicked();
void on_mdf_3_clicked();
void on_recherchertype_4_textChanged(const QString &arg1);
void on_pdf_3_clicked();
void on_calendarWidget_3_selectionChanged();
void on_qrcode_button_3_clicked();
void on_tabEvenement_4_clicked(const QModelIndex &index);
void update_label();

void on_pushButton_4_clicked();
void on_pushmod_2_clicked();
void on_supp_clicked();
void on_xl_clicked();
void on_search_textEdited(const QString &arg1);
void on_tri_clicked();
void readfile();
void on_tabWidget_2_currentChanged(int index);
void on_pdf1_clicked();
void on_comboBox_activated(const QString &arg1);
void on_le_date_userDateChanged(const QDate &date);
void on_le_nom_cursorPositionChanged(int arg1, int arg2);
void on_pushButton_5_clicked();
void on_tableView_Res_viewportEntered();
void on_tri_2_clicked();
void renderChart1();


void on_pb_ajouter1_clicked();
void on_pb_supprimer1_clicked();
void on_tab_employe_activated(const QModelIndex &index);
void on_pb_modifier_clicked();
void on_lineEditRecherche_textChanged(const QString &arg1);
void on_comboBox1_highlighted(const QString &arg1);
void on_radioButton_5_clicked();
void on_radioButton_6_clicked();
void on_pdf2_clicked();
void on_stats_clicked();
void on_pushButton_login_clicked();
void on_pushButton_mailing_clicked();

void on_leajouter_clicked();

//void on_pushButton_clicked();

void on_supprimer_clicked();

void on_modifier_clicked();

void on_pushButton_clicked();

void on_pushButton_2_clicked();

void on_pushButton_3_clicked();

void on_chercher_clicked();

// void on_comboBox_highlighted(const QString &arg1);

void on_radioButton_a_clicked();

void on_radioButton_d_clicked();

void on_pushButton_10_clicked();

void on_pushButton_11_clicked();

void on_pushButton_6_clicked();

void on_label_11_linkActivated(const QString &link);


void on_pushButtonactiver_clicked();

void on_pushButtondeactiver_clicked();
void updatelabel();


void on_addpart_2_clicked();

void on_supp_2_clicked();

void on_pushButton_12_clicked();

void on_btnrecherche_clicked();

void on_comboBox_highlighted(const QString &arg1);

void on_radioButton_clicked();

void on_radioButton_2_clicked();

void on_pdf_clicked();

void sendMail();

void mailSent(QString);

void browse();




private:
    Ui::MainWindow *ui;
        Evenement EV;
        Client tmpres ;
            Employe E;
            Lieux l;
            Arduino A;
            QByteArray data;
            partenaires p;
           QStringList files;

};
#endif // MAINWINDOW_H

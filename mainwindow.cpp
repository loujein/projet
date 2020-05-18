#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include"location.h"
#include <QSqlQuery>
#include<QDate>
#include<QDateEdit>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include "mailing/SmtpMime"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_passe->setInputMask("aaaaaaaaaaaaaaaa");
    ui->lineEdit_m->setInputMask("aaaaaaaaaaaaaaaa");
    ui->lineEdit_pseudo->setValidator( new QIntValidator(0, 99999999, this) );
    ui->lineEdit_13->setValidator( new QIntValidator(0, 99999999, this) );

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString cin= ui->lineEdit_pseudo->text();
    QString nom= ui->lineEdit_passe->text();
    QString prenom= ui->lineEdit_m->text();
    QString salaire= ui->lineEdit_ida->text();
    QString departement= ui->comboBox_2->currentText();
    QString ville= ui->lineEdit_4->text();
    QString adresse= ui->lineEdit_5->text();
    QString gendre= ui->comboBox->currentText();
    int id_agence= ui->lineEdit_6->text().toInt();
    QDate date_ajout= ui->dateEdit->date();
    QString image= ui->lineEdit_3->text();
    employe e(cin,nom,prenom,salaire,gendre,departement,ville,adresse,image,id_agence,date_ajout);
    bool test=e.ajouter();
    if(test)
    {
        ui->tableemp->setModel(tmpemp.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ajouter un employe"),
                          QObject::tr("employe ajouté.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("Ajouter un employe"),
                          QObject::tr("erreur.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    QString cin= ui->lineEdit_pseudo->text();
    QString nom= ui->lineEdit_passe->text();
    QString prenom= ui->lineEdit_m->text();
    QString salaire= ui->lineEdit_ida->text();
    QString departement= ui->comboBox_2->currentText();
    QString ville= ui->lineEdit_4->text();
    QString adresse= ui->lineEdit_5->text();
    QString gendre= ui->comboBox->currentText();
    int id_agence= ui->lineEdit_6->text().toInt();
    QDate date_ajout= ui->dateEdit->date();
    QString image= ui->lineEdit_3->text();
    employe e(cin,nom,prenom,salaire,gendre,departement,ville,adresse,image,id_agence,date_ajout);
    bool test=e.modifier(id);
    if(test)
    {
        ui->tableemp->setModel(tmpemp.afficher());
        QMessageBox::information(nullptr, QObject::tr("Modifier un employe"),
                          QObject::tr("employe modifié.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("Modifier un employe"),
                          QObject::tr("erreur.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_10_clicked()
{
   ui->tableemp->setModel(tmpemp.afficher());
}

void MainWindow::on_pushButton_5_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    bool test=tmpemp.supprimer(id);
    //bool test1=tmpcompte.tester(id);
    if(test)
    {
            QMessageBox::information(nullptr, QObject::tr("compte existe"),
                        QObject::tr("compte supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
             ui->tableemp->setModel(tmpemp.afficher());

    }

    else
    {

        QMessageBox::critical(nullptr, QObject::tr("compte n'existe pas"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

void MainWindow::on_pushButton_12_clicked()
{
   QString nom= ui->lineEdit_passe->text();
   ui->tableemp->setModel(tmpemp.recherche(nom));

   QMessageBox::information(this, QObject::tr("Rechercher un compte"),
        QObject::tr("compte recherché.\n"
                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->tableemp->setModel(tmpemp.tri());
}

void MainWindow::on_radioButton_clicked()
{
    ui->tableemp->setModel(tmpemp.tri2());
}

void MainWindow::on_lineEdit_7_textChanged(const QString &arg1)
{
    employe e ;
    QString nom=ui->lineEdit_7->text();
    e.recherchee(ui->tableemp,nom);
}

void MainWindow::on_tableemp_activated(const QModelIndex &index)
{
    QString val= ui->tableemp->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from employe where id= '"+val+"' ");
    if(query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_id->setText(query.value(0).toString());
            ui->lineEdit_pseudo->setText(query.value(1).toString());
            ui->lineEdit_passe->setText(query.value(2).toString());
            ui->lineEdit_m->setText(query.value(3).toString());
            ui->lineEdit_ida->setText(query.value(4).toString());
            ui->comboBox_2->setCurrentText(query.value(5).toString());
            ui->lineEdit_4->setText(query.value(6).toString());
            ui->lineEdit_5->setText(query.value(7).toString());
            ui->comboBox->setCurrentText(query.value(8).toString());
            ui->lineEdit_6->setText(query.value(9).toString());
            ui->dateEdit->setDate(query.value(10).toDate());
            ui->lineEdit_3->setText(query.value(11).toString());
        }
    }
    else
        QMessageBox::information(nullptr, QObject::tr("Modifier un compte"),
                          QObject::tr("erreur.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_14_clicked()
{
    //QDate datecreation = dateEdit.currentDateTime();
        //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
               QPdfWriter pdf("C:/Users/Administrateur/Downloads/Pdf.pdf"); //hedha badlouh ca depend win thobou tsobou le fichier pdf
               QPainter painter(&pdf);
              int i = 4000;
                   painter.setPen(Qt::blue);
                   painter.setFont(QFont("Arial", 30));
                   painter.drawText(1100,1200,"Liste Des employees");
                   painter.setPen(Qt::black);
                   painter.setFont(QFont("Arial", 15));
                  //painter.drawText(1100,2000,afficheDC);
                   painter.drawRect(100,100,7300,3000);
                   painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/Administrateur/Pictures/Saved Pictures/loc.jpg"));
                   painter.drawRect(0,3000,9600,500);
                   painter.setFont(QFont("Arial", 9));
                   painter.drawText(200,3300,"ID");
                   painter.drawText(1300,3300,"CIN");
                   painter.drawText(2100,3300,"NOM");
                   painter.drawText(3200,3300,"PRENOM");
                   painter.drawText(4300,3300,"SALAIRE");
                   painter.drawText(5400,3300,"GENDRE");
                   painter.drawText(6500,3300,"DEPARTEMENT");
                   painter.drawText(7600,3300,"VILLE");
                   painter.drawText(8700,3300,"ADRESSE");
                   painter.drawText(9800,3300,"IMAGE");
                   painter.drawText(10900,3300,"ID_AGENCE");
                   painter.drawText(11000,3300,"DATE_AJOUT");

                   QSqlQuery query;
                   query.prepare("select * from employe");
                   query.exec();
                   while (query.next())
                   {
                       painter.drawText(200,i,query.value(0).toString());
                       painter.drawText(1300,i,query.value(1).toString());
                       painter.drawText(2200,i,query.value(2).toString());
                       painter.drawText(3200,i,query.value(3).toString());
                       painter.drawText(4500,i,query.value(4).toString());
                       painter.drawText(5600,i,query.value(5).toString());
                       painter.drawText(6700,i,query.value(6).toString());
                       painter.drawText(7800,i,query.value(7).toString());
                       painter.drawText(8900,i,query.value(8).toString());
                       painter.drawText(10000,i,query.value(9).toString());
                       painter.drawText(11200,i,query.value(10).toString());
                       painter.drawText(12300,i,query.value(11).toString());
                      i = i + 500;
                   }
                   int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                       if (reponse == QMessageBox::Yes)
                       {

                           painter.end();
                       }
                       if (reponse == QMessageBox::No)
                       {
                            painter.end();
                       }
}

/////////////////////////////////////////////////////LOCATION///////////////////////////////////////////
void MainWindow::on_pushButton_8_clicked()
{
    ui->lineEdit_13->setDisabled(1);
    ui->lineEdit_16->setDisabled(1);
    QString res_entretien= ui->lineEdit_15->text();
    int id_client= tmploc.getClient(ui->lineEdit->text());
    int id_voiture= tmploc.getVoiture(ui->lineEdit_14->text());
    int id_compte= tmploc.getAgent(ui->lineEdit_18->text());
    qDebug()<<id_client;
    qDebug()<<id_voiture;
    qDebug()<<id_compte;
    QDate date_debut= ui->dateEdit_2->date();
    QDate date_fin= ui->dateEdit_3->date();
    int nbreJ= date_debut.daysTo(date_fin);
    double prix=tmploc.prixTot(nbreJ,id_voiture);
    ui->lineEdit_16->setText(QString::number(prix));
    double prixf=tmploc.prixF(prix,id_voiture);
    prixf=qRound(prixf);
    ui->lineEdit_13->setText(QString::number(prixf));
    location c(QString::number(prixf),res_entretien,id_client,id_voiture,id_compte,date_debut,date_fin);
    bool test=c.ajouter();
    if(test)
    {
        ui->tableView_2->setModel(tmploc.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ajouter une location"),
                          QObject::tr("location ajoutée.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("Ajouter une location"),
                          QObject::tr("erreur.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    int id=ui->lineEdit_2->text().toInt();
    QString prix= ui->lineEdit_13->text();
    QString res_entretien= ui->lineEdit_15->text();
    int id_client= ui->lineEdit->text().toInt();
    int id_voiture= ui->lineEdit_14->text().toInt();
    int id_compte= ui->lineEdit_18->text().toInt();

    QDate date_debut= ui->dateEdit_2->date();
    QDate date_fin= ui->dateEdit_3->date();
    location c(prix,res_entretien,id_client,id_voiture,id_compte,date_debut,date_fin);
    bool test=c.modifier(id);
    if(test)
    {
        ui->tableView_2->setModel(tmploc.afficher());
        QMessageBox::information(nullptr, QObject::tr("Modifier une location"),
                          QObject::tr("location modifièe.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("Modifier une location"),
                          QObject::tr("erreur.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_13_clicked()
{

    int id=ui->lineEdit_2->text().toInt();
    bool test=tmploc.supprimer(id);
    //bool test1=tmpcompte.tester(id);
    if(test)
    {
            QMessageBox::information(nullptr, QObject::tr("location existe"),
                        QObject::tr("location supprimée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
             ui->tableView_2->setModel(tmploc.afficher());

    }

    else
    {

        QMessageBox::critical(nullptr, QObject::tr("location n'existe pas"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->tableView_2->setModel(tmploc.afficher());
}

/*void MainWindow::on_pushButton_14_clicked()
{
    int id= ui->lineEdit_2->text().toInt();
    ui->tableView_2->setModel(tmploc.recherche(id));

    QMessageBox::information(this, QObject::tr("Rechercher une location"),
         QObject::tr("location recherchée.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
}*/

void MainWindow::on_radioButton_3_clicked()
{
   ui->tableView_2->setModel(tmploc.tri());
}

void MainWindow::on_radioButton_4_clicked()
{
   ui->tableView_2->setModel(tmploc.tri2());
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    location l ;
    int id= ui->lineEdit_2->text().toInt();
    l.recherchee(ui->tableView_2,id);
}

void MainWindow::on_tableView_2_activated(const QModelIndex &index)
{
    QString val= ui->tableView_2->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from location where id= '"+val+"' ");
    if(query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_2->setText(query.value(0).toString());
            ui->lineEdit_13->setText(query.value(1).toString());
            ui->lineEdit_15->setText(query.value(2).toString());
            ui->lineEdit->setText(query.value(3).toString());
            ui->lineEdit_14->setText(query.value(4).toString());
            ui->lineEdit_18->setText(query.value(5).toString());
            ui->dateEdit_2->setDate(query.value(6).toDate());
            ui->dateEdit_3->setDate(query.value(7).toDate());
        }
    }
    else
        QMessageBox::information(nullptr, QObject::tr("Modifier un compte"),
                          QObject::tr("erreur.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
}





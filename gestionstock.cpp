#include "gestionstock.h"
#include "mainwindow.h"
#include "ui_gestionstock.h"
#include "panne.h"
#include "participation.h"
#include "mecanicien.h"
#include <QMessageBox>
#include <QDebug>
#include <mailing/SmtpMime>
int n=0,nb=0,id2=-1;
QString ch="";
QString ch1="";
QString chaine="";
QString filename="";
QString rechP="",rechv="";
gestionStock::gestionStock(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestionStock)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableMecanicien->setModel(tabMecanicien.afficher(nb));
    ui->tablePan->setModel(tabPanne.afficher(n));
    ui->table_rech_v->setModel(tabRechV.afficherV(ch));
    ui->table_rech_m->setModel(tabRechM.afficherM(chaine));
    ui->tableVoiture->setModel(tabVoiture.afficher());
    ui->tableAgence->setModel(tabVoiture.afficherA(ch1));
    ui->rechAgence->setPlaceholderText("ville du l agence");
    ui->cinM->setPlaceholderText("Cin du mecanicien");
    ui->matrV->setPlaceholderText("matricule du voiture");
    ui->tabEve->setModel(tmpevent.affichage("Gestion Stock"));
    ui->titre->setText("<h2><center>Evenements A Venir</center></h2>");
}

gestionStock::~gestionStock()
{
    delete ui;
}
void gestionStock::authentification(QString pseudo, QString passe)
{
    compte c;
    this->id=c.connecter(pseudo,passe);
}
bool chaineNum(QString ch)
{
    bool test=true;
        for(int i=0;i<ch.length();i++)
        {
            if((ch[i]<'0')||(ch[i]>'9'))
                test=false;
        }
        return test;
}
bool chaineAlpha(QString ch)
{bool test=true;
    for(int i=0;i<ch.length();i++)
    {
        if((ch[i]<'A')||(ch[i]>'z')||((ch[i]>'Z')&&(ch[i]<'a')))
        {test=false;
        }
    }
    return test;
}
void gestionStock::on_gestionPanne_clicked()
{
ui->stackedWidget->setCurrentIndex(1);
}

void gestionStock::on_gestionMecanicien_clicked()
{
ui->stackedWidget->setCurrentIndex(2);
}

void gestionStock::on_gestionVoiture_clicked()
{
ui->stackedWidget->setCurrentIndex(3);
}

void gestionStock::on_ajouter_panne_clicked()
{ui->lineEdit_cin->setReadOnly(false);
    bool test=true;
        QString msg="";
        QString gendre="";
        QString cin = ui->lineEdit_cin->text();
        QString nom = ui->lineEdit_nom->text();
        QString prenom = ui->lineEdit_prenom->text();
        QString tel = ui->lineEdit_tel->text();
        QString adresse = ui->lineEdit_adresse->text();
        QString ville = ui->lineEdit_ville->text();
        if(ui->male->isCheckable())
        {
        gendre="male";
        }
        else  gendre="female";
            if((chaineNum(cin)==false)||(cin.length()!=8))
            {
                test=false;
                ui->lineEdit_cin->clear();
                if(msg=="")
                msg="cin doit etre forme de 8 chiffres";
            }
            if((chaineAlpha(nom)==false)||(nom.length()==0)||(nom.length()>20))
            {   test=false;
                ui->lineEdit_nom->clear();
                if(msg=="")
                msg="nom est une chaine de caracteres de longeur maximale egal a 20";
            }
            if((chaineAlpha(prenom)==false)||(prenom.length()==0)||(prenom.length()>20))
            {
                test=false;
                ui->lineEdit_prenom->clear();
                if(msg=="")
                msg="prenom est une chaine de caracteres de longeur maximale egal a 20";
            }
            if((chaineNum(tel)==false)||(tel.length()!=8))
            {
                test=false;
                ui->lineEdit_tel->clear();
                if(msg=="")
                msg="tel doit etre forme de 8 chiffres";
            }
            if(gendre=="")
            {
                test=false;
                if(msg=="")
                msg="veuillez choisir votre sexe";
            }
            if((chaineAlpha(adresse)==false)||(adresse.length()==0)||(adresse.length()>50))
            {
                test=false;
                ui->lineEdit_adresse->clear();
                if(msg=="")
                msg="Adresse est une chaine de caracteres de longeur maximale egal a 50";
            }
            if((chaineAlpha(ville)==false)||(ville.length()==0)||(ville.length()>20))
            {
                test=false;
                ui->lineEdit_ville->clear();
                if(msg=="")
                msg="ville est une chaine de caracteres de longeur maximale egal a 20";
            }
         if(test==true)
        {mecanicien m(cin,nom,prenom,adresse,ville,gendre,tel);
        if(!(m.ajouter()))
            {m.modifier(cin);
            ui->tableMecanicien->setModel(tabMecanicien.afficher(nb));
            QMessageBox::critical(this,"informal","mecanicien modifié");
            }
            else
            QMessageBox::critical(this,"informal","mecanicien ajouté");
        }
         else
         {
             QMessageBox::critical(this,"warning",msg);
         }
         ui->lineEdit_cin->setText("");
         ui->lineEdit_nom->setText("");
         ui->lineEdit_prenom->setText("");
         ui->lineEdit_tel->setText("");
         ui->lineEdit_ville->setText("");
         ui->lineEdit_adresse->setText("");
}

void gestionStock::on_comboBox_2_currentIndexChanged(int index)
{
    nb=index;
    ui->tableMecanicien->setModel(tabMecanicien.afficher(nb));
}

void gestionStock::on_suppPanne_clicked()
{
    mecanicien m;
        QItemSelectionModel *select = ui->tableMecanicien->selectionModel();
        QModelIndexList list;
        if(select->hasSelection())
        list=select->selectedRows();
        for(int i=0; i< list.count(); i++)
        {
            if(m.supprimer(list[i].data().toString())==false)
                QMessageBox::critical(this,"warning","ce mecanicien est en train de regler une panne");
        }
    ui->tableMecanicien->setModel(tabMecanicien.afficher(nb));
}
void gestionStock::on_pushButton_7_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
}

void gestionStock::on_matrV_textEdited(const QString &arg1)
{
    ch=arg1;
      ui->table_rech_v->setModel(tabRechV.afficherV(ch));
}

void gestionStock::on_cinM_textEdited(const QString &arg1)
{
    chaine=arg1;
      ui->table_rech_m->setModel(tabRechM.afficherM(chaine));
}



void gestionStock::on_ajouterPanne_clicked()
{
    int idV,idM;
     bool test=true;
     QString msg="",dateD,dateF;
     QString prix=ui->prix->text();
     QModelIndex index = ui->table_rech_v->currentIndex();
     QString matricule = index.data(Qt::DisplayRole).toString();
     idV=tabRechV.chercher_id_voiture(matricule);
     QModelIndex index2 = ui->table_rech_m->currentIndex();
     QString nom = index2.data(Qt::DisplayRole).toString();
     idM=tabRechM.chercher_id_mecanicien(nom);
     if(prix.length()==0)
     {
         test=false;
         ui->prix->clear();
         if(msg=="")
         msg="donner un prix";
     }
     if(test==true)
     {panne p(idV,idM,0,dateD,dateF,prix);
     p.ajouter();
     ui->tablePan->setModel(p.afficher(n));
     ui->table_rech_v->setModel(tabRechV.afficherV(ch));
     }
     else
         QMessageBox::critical(this,"warning",msg);
}

void gestionStock::on_modifierPan_clicked()
{
    QItemSelectionModel *select = ui->tablePan->selectionModel();
    QModelIndexList list;
    if(select->hasSelection())
    list=select->selectedRows();
    for(int i=0; i< list.count(); i++)
    {
        tabPanne.modifier(list[i].data().toInt());
    }
ui->tablePan->setModel(tabPanne.afficher(n));
ui->table_rech_v->setModel(tabRechV.afficherV(ch));
}

void gestionStock::on_suppPan_clicked()
{
    panne p;
        QItemSelectionModel *select = ui->tablePan->selectionModel();
        QModelIndexList list;
        if(select->hasSelection())
        list=select->selectedRows();
        for(int i=0; i< list.count(); i++)
        {
            p.supprimer(list[i].data().toInt());
        }
   ui->tablePan->setModel(p.afficher(n));
}

void gestionStock::on_comboBox_currentIndexChanged(int index)
{
    n=index;
    if(n==1)
    ui->modifierPan->setEnabled(false);
else
    ui->modifierPan->setEnabled(true);
    ui->tablePan->setModel(tabPanne.afficher(n));
}

void gestionStock::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
bool testerMat(QString ch)
{
    if(ch.length()==8)
    {QString chaine1=ch.mid(2,2);
    QString chaine2=ch.mid(0,2);
    QString chaine3=ch.mid(4,4);
    if((chaine1=="TN")&&(chaineNum(chaine2))&&(chaineNum(chaine3)))
        return true;
    else return false;
    }
    else if(ch.length()==9)
    {QString chaine1=ch.mid(3,2);
    QString chaine2=ch.mid(0,3);
    QString chaine3=ch.mid(5,4);
    if((chaine1=="TN")&&(chaineNum(chaine2))&&(chaineNum(chaine3)))
        return true;
    else return false;
    }
    else return false;

}
void gestionStock::on_ajouterV_clicked()
{   bool test=true;
    QString msg="";
    QModelIndex index = ui->tableAgence->currentIndex();
    int idA = index.data(Qt::DisplayRole).toInt();
    QString immatricule=ui->imma->text();
    QString fabriquant=ui->fabr->currentText();
    QString marque=ui->marque->text();
    QString prix=ui->prixJour->text();
    QString boite=ui->boite->currentText();
    QString grise=ui->grise->text();
    QString couleur=ui->couleur->text();
    QString energie=ui->energie->text();
    QString puissance=ui->puissance->text();
    QString typ=ui->comboBox_3->currentText();
    int place=0;
    if(ui->portes2->isCheckable())
        place=2;
    else if(ui->portes4->isCheckable()) place=4;
    if(ui->portes2->isCheckable())
        place=2;
    else if(ui->portes4->isCheckable()) place=4;
    if(testerMat(immatricule)==false)
    {
        test=false;
        ui->imma->clear();
        if(msg=="")
        msg="immatricule doit etre sous la forme XXTNXXXX ou XXXTNXXXX";
    }
    if(fabriquant=="")
    {
        test=false;
        if(msg=="")
        msg="Choisir un fabriquant";
    }
    if(marque=="")
    {
        test=false;
        ui->marque->clear();
        if(msg=="")
        msg="Donner une marque";
    }
    if(prix=="")
    {
        test=false;
        ui->prixJour->clear();
        if(msg=="")
        msg="Donner un prix";
    }
    if(boite=="")
    {
        test=false;
        ui->boite->clear();
        if(msg=="")
        msg="Donner une boite vitesse";
    }
    if((couleur=="")||(chaineAlpha(couleur)==false))
    {
        test=false;
        ui->couleur->clear();
        if(msg=="")
        msg="Donner un couleur";
    }
    if((energie=="")||(chaineAlpha(energie)==false))
    {
        test=false;
        ui->energie->clear();
        if(msg=="")
        msg="Donner une source d'energie";
    }
    if((puissance=="")||(chaineNum(puissance)==false))
    {
        test=false;
        ui->puissance->clear();
        if(msg=="")
        msg="Donner le nombre de chevaux";
    }
    if(place==0)
    {
        test=false;
        if(msg=="")
        msg="Choisir le nombre de place";
    }
    if(test)
    {VOITURE v(place,immatricule,boite,marque,typ,prix,grise,couleur,energie,puissance,filename,"libre",idA,fabriquant);
    if(v.ajouter())
    {v.modifier(immatricule); }
    ui->tableVoiture->setModel(tabVoiture.afficher());
            ui->tableAgence->setModel(tabVoiture.afficherA(ch1));}
    else{
        QMessageBox::critical(this,"warning",msg);
    }
}

void gestionStock::on_suppV_clicked()
{
    QItemSelectionModel *select = ui->tableVoiture->selectionModel();
    QModelIndexList list;
    if(select->hasSelection())
    list=select->selectedRows();
    for(int i=0; i< list.count(); i++)
    {
        tabVoiture.supprimer(list[i].data().toString());
    }
    ui->tableVoiture->setModel(tabVoiture.afficher());
            ui->tableAgence->setModel(tabVoiture.afficherA(ch1));
}

void gestionStock::on_consulter_clicked()
{
    QModelIndex index = ui->tableVoiture->currentIndex();
    QString mat = index.data(Qt::DisplayRole).toString();
    QString img;
    VOITURE v;
    int w=ui->imgVoiture2->width();
    int h=ui->imgVoiture2->height();
    v=v.remplirFiche(mat);
    ui->stackedWidget->setCurrentIndex(4);
    if(v.get_IMAGE()=="")
    {
QPixmap pix("D:/ProjetFinale/ProjetFinale/projetA/none.png");
ui->imgVoiture2->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    }
    else
         {QPixmap pix(v.get_IMAGE());
          ui->imgVoiture2->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));}
ui->imma_2->setText(v.get_MATRICULE());
ui->imma_2->setDisabled(1);
ui->fabr_2->setText(v.get_fabriquant());
ui->fabr_2->setDisabled(1);
ui->marque_2->setText(v.get_MARQUE());
ui->marque_2->setDisabled(1);
ui->prixJour_2->setText(v.get_PRIX_JOUR());
ui->prixJour_2->setDisabled(1);
ui->boite_2->setText(v.get_BOITE_VITESSE());
ui->boite_2->setDisabled(1);
ui->grise_2->setText(v.get_NUM_CARTE_GRISE());
ui->grise_2->setDisabled(1);
ui->couleur_2->setText(v.get_COULEUR());
ui->couleur_2->setDisabled(1);
ui->energie_2->setText(v.get_ENERGIE());
ui->energie_2->setDisabled(1);
ui->puissance_2->setText(v.get_PUISSANCE());
ui->puissance_2->setDisabled(1);
ui->nbr->setText(QString::number(v.get_PLACE()));
ui->nbr->setDisabled(1);
}

void gestionStock::on_rechAgence_textEdited(const QString &arg1)
{
    ch1=arg1;
      ui->tableAgence->setModel(tabVoiture.afficherA(ch1));
}

void gestionStock::on_pushButton_clicked()
{
    filename=QFileDialog::getOpenFileName(this,tr("choose"),"",tr("Images (*.png *.jpg *.bmp *.jpeg)"));
    if(QString::compare(filename,QString())!=0)
    {
        QImage image;
        bool valid=image.load(filename);
        if(valid)
        {
            image=image.scaledToWidth(ui->imgVoiture->width(),Qt::SmoothTransformation);
            ui->imgVoiture->setPixmap(QPixmap::fromImage(image));
        }
    }
}

void gestionStock::on_deconnecter_clicked()
{
    MainWindow *m = new MainWindow();
                m->show();
                this->close();
}

void gestionStock::on_menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void gestionStock::on_tableMecanicien_activated(const QModelIndex &index)
{
    QString val=ui->tableMecanicien->model()->data(index).toString();
    mecanicien m=tabMecanicien.getMecanicien(val);
    ui->lineEdit_cin->setText(m.get_cin());
    ui->lineEdit_nom->setText(m.get_nom());
    ui->lineEdit_prenom->setText(m.get_prenom());
    ui->lineEdit_tel->setText(m.get_tel());
    ui->lineEdit_ville->setText(m.get_ville());
    ui->lineEdit_adresse->setText(m.get_adresse());
    if(m.get_gendre()=="male")
        ui->male->setChecked(true);
    else ui->female->setChecked(true);
    ui->lineEdit_cin->setReadOnly(true);

}

void gestionStock::on_participer_clicked()
{
    QItemSelectionModel *select = ui->tabEve->selectionModel();
    QModelIndexList list;
    if(select->hasSelection())
    list=select->selectedRows();
    for(int i=0; i< list.count(); i++)
    {
       participation p(list[i].data().toInt(),this->id);
       p.ajouter();
    }
    ui->tabEve->setModel(tmpevent.affichage("Gestion Stock"));
}

void gestionStock::on_gestionPromotion_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->tableV->setModel(tmppro.afficherV(rechv));
    ui->tableV_2->setModel(tmppro.afficher(rechP));
    ui->modif->setDisabled(true);
    ui->ajouterP->setEnabled(true);
    ui->dateD->setDate(QDate::currentDate());
    ui->dateF->setDate(QDate::currentDate());
    ui->rechV->setPlaceholderText("chercher par Matricule ou marque du voiture");
    ui->rechV_3->setPlaceholderText("chercher par Matricule ou marque du voiture");
}

void gestionStock::on_ajouterP_clicked()
{
    bool test=true;
    QString msg="";
    QString dateD=ui->dateD->date().toString("dd/MM/yyyy");
    QString dateF=ui->dateF->date().toString("dd/MM/yyyy");
    QString v=ui->valeur->text();
    QModelIndex index = ui->tableV->currentIndex();
    int id = index.data(Qt::DisplayRole).toInt();
    QString marque=tmppro.getV(id);
    if(ui->dateD->date()<QDate::currentDate())
    {test=false;
     ui->dateD->setDate(QDate::currentDate());
    if(msg=="")
    msg="date debut superieur a la date actuelle";
    }
    if(ui->dateF->date()<ui->dateD->date())
    {
        test=false;
             ui->dateF->setDate(ui->dateD->date());
            if(msg=="")
            msg="date debut superieur a la date fin";
    }
    if((v.toInt()>80)||(v.toInt()<5)||(v.length()==0))
    {
        test=false;
        ui->valeur->setText("");
        if(msg=="")
        msg="valeur du promotion doit etre entre 5 et 80";
    }
    if(test==false)
    {
       QMessageBox::critical(this,"warning",msg);
    }
    else
     {promotion p(dateD,dateF,v,id);
        if(p.ajouter())
        {QMessageBox::information(this,"information","promotion ajouté");
         QSqlQuery q=tmpcl.getMails();
         q.exec();
         while(q.next())
         {
             SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

                        smtp.setUser("rentcar908@gmail.com");
                        smtp.setPassword("rentcar123");


                        MimeMessage message;

                        message.setSender(new EmailAddress("rentcar908@gmail.com", "Rent Car"));

                        message.addRecipient(new EmailAddress(q.value(0).toString(),"Rent Car"));
                        message.setSubject("Nouvelle Promotion");
                        MimeText text;
                        text.setText("une nouvelle promotion de "+v+"% est disponible a Rent Car de "+dateD+" jusqu'a "+dateF+" pour une voiture de marque "+marque);
                        message.addPart(&text);
                        smtp.connectToHost();
                        smtp.login();
                        smtp.sendMail(message);
                        smtp.quit();
         }
        }
        ui->tableV_2->setModel(tmppro.afficher(rechP));
    }
}

void gestionStock::on_rechV_textEdited(const QString &arg1)
{
    rechv=arg1;
    ui->tableV->setModel(tmppro.afficherV(rechv));
}

void gestionStock::on_rechV_3_textEdited(const QString &arg1)
{
    rechP=arg1;
    ui->tableV_2->setModel(tmppro.afficher(rechP));
}

void gestionStock::on_suppP_clicked()
{
    QItemSelectionModel *select = ui->tableV_2->selectionModel();
    QModelIndexList list;
    if(select->hasSelection())
    list=select->selectedRows();
    for(int i=0; i< list.count(); i++)
    {
       tmppro.supprimer(list[i].data().toInt());
    }
    ui->tableV_2->setModel(tmppro.afficher(rechP));
}

void gestionStock::on_retour_clicked()
{
 ui->stackedWidget->setCurrentIndex(0);
}

void gestionStock::on_tableV_2_doubleClicked(const QModelIndex &index)
{
    ui->modif->setEnabled(true);
    ui->ajouterP->setDisabled(true);
    id2=ui->tableV_2->model()->data(index).toInt();
    promotion p=tmppro.remplir(id2);
    ui->dateD->setDate(QDate::fromString(p.get_date_debut(),"dd/MM/yyyy"));
    ui->dateF->setDate(QDate::fromString(p.get_date_fin(),"dd/MM/yyyy"));
    ui->valeur->setText(p.get_valeur());
}

void gestionStock::on_modif_clicked()
{QModelIndex index = ui->tableV->currentIndex();
    int idv = index.data(Qt::DisplayRole).toInt();
    promotion p(ui->dateD->date().toString("dd/MM/yyyy"),ui->dateF->date().toString("dd/MM/yyyy"),ui->valeur->text(),idv);
    if(tmppro.modifier(p,id2))
    {
       ui->dateD->setDate(QDate::currentDate());
       ui->dateF->setDate(QDate::currentDate());
       ui->valeur->clear();
       ui->ajouterP->setEnabled(true);
       ui->modif->setDisabled(true);
       ui->tableV_2->setModel(tmppro.afficher(rechP));
       QMessageBox::information(this,"information","promotion modifié");
       ui->tableV_2->setModel(tmppro.afficher(rechP));
    }
    else
    QMessageBox::critical(this,"erreur","erreur de modification");
}
void gestionStock::on_deconnecter_clicked()
{
    MainWindow *m = new MainWindow();
                m->show();
                this->close();
}

void gestionStock::on_menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void gestionStock::on_tableMecanicien_activated(const QModelIndex &index)
{
    QString val=ui->tableMecanicien->model()->data(index).toString();
    mecanicien m=tabMecanicien.getMecanicien(val);
    ui->lineEdit_cin->setText(m.get_cin());
    ui->lineEdit_nom->setText(m.get_nom());
    ui->lineEdit_prenom->setText(m.get_prenom());
    ui->lineEdit_tel->setText(m.get_tel());
    ui->lineEdit_ville->setText(m.get_ville());
    ui->lineEdit_adresse->setText(m.get_adresse());
    if(m.get_gendre()=="male")
        ui->male->setChecked(true);
    else ui->female->setChecked(true);
    ui->lineEdit_cin->setReadOnly(true);

}

void gestionStock::on_participer_clicked()
{
    QItemSelectionModel *select = ui->tabEve->selectionModel();
    QModelIndexList list;
    if(select->hasSelection())
    list=select->selectedRows();
    for(int i=0; i< list.count(); i++)
    {
       participation p(list[i].data().toInt(),this->id);
       p.ajouter();
    }
    ui->tabEve->setModel(tmpevent.affichage("Gestion Stock"));
}

void gestionStock::on_gestionPromotion_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->tableV->setModel(tmppro.afficherV(rechv));
    ui->tableV_2->setModel(tmppro.afficher(rechP));
    ui->modif->setDisabled(true);
    ui->ajouterP->setEnabled(true);
    ui->dateD->setDate(QDate::currentDate());
    ui->dateF->setDate(QDate::currentDate());
    ui->rechV->setPlaceholderText("chercher par Matricule ou marque du voiture");
    ui->rechV_3->setPlaceholderText("chercher par Matricule ou marque du voiture");
}

void gestionStock::on_ajouterP_clicked()
{
    bool test=true;
    QString msg="";
    QString dateD=ui->dateD->date().toString("dd/MM/yyyy");
    QString dateF=ui->dateF->date().toString("dd/MM/yyyy");
    QString v=ui->valeur->text();
    QModelIndex index = ui->tableV->currentIndex();
    int id = index.data(Qt::DisplayRole).toInt();
    QString marque=tmppro.getV(id);
    if(ui->dateD->date()<QDate::currentDate())
    {test=false;
     ui->dateD->setDate(QDate::currentDate());
    if(msg=="")
    msg="date debut superieur a la date actuelle";
    }
    if(ui->dateF->date()<ui->dateD->date())
    {
        test=false;
             ui->dateF->setDate(ui->dateD->date());
            if(msg=="")
            msg="date debut superieur a la date fin";
    }
    if((v.toInt()>80)||(v.toInt()<5)||(v.length()==0))
    {
        test=false;
        ui->valeur->setText("");
        if(msg=="")
        msg="valeur du promotion doit etre entre 5 et 80";
    }
    if(test==false)
    {
       QMessageBox::critical(this,"warning",msg);
    }
    else
     {promotion p(dateD,dateF,v,id);
        if(p.ajouter())
        {QMessageBox::information(this,"information","promotion ajouté");
         QSqlQuery q=tmpcl.getMails();
         q.exec();
         while(q.next())
         {
             SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

                        smtp.setUser("rentcar908@gmail.com");
                        smtp.setPassword("rentcar123");


                        MimeMessage message;

                        message.setSender(new EmailAddress("rentcar908@gmail.com", "Rent Car"));

                        message.addRecipient(new EmailAddress(q.value(0).toString(),"Rent Car"));
                        message.setSubject("Nouvelle Promotion");
                        MimeText text;
                        text.setText("une nouvelle promotion de "+v+"% est disponible a Rent Car de "+dateD+" jusqu'a "+dateF+" pour une voiture de marque "+marque);
                        message.addPart(&text);
                        smtp.connectToHost();
                        smtp.login();
                        smtp.sendMail(message);
                        smtp.quit();
         }
        }
        ui->tableV_2->setModel(tmppro.afficher(rechP));
    }
}

void gestionStock::on_rechV_textEdited(const QString &arg1)
{
    rechv=arg1;
    ui->tableV->setModel(tmppro.afficherV(rechv));
}

void gestionStock::on_rechV_3_textEdited(const QString &arg1)
{
    rechP=arg1;
    ui->tableV_2->setModel(tmppro.afficher(rechP));
}

void gestionStock::on_suppP_clicked()
{
    QItemSelectionModel *select = ui->tableV_2->selectionModel();
    QModelIndexList list;
    if(select->hasSelection())
    list=select->selectedRows();
    for(int i=0; i< list.count(); i++)
    {
       tmppro.supprimer(list[i].data().toInt());
    }
    ui->tableV_2->setModel(tmppro.afficher(rechP));
}

void gestionStock::on_retour_clicked()
{
 ui->stackedWidget->setCurrentIndex(0);
}

void gestionStock::on_tableV_2_doubleClicked(const QModelIndex &index)
{
    ui->modif->setEnabled(true);
    ui->ajouterP->setDisabled(true);
    id2=ui->tableV_2->model()->data(index).toInt();
    promotion p=tmppro.remplir(id2);
    ui->dateD->setDate(QDate::fromString(p.get_date_debut(),"dd/MM/yyyy"));
    ui->dateF->setDate(QDate::fromString(p.get_date_fin(),"dd/MM/yyyy"));
    ui->valeur->setText(p.get_valeur());
}

void gestionStock::on_modif_clicked()
{QModelIndex index = ui->tableV->currentIndex();
    int idv = index.data(Qt::DisplayRole).toInt();
    promotion p(ui->dateD->date().toString("dd/MM/yyyy"),ui->dateF->date().toString("dd/MM/yyyy"),ui->valeur->text(),idv);
    if(tmppro.modifier(p,id2))
    {
       ui->dateD->setDate(QDate::currentDate());
       ui->dateF->setDate(QDate::currentDate());
       ui->valeur->clear();
       ui->ajouterP->setEnabled(true);
       ui->modif->setDisabled(true);
       ui->tableV_2->setModel(tmppro.afficher(rechP));
       QMessageBox::information(this,"information","promotion modifié");
       ui->tableV_2->setModel(tmppro.afficher(rechP));
    }
    else
    QMessageBox::critical(this,"erreur","erreur de modification");
}

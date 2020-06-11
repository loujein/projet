#include "mecanicien.h"
#include <QDebug>
#include "connexion.h"
mecanicien::mecanicien()
{
cin="";
nom="";
prenom="";
adresse="";
ville="";
gendre="";
tel="";
}
mecanicien::mecanicien(QString cin,QString nom,QString prenom,QString adresse,QString ville,QString gendre,QString tel)
{
  this->cin=cin;
  this->nom=nom;
  this->prenom=prenom;
  this->adresse=adresse;
  this->ville=ville;
  this->gendre=gendre;
  this->tel=tel;
}
QString mecanicien::get_nom(){return  nom;}
QString mecanicien::get_prenom(){return prenom;}
int mecanicien::get_id(){return  id;}
QString mecanicien::get_cin(){return  cin;}
QString mecanicien::get_adresse(){return  adresse;}
QString mecanicien::get_ville(){return  ville;}
QString mecanicien::get_gendre(){return  gendre;}
QString mecanicien::get_tel(){return  tel;}
bool mecanicien::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO mecanicien (cin,nom,prenom,gendre,adresse,ville,tel) "
                    "VALUES (:cin,:nom,:prenom,:gendre,:adresse,:ville,:tel)");
query.bindValue(":cin", this->cin);
query.bindValue(":nom", this->nom);
query.bindValue(":prenom", this->prenom);
query.bindValue(":gendre", this->gendre);
query.bindValue(":adresse", this->adresse);
query.bindValue(":ville", this->ville);
query.bindValue(":tel", this->tel);
return    query.exec();
}

QSqlQueryModel * mecanicien::afficher(int n)
{QSqlQueryModel * model= new QSqlQueryModel();
    switch(n)
    {
    case 0:model->setQuery("select cin,nom,prenom,gendre,adresse,ville,tel from mecanicien order by nom ASC");break;
    case 1:model->setQuery("select cin,nom,prenom,gendre,adresse,ville,tel from mecanicien order by prenom ASC");break;
    case 2:model->setQuery("select cin,nom,prenom,gendre,adresse,ville,tel from mecanicien order by ville ASC");break;
    default:model->setQuery("select cin,nom,prenom,gendre,adresse,ville,tel from mecanicien");
    }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("gendre"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ville"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("tel"));

    return model;
}

bool mecanicien::modifier(QString cin)
{
QSqlQuery query;
query.prepare("update mecanicien set cin=:cin,nom=:nom,prenom=:prenom,gendre=:gendre,adresse=:adresse,ville=:ville,tel=:tel where cin = :cin ");
query.bindValue(":cin", cin);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":gendre", gendre);
query.bindValue(":adresse", adresse);
query.bindValue(":ville", ville);
query.bindValue(":tel", tel);
return    query.exec();
}
bool mecanicien::supprimer(QString cinn)
{
QSqlQuery query,q;
query.prepare("Delete from mecanicien where cin = :cinn ");
query.bindValue(":cinn", cinn);
return    query.exec();
}
mecanicien mecanicien::getMecanicien(QString cin)
{QSqlQuery query;
    query.prepare("select cin,nom,prenom,adresse,ville,gendre,tel from mecanicien where cin = :cinn ");
    query.bindValue(":cinn", cin);
    query.exec();
    query.first();
   mecanicien m(query.value(0).toString(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString(),query.value(4).toString(),query.value(5).toString(),query.value(6).toString());
   return m;
}

#include "location.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
location::location()
{
  prix="";
  res_entretien="";
  id_client=0;
  id_compte=0;
  id_client=0;
}

location::location(QString prix,QString res_entretien,int id_client,int id_voiture,int id_compte,QDate date_debut,QDate date_fin)
{
    this->prix=prix;
    this->res_entretien=res_entretien;
    this->id_client=id_client;
    this->id_voiture=id_voiture;
    this->id_compte=id_compte;
    this->date_debut=date_debut;
    this->date_fin=date_fin;
}

int location::get_id(){return id;}
QString location::get_prix(){return prix;}
QString location::get_res(){return res_entretien;}
int location::get_id_client(){return id_client;}
int location::get_id_voiture(){return id_voiture;}
int location::get_id_compte(){return id_client;}
QDate location::get_datedebut(){return date_debut;}
QDate location::get_datefin(){return date_fin;}

bool location::ajouter()
{
    QSqlQuery query;
    //QString res= QString::number(id);
    query.prepare("INSERT INTO location (id,prix,res_entretien,id_client,id_voiture,id_compte,date_debut,date_fin)"
                  "VALUES (null, :prix, :res_entretien, :id_client, :id_voiture, :id_compte, :date_debut, :date_fin)");
    query.bindValue(":prix",prix);
    query.bindValue(":res_entretien",res_entretien);
    query.bindValue(":id_client",id_client);
    query.bindValue(":id_voiture",id_voiture);
    query.bindValue(":id_compte",id_compte);
    query.bindValue(":date_debut",date_debut);
    query.bindValue(":date_fin",date_fin);
    return query.exec();

}

QSqlQueryModel * location::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from location");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("RES_ENTRETIEN"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID_CLIENT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_VOITURE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_COMPTE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DATE_DEBUT"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DATE_FIN"));
    return model;
}

bool location::modifier(int id)
{
    QSqlQuery query;
    //QString res= QString::number(idd);
    query.prepare("Update location set prix = :prix , res_entretien = :res_entretien , id_client = :id_client , id_voiture = :id_voiture , id_compte = :id_compte , date_debut = :date_fin where id= :id");
    query.bindValue(":id",id);
    query.bindValue(":prix",prix);
    query.bindValue(":res_entretien",res_entretien);
    query.bindValue(":id_client",id_client);
    query.bindValue(":id_voiture",id_voiture);
    query.bindValue(":id_compte",id_compte);
    query.bindValue(":date_debut",date_debut);
    query.bindValue(":date_fin",date_fin);
    return query.exec();

}
bool location::supprimer(int id)
{
    QSqlQuery query;
    //QString res= QString::number(id);
    query.prepare("Delete from location where id = :id ");
    query.bindValue(":id", id);
    return    query.exec();
}

QSqlQueryModel * location::recherche(int id)
{
    QSqlQuery query;
    QSqlQueryModel * model=new QSqlQueryModel();
    QString res= QString::number(id);
    model->setQuery("select * from location where id like id");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("RES_ENTRETIEN"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID_CLIENT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_VOITURE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_COMPTE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DATE_DEBUT"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DATE_FIN"));
            return model;

}
QSqlQueryModel* location::tri()
{

    QSqlQuery * q = new  QSqlQuery ();
    QSqlQueryModel * model = new  QSqlQueryModel ();
    q->prepare("SELECT * FROM location ORDER BY ID");
    q->exec();
    model->setQuery(*q);
    return model;
}

QSqlQueryModel* location::tri2()
{

    QSqlQuery * q = new  QSqlQuery ();
    QSqlQueryModel * model = new  QSqlQueryModel ();
    q->prepare("SELECT * FROM location ORDER BY ID desc");
    q->exec();
    model->setQuery(*q);
    return model;
}

void location::recherchee(QTableView *table,int n)
{
QString res=QString::number(n);
QSqlQueryModel *model=new QSqlQueryModel() ;
QSqlQuery qry ;
qry.prepare("Select * from location where (regexp_like(ID,:id))");
qry.bindValue(":id",res);
qry.exec() ;
model->setQuery(qry) ;
table->setModel(model) ;
table->show() ;
}
double location::prixTot(int n,int idv)
{int nb=0;
    QSqlQuery qry ;
    qry.prepare("Select prix_jour from voiture where id=:idv");
    qry.bindValue(":idv",idv);
    qry.exec() ;
    qry.first();
    return qry.value(0).toDouble()*n;
}
double location::prixF(double p,int idv)
{int nb=0;
    QSqlQuery qry ;
    qry.prepare("select max(valeur) from promotion where (SYSDATE between dates and dateF) and id_voiture=:idv");
    qry.bindValue(":idv",idv);
    qry.exec() ;
    while(qry.next())
    {
        nb++;
    }
    qry.first();
    if (nb==0)
        return p;
    else
    {qDebug()<<"here";
    return (p*(1-(qry.value(0).toDouble()/100.0)));
    }
}
int location::getClient(QString cin)
{
    QSqlQuery qry ;
    qry.prepare("Select id from client where cin=:idv");
    qry.bindValue(":idv",cin);
    qry.exec();
    qry.first();
    return qry.value(0).toInt();
 }
int location::getVoiture(QString mat)
{
    QSqlQuery qry ;
    qry.prepare("Select id from voiture where matricule=:idv");
    qry.bindValue(":idv",mat);
    qry.exec();
    qry.first();
    return qry.value(0).toInt();
 }
int location::getAgent(QString cin)
{
    QSqlQuery qry ;
    qry.prepare("Select c.id from compte c inner join employe e on c.id_agent=e.id where e.cin=:idv");
    qry.bindValue(":idv",cin);
    qry.exec();
    qry.first();
    return qry.value(0).toInt();
 }

#include "employe.h"
#include <QSqlQuery>

employe::employe()
{
    cin="";
    nom="";
    prenom="";
    salaire="";
    gendre="";
    departement="";
    ville="";
    adresse="";
    image="";
    id_agence=0;
}

employe::employe(QString cin,QString nom,QString prenom,QString salaire,QString gendre,QString departement,QString ville,QString adresse,QString image,int id_agence,QDate date_ajout)
{
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->salaire=salaire;
    this->gendre=gendre;
    this->departement=departement;
    this->ville=ville;
    this->adresse=adresse;
    this->image=image;
    this->id_agence=id_agence;
    this->date_ajout=date_ajout;
}

int employe::get_id(){return id;}
QString employe::get_cin(){return cin;}
QString employe::get_nom(){return nom;}
QString employe::get_prenom(){return prenom;}
QString employe::get_salaire(){return salaire;}
QString employe::get_gendre(){return gendre;}
QString employe::get_departement(){return departement;}
QString employe::get_ville(){return ville;}
QString employe::get_adresse(){return adresse;}
QString employe::get_image(){return image;}
int employe::get_idagence(){return id_agence;}
QDate employe::get_dateajout(){return date_ajout;}


bool employe::ajouter()
{
    QSqlQuery query;
    //QString res= QString::number(id);
    query.prepare("INSERT INTO employe (id,cin,nom,prenom,salaire,gendre,departement,ville,adresse,image,id_agence,date_ajout)"
                  "VALUES (null, :cin, :nom, :prenom, :salaire, :gendre, :departement, :ville, :adresse, :image, :id_agence, :date_ajout)");
    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":salaire",salaire);
    query.bindValue(":gendre",gendre);
    query.bindValue(":departement",departement);
    query.bindValue(":ville",ville);
    query.bindValue(":adresse",adresse);
    query.bindValue(":image",image);
    query.bindValue(":id_agence",id_agence);
    query.bindValue(":date_ajout",date_ajout);
    return query.exec();

}

QSqlQueryModel * employe::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from employe");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("GENDRE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DEPARTEMENT"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("IMAGE"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("ID_AGENCE"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("DATE_AJOUT"));
    return model;
}

bool employe::modifier(int id)
{
    QSqlQuery query;
    //QString res= QString::number(idd);
    query.prepare("Update employe set cin = :cin , nom = :nom , prenom = :prenom , salaire = :salaire , gendre = :gendre , departement = :departement , ville = :ville , adresse = :adresse , image = :image , id_agence = :id_agence , date_ajout = :date_ajout where id= :id");
    query.bindValue(":id",id);
    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":salaire",salaire);
    query.bindValue(":gendre",gendre);
    query.bindValue(":departement",departement);
    query.bindValue(":ville",ville);
    query.bindValue(":adresse",adresse);
    query.bindValue(":image",image);
    query.bindValue(":id_agence",id_agence);
    query.bindValue(":date_ajout",date_ajout);
    return query.exec();

}
bool employe::supprimer(int id)
{
    QSqlQuery query;
    //QString res= QString::number(id);
    query.prepare("Delete from employe where id = :id ");
    query.bindValue(":id", id);
    return    query.exec();
}

QSqlQueryModel * employe::recherche(QString nom)
{
    QSqlQuery query;
    QSqlQueryModel * model=new QSqlQueryModel();
    //QString res= QString::number(id);
    model->setQuery("select * from employe where nom like '"+nom+"'  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("GENDRE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DEPARTEMENT"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("IMAGE"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("ID_AGENCE"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("DATE_AJOUT"));
            return model;

}
QSqlQueryModel* employe::tri()
{

    QSqlQuery * q = new  QSqlQuery ();
    QSqlQueryModel * model = new  QSqlQueryModel ();
    q->prepare("SELECT * FROM employe ORDER BY ID");
    q->exec();
    model->setQuery(*q);
    return model;
}

QSqlQueryModel* employe::tri2()
{

    QSqlQuery * q = new  QSqlQuery ();
    QSqlQueryModel * model = new  QSqlQueryModel ();
    q->prepare("SELECT * FROM employe ORDER BY ID desc");
    q->exec();
    model->setQuery(*q);
    return model;
}

void employe::recherchee(QTableView *table,QString n)
{
//QString res=QString::number(n);
QSqlQueryModel *model=new QSqlQueryModel() ;
QSqlQuery qry ;
qry.prepare("Select * from employe where (regexp_like(NOM,:nom))");
qry.bindValue(":nom",n);
qry.exec() ;
model->setQuery(qry) ;
table->setModel(model) ;
table->show() ;
}


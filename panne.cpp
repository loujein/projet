#include "panne.h"
#include <QDebug>
#include "connexion.h"
panne::panne()
{
res=0;
id_voiture=0;
id_mecanicien=0;
dateD="";
dateF="";
prix="";
}
panne::panne(int id_voiture,int id_mecanicien,int res,QString dateD,QString dateF,QString prix)
{this->dateD=dateD;
    this->dateF=dateF;
  this->res=res;
  this->prix=prix;
  this->id_voiture=id_voiture;
  this->id_mecanicien=id_mecanicien;
}
int panne::get_res(){return  res;}
int panne::get_id(){return  id;}
int panne::get_id_voiture(){return  id_voiture;}
int panne::get_id_mecanicien(){return  id_mecanicien;}
QString panne::get_prix(){return  prix;}
QString panne::get_dateD(){return  dateD;}
QString panne::get_dateF(){return  dateF;}
bool panne::ajouter()
{
QSqlQuery query,q,que;
query.prepare("INSERT INTO panne (id_voiture,id_mecanicien,date_debut,prix,resultat) "
                    "VALUES (:idv,:idm,SYSDATE,:prix,:res)");
q.prepare("update voiture set etat='en panne' where id = :idv ");
que.prepare("update reclamation set res=1 where id_voiture = :idv ");
query.bindValue(":prix", prix);
query.bindValue(":idv", id_voiture);
q.bindValue(":idv", id_voiture);
que.bindValue(":idv", id_voiture);
query.bindValue(":idm", id_mecanicien);
query.bindValue(":res", res);
q.exec();
que.exec();
return    query.exec();
}

QSqlQueryModel * panne::afficher(int index)
{QSqlQueryModel * model= new QSqlQueryModel();
    switch(index)
    {
    case 2:model->setQuery("select p.id,p.date_debut,p.prix,p.date_fin,v.matricule,concat(m.nom,concat(' ',m.prenom)) from panne p inner join voiture v on p.id_voiture=v.id inner join mecanicien m on p.id_mecanicien=m.id where p.resultat=0");break;
    case 1:model->setQuery("select p.id,p.date_debut,p.prix,p.date_fin,v.matricule,concat(m.nom,concat(' ',m.prenom)) from panne p inner join voiture v on p.id_voiture=v.id inner join mecanicien m on p.id_mecanicien=m.id where p.resultat=1");break;
    default:model->setQuery("select p.id,p.date_debut,p.prix,p.date_fin,v.matricule,concat(m.nom,concat(' ',m.prenom)) from panne p inner join voiture v on p.id_voiture=v.id inner join mecanicien m on p.id_mecanicien=m.id");
    }
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num d'enregistrement"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("date d'enregistrement"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("date de reglage"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("matricule"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("mecanicien"));
    return model;
}
QSqlQueryModel * panne::afficherV(QString ch)
{QSqlQueryModel * model= new QSqlQueryModel();
    if(ch=="")
    model->setQuery("select v.matricule,count(*) as nbr from voiture v inner join reclamation r on v.id=r.id_voiture where r.res=0 group by v.matricule order by nbr desc;");
    else
    model->setQuery("select v.matricule,count(*) as nbr from voiture v inner join reclamation r on v.id=r.id_voiture where r.res=0 AND matricule like '"+ch+"%' group by v.matricule order by nbr desc;");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Matricule"));

    return model;
}
QSqlQueryModel * panne::afficherM(QString ch)
{QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select concat(nom,concat(' ',prenom)) from mecanicien where concat(nom,concat(' ',prenom)) like '"+ch+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("mecanicien"));
    return model;
}
bool panne::supprimer(int id)
{
QSqlQuery query;
query.prepare("Delete from panne where id = :id");
query.bindValue(":id",id);
return    query.exec();
}
int panne::chercher_id_voiture(QString matricule)
{
    QSqlQuery query;
    query.prepare("select id from voiture where matricule = :matricule ");
    query.bindValue(":matricule",matricule);
    query.exec();
    query.first();
 int id = query.value(0).toInt();
    return id;
}
int panne::chercher_id_mecanicien(QString m)
{
    QSqlQuery query;
    query.prepare("select id from mecanicien where concat(nom,concat(' ',prenom)) = :m ");
    query.bindValue(":m",m);
    query.exec();
    query.first();
    int id = query.value(0).toInt();
    return id;
}
bool panne::modifier(int id)
{
    QSqlQuery query,q;
    query.prepare("update panne set resultat=:r,date_fin=SYSDATE where id = :id ");
    q.prepare("update voiture set etat='libre' where id in (select id_voiture from panne where id=:id) ");
    query.bindValue(":r",1);
    q.bindValue(":id",id);
    query.bindValue(":id",id);
    q.exec();
    return  query.exec();
}
QVector<QString> panne::tabMarque()
{int i=0;
  QVector<QString> t;
    QSqlQuery query;
    query.prepare("select count(*) as nbr,v.marque from panne p inner join voiture v on v.id=p.id_voiture group by v.marque order by nbr DESC");
    query.exec();
    while((query.next())&&(i<7))
    {
        i++;
        t.push_back(query.value(1).toString());
    }
    return t;
}
QVector<double> panne::tabNbr()
{int i=0;
  QVector<double> t;
    QSqlQuery query;
    query.prepare("select count(*) as nbr,v.marque from panne p inner join voiture v on v.id=p.id_voiture group by v.marque order by nbr DESC");
    query.exec();
    while((query.next())&&(i<7))
    {
        i++;
        t.push_back(query.value(0).toDouble());
    }
    return t;
}
QVector<QString> panne::tabMarque2()
{int i=0;
  QVector<QString> t;
    QSqlQuery query;
    query.prepare("select count(*) as nbr,v.marque from reclamation p inner join voiture v on v.id=p.id_voiture group by v.marque order by nbr DESC");
    query.exec();
    while((query.next())&&(i<7))
    {
        i++;
        t.push_back(query.value(1).toString());
    }
    return t;
}
QVector<double> panne::tabNbr2()
{int i=0;
  QVector<double> t;
    QSqlQuery query;
    query.prepare("select count(*) as nbr,v.marque from reclamation p inner join voiture v on v.id=p.id_voiture group by v.marque order by nbr DESC");
    query.exec();
    while((query.next())&&(i<7))
    {
        i++;
        t.push_back(query.value(0).toDouble());
    }
    return t;
}

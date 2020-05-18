#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QDateEdit>
#include <QDate>
#include <QSqlQueryModel>
#include <QTableView>

class employe
{
public:
    employe();
    employe(QString,QString,QString,QString,QString,QString,QString,QString,QString,int,QDate);
    int get_id();
    QString get_cin();
    QString get_nom();
    QString get_prenom();
    QString get_salaire();
    QString get_gendre();
    QString get_departement();
    QString get_ville();
    QString get_adresse();
    QString get_image();
    int get_idagence();
    QDate get_dateajout();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier (int);
    QSqlQueryModel * recherche(QString);
    QSqlQueryModel* tri();
    QSqlQueryModel* tri2();
    void recherchee(QTableView *table,QString n);
private:
    int id,id_agence;
    QString cin,nom,prenom,gendre,departement,ville,adresse,image,salaire;
    QDate date_ajout;
};

#endif // EMPLOYE_H

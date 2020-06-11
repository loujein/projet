#ifndef MECANICIEN_H
#define MECANICIEN_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class mecanicien
{public:
    mecanicien();
    mecanicien(QString,QString,QString,QString,QString,QString,QString);
    int get_id();
    QString get_cin();
    QString get_nom();
    QString get_prenom();
    QString get_gendre();
    QString get_adresse();
    QString get_ville();
    QString get_tel();
    bool ajouter();
    QSqlQueryModel * afficher(int n);
    QSqlQueryModel * afficherDesc(int n);
    bool modifier(QString);
    bool supprimer(QString);
    mecanicien getMecanicien(QString cin);
private:
    QString nom,prenom,cin,gendre,adresse,ville,tel;
    int id;
};

#endif // ETUDIANT_H

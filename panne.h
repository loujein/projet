#ifndef PANNE_H
#define PANNE_H
#include <QString>
#include <QVector>
#include <QSqlQuery>
#include <QSqlQueryModel>
class panne
{public:
    panne();
    panne(int,int,int,QString,QString,QString);
    int get_id();
    int get_res();
    QString get_dateD();
    QString get_dateF();
    QString get_prix();
    int get_id_voiture();
    int get_id_mecanicien();
    bool ajouter();
    int chercher_id_voiture(QString);
    int chercher_id_mecanicien(QString);
    QSqlQueryModel * afficherV(QString);
    QSqlQueryModel * afficherM(QString);
    QSqlQueryModel * afficher(int);
    bool modifier(int);
    bool supprimer(int);
    int nombrePan();
    QVector<QString> tabMarque();
    QVector<double> tabNbr();
    QVector<QString> tabMarque2();
    QVector<double> tabNbr2();
private:
    QString prix,dateD,dateF;
    int id,id_voiture,id_mecanicien,res;

};
#endif // PANNE_H

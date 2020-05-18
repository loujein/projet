#ifndef LOCATION_H
#define LOCATION_H
#include<QString>
#include<QDate>
#include<QSqlQueryModel>
#include<QTableView>

class location
{
public:
    location();
    location(QString,QString,int,int,int,QDate,QDate);
    int get_id();
    QString get_prix();
    QString get_res();
    int get_id_client();
    int get_id_voiture();
    int get_id_compte();
    QDate get_datedebut();
    QDate get_datefin();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier (int);
    QSqlQueryModel * recherche(int);
    QSqlQueryModel* tri();
    QSqlQueryModel* tri2();
    void recherchee(QTableView *table,int n);
    double prixTot(int,int);
    double prixF(double p, int idv);
    int getClient(QString cin);
    int getVoiture(QString mat);
    int getAgent(QString cin);
private:
    int id,id_client,id_voiture,id_compte;
    QString prix,res_entretien;
    QDate date_debut,date_fin;
};

#endif // LOCATION_H

#include "connexion.h"

Connexion::Connexion()
{}

bool Connexion::ouvrirConnexion()
{
bool test=false;
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("elyes");
db.setUserName("elyes");//inserer nom de l'utilisateur
db.setPassword("elyes");//inserer mot de passe de cet utilisateur


if (db.open()) test = true;


return test;

}
void Connexion::fermerConnexion()
{db.close();}

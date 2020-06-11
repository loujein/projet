#ifndef GESTIONSTOCK_H
#define GESTIONSTOCK_H

#include <QMainWindow>
#include <QFileDialog>
#include "mecanicien.h"
#include "panne.h"
#include "client.h"
#include "evenement.h"
#include "voiture.h"
#include "promotion.h"
namespace Ui {
class gestionStock;
}

class gestionStock : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestionStock(QWidget *parent = nullptr);
    ~gestionStock();
private slots:
    void on_gestionPanne_clicked();

    void on_gestionMecanicien_clicked();

    void on_gestionVoiture_clicked();

    void on_ajouter_panne_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_suppPanne_clicked();

    void on_pushButton_7_clicked();

    void on_matrV_textEdited(const QString &arg1);

    void on_cinM_textEdited(const QString &arg1);

    void on_ajouterPanne_clicked();

    void on_modifierPan_clicked();

    void on_suppPan_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_6_clicked();

    void on_ajouterV_clicked();

    void on_suppV_clicked();

    void on_consulter_clicked();
    
    void on_rechAgence_textEdited(const QString &arg1);

    void on_pushButton_clicked();

    void on_deconnecter_clicked();

    void on_menu_clicked();

    void on_tableMecanicien_activated(const QModelIndex &index);
    void on_participer_clicked();
    
    void on_gestionPromotion_clicked();

    void on_ajouterP_clicked();

    void on_rechV_textEdited(const QString &arg1);

    void on_rechV_3_textEdited(const QString &arg1);

    void on_suppP_clicked();

    void on_retour_clicked();

    void on_tableV_2_doubleClicked(const QModelIndex &index);

    void on_modif_clicked();

public slots:
    void authentification(QString pseudo,QString passe);
private:
    Ui::gestionStock *ui;
    panne tabPanne;
    panne tabRechV;
    panne tabRechM;
    mecanicien tabMecanicien;
    VOITURE tabVoiture;
    evenement tmpevent;
    promotion tmppro;
    client tmpcl;
    int id;
};

#endif // GESTIONSTOCK_H

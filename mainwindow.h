#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"
#include <QMainWindow>
#include "location.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_7_clicked();


    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_12_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

    void on_lineEdit_7_textChanged(const QString &arg1);

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_11_clicked();



    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_tableView_2_activated(const QModelIndex &index);

    void on_tableemp_activated(const QModelIndex &index);

    void on_pushButton_14_clicked();


private:
    Ui::MainWindow *ui;
    employe tmpemp;
    location tmploc;
};
#endif // MAINWINDOW_H

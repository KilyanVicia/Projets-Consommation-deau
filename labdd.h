#ifndef LABDD_H
#define LABDD_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>



class laBDD : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> perso READ getimage CONSTANT)
    Q_PROPERTY(QList<QString> prenom READ getprenom CONSTANT)
    Q_PROPERTY (QVariantMap user READ getUser CONSTANT)
    Q_PROPERTY(QList<float> ec READ getEc CONSTANT)
    Q_PROPERTY(QList<float> ef READ getEf CONSTANT)
public:
    explicit laBDD(QObject *parent = nullptr);
    ~laBDD();
    void recupUtilisateur();
    void getutilisateur();
    Q_INVOKABLE void InBdd(float enbddec, float enbddef, bool jourOrNot);
    Q_INVOKABLE void informationUser(QString connectedUser);
    Q_INVOKABLE void gestionCharts(bool jourOrNot);
    void chartJours();
    void chartMois();
    QList<QString> getimage(){return utilsateurImage;}
    QList<QString> getprenom(){return utilsateurPrenom;}
    QVariantMap getUser(){return connected;}
    QList<float> getEc(){return ec;}
    QList<float> getEf(){return ef;}

private:
    QSqlDatabase Mybdd;
    QList<QString> utilsateurImage;
    QList<QString> utilsateurPrenom;
    QVariantMap connected;
    QList<float> eauChaude;
    QList<float> eauFroide;
    QList<QDateTime> eauHeure;
    QList<float> ec;
    QList<float> ef;
    float enbddec;
    float enbddef;





signals:
    void joursAndMois();
    void deuxCharts();
    void noChartJourAndMois();
    void mois();
    void jours();
    void consoTempsReel(float ec, float ef, int placeDansCharts);
};



#endif // LABDD_H

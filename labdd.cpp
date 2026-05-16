#include "labdd.h"
#include <ctime>
#include <QDateTime>
#include <bitset>

laBDD::laBDD(QObject *parent)
    : QObject{parent}
{
    Mybdd = QSqlDatabase::addDatabase("QMYSQL");
    Mybdd.setHostName("172.16.17.10");
    Mybdd.setDatabaseName("Consdeau");
    Mybdd.setUserName("Admin");
    Mybdd.setPassword("Admin1234");

    if (!Mybdd.open()) {
        qDebug() << "Erreur connexion BDD :" << Mybdd.lastError().text();
    }
    else{
        qDebug() << "Connexion MySQL réussie !";
        recupUtilisateur();
    }

}


laBDD::~laBDD()
{
    if (Mybdd.isOpen()) {
        Mybdd.close();
    }
}

void laBDD::recupUtilisateur()
{
    QSqlQuery query(Mybdd);
    query.exec("SELECT prenom, avatar FROM utilisateurs");

    if(!query.exec())       // -> returns true
    {
        qDebug() << "test";
    }

    while (query.next()) {
        utilsateurPrenom.append(query.value("prenom").toString());
        utilsateurImage.append(query.value("avatar").toString());
        //qDebug() << "-------" << utilsateurPrenom;
        //qDebug() << "-------" << utilsateurImage;
    }
}

void laBDD::informationUser(QString connectedUser)
{


    QSqlQuery query(Mybdd);
    query.prepare("SELECT avatar, configuration, seuilAVisuelle, seuilASonore, seuilCoupure, Id FROM utilisateurs WHERE `utilisateurs`.`prenom` = :connectedUser;");
    query.bindValue(":connectedUser", connectedUser);
    query.exec();
    query.next();
    connected["prenom"] = connectedUser;
    int configuration = query.value("configuration").toInt();
    connected["img"] = query.value("avatar").toString();
    connected["visuel"] = query.value("seuilAVisuelle").toInt();
    connected["sonor"] = query.value("seuilASonore").toInt();
    connected["coupure"] = query.value("seuilCoupure").toInt();
    connected["id"] = query.value("Id").toInt();
    std::bitset<8> bits(configuration);
    QList <bool> config;
    for(int i = 0; i < 8 ; i++){
        config.append(bits.test(i));
    }
    if(config[2] == true){
        emit deuxCharts();
        if(config[0] == true && config[1] == true){
            gestionCharts(true);
            emit joursAndMois();
        }
        else if(config[0] == true && config[1] == false){
            gestionCharts(true);
        }
        else if (config[0] == false && config[1] == true){
            gestionCharts(false);
        }
        else{
            emit noChartJourAndMois();
            gestionCharts(true);
        }
    }
    else{
        if(config[0] == true && config[1] == true){
            emit joursAndMois();
            gestionCharts(true);
        }
        else if(config[0] == true && config[1] == false){
            gestionCharts(true);
        }
        else if(config[0] == false && config[1] == true){
            gestionCharts(false);
        }
        else{
            emit noChartJourAndMois();
        }
    }
}

void laBDD::gestionCharts(bool jourOrNot)
{
    qDebug() << "---gestionCharts";

    // std::time_t ajd = std::time(nullptr);
    // std::tm* dateReel = std::localtime(&ajd);
    QDateTime dateTimeActuel = QDateTime::currentDateTime();
    QSqlQuery query(Mybdd);

    if(jourOrNot == true){
        query.prepare("SELECT consommation_xx_yyyy.consoEauFroide , consommation_xx_yyyy.consoEauChaude, consommation_xx_yyyy.heure FROM consommation_xx_yyyy INNER JOIN utilisateurs ON utilisateurs.Id = consommation_xx_yyyy.idUtilisateur WHERE utilisateurs.prenom = :prenom AND DAY(heure) = :date;");
        query.bindValue(":prenom", connected["prenom"]);
        QString format = "dd";
        query.bindValue(":date", dateTimeActuel.toString(format).toInt());
    }
    else{
        qDebug() << "---gestionCharts else";
        query.prepare("SELECT consommation_xx_yyyy.consoEauFroide , consommation_xx_yyyy.consoEauChaude, consommation_xx_yyyy.heure FROM consommation_xx_yyyy INNER JOIN utilisateurs ON utilisateurs.Id = consommation_xx_yyyy.idUtilisateur WHERE utilisateurs.prenom = :prenom AND MONTH(heure) = :date;");
        query.bindValue(":prenom", connected["prenom"]);
        QString format = "MM";
        qDebug() << dateTimeActuel.toString(format).toInt();
        query.bindValue(":date", dateTimeActuel.toString(format).toInt());
    }





    query.exec();
    eauFroide.clear();
    eauChaude.clear();
    eauHeure.clear();
    while (query.next()) {
        eauFroide.append(query.value("consoEauFroide").toFloat());
        eauChaude.append(query.value("consoEauChaude").toFloat());
        eauHeure.append(query.value("heure").toDateTime());
        //qDebug() << query.value("heure").toDateTime();

    }

    if(jourOrNot == true){
        chartJours();
    }
    else{
        chartMois();
    }

}

 void laBDD::chartJours()
{
    qDebug() << "---chartJours";

    QString format = "hh";
    int date;
    float ec1 = 0.0f, ef1 = 0.0f, ec2 = 0.0f, ef2 = 0.0f, ec3 = 0.0f, ef3 = 0.0f, ec4 = 0.0f, ef4 = 0.0f, ec5 = 0.0f, ef5 = 0.0f, ec6 = 0.0f, ef6 = 0.0f;


    for(int i = 0 ; i < eauChaude.size(); i++){
        date = eauHeure[i].toString(format).toInt();
        if(date <= 4){
            ec1 += eauChaude[i];
            ef1 += eauFroide[i];
        }
        else if(date <= 8){
            ec2 += eauChaude[i];
            ef2 += eauFroide[i];
        }
        else if(date <= 12){
            ec3 += eauChaude[i];
            ef3 += eauFroide[i];
        }
        else if(date <= 16){
            ec4 += eauChaude[i];
            ef4 += eauFroide[i];
        }
        else if(date <= 20){
            ec5 += eauChaude[i];
            ef5 += eauFroide[i];
        }
        else if(date <= 24){
            ec6 += eauChaude[i];
            ef6 += eauFroide[i];
        }
    }
    ef.clear();
    ec.clear();

    ef << ef1 << ef2 << ef3 << ef4 << ef5 << ef6;
    ec << ec1 << ec2 << ec3 << ec4 << ec5 << ec6;
    emit jours();

}

void laBDD::chartMois()
{
    qDebug() << "--- chartMois";
    QString format = "dd";
    int date;
    float ec1 = 0.0f, ef1 = 0.0f, ec2 = 0.0f, ef2 = 0.0f, ec3 = 0.0f, ef3 = 0.0f, ec4 = 0.0f, ef4 = 0.0f, ec5 = 0.0f, ef5 = 0.0f, ec6 = 0.0f, ef6 = 0.0f;


    for(int i = 0 ; i < eauChaude.size(); i++){
        date = eauHeure[i].toString(format).toInt();
        if(date <= 5){
            ec1 += eauChaude[i];
            ef1 += eauFroide[i];
        }
        else if(date <= 10){
            ec2 += eauChaude[i];
            ef2 += eauFroide[i];
        }
        else if(date <= 15){
            ec3 += eauChaude[i];
            ef3 += eauFroide[i];
        }
        else if(date <= 20){
            ec4 += eauChaude[i];
            ef4 += eauFroide[i];
        }
        else if(date <= 25){
            ec5 += eauChaude[i];
            ef5 += eauFroide[i];
        }
        else if(date <= 31){
            ec6 += eauChaude[i];
            ef6 += eauFroide[i];
        }
    }
    ef.clear();
    ec.clear();

    ef << ef1 << ef2 << ef3 << ef4 << ef5 << ef6;
    ec << ec1 << ec2 << ec3 << ec4 << ec5 << ec6;
    emit mois();

}

void laBDD::InBdd(float enbddec, float enbddef, bool jourOrNot)
{
    qDebug() << "on passe en signal     "  << enbddec << "        " << enbddef;
    QSqlQuery query(Mybdd);
    QDateTime dateTimeActuel = QDateTime::currentDateTime();
    QString date = dateTimeActuel.toString("yyyy-MM-dd hh:mm:ss");
    query.prepare("INSERT INTO `consommation_xx_yyyy` (`idUtilisateur` , `heure`, `consoEauFroide`, `consoEauChaude`) VALUES (:leid , :ladate , :ef , :ec);");
    query.bindValue(":leid", connected["id"].toInt());
    query.bindValue(":ladate",date);
    query.bindValue(":ef" , enbddef);
    query.bindValue(":ec" , enbddec);
    qDebug() << "-------" << connected["id"] << date;
    qDebug() << "INSERT INTO `consommation_xx_yyyy` (`idUtilisateur` , `heure`, `consoEauFroide`, `consoEauChaude`) VALUES (" << connected["id"].toInt() << " , "<< date <<" , " << enbddef << " , " << enbddec << ");";
    query.exec();
    qDebug() << "Erreur connexion BDD :" << Mybdd.lastError().text();


    if(jourOrNot == true){
        qDebug() << "on true";
        int placeDansCharts;
        int testdate = dateTimeActuel.toString("hh").toInt();
        if(testdate <= 4){
            placeDansCharts = 0;
        }
        else if(testdate <= 8){
            placeDansCharts = 1;
        }
        else if(testdate <= 12){
            placeDansCharts = 2;
        }
        else if(testdate <= 16){
            placeDansCharts = 3;
        }
        else if(testdate <= 20){
            placeDansCharts = 4;
        }
        else if(testdate <= 24){
            placeDansCharts = 5;
        }
        qDebug() << placeDansCharts;


        emit consoTempsReel(enbddec, enbddef, placeDansCharts);

    }
    else{
        int placeDansCharts;
        qDebug() << "on false";

        int testdate = dateTimeActuel.toString("dd").toInt();
        qDebug() << testdate;
        if(testdate <= 5){
            placeDansCharts = 0;
        }
        else if(testdate <= 10){
            placeDansCharts = 1;
        }
        else if(testdate <= 15){
            placeDansCharts = 2;
        }
        else if(testdate <= 20){
            placeDansCharts = 3;
        }
        else if(testdate <= 25){
            placeDansCharts = 4;
        }
        else if(testdate <= 31){
            placeDansCharts = 5;
        }
        qDebug() << placeDansCharts;


        emit consoTempsReel(enbddec, enbddef, placeDansCharts);
    }

}

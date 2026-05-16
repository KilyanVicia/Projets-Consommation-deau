#include <QApplication>
#include <QQmlApplicationEngine>
#include "labdd.h"
#include "serveur.h"
#include <QQmlContext>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    laBDD uneBdd;
    serveur leserv;
    qDebug() << QSqlDatabase::drivers();
    engine.rootContext()->setContextProperty("bdd", &uneBdd);
    engine.rootContext()->setContextProperty("serveur", &leserv);
    qmlRegisterType<laBDD>("MonModule", 1, 0, "BDD");
    engine.load(QUrl("../../Main.qml"));

    return app.exec();
}

#ifndef SERVEUR_H
#define SERVEUR_H
#include "labdd.h"
#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QtWebSockets>

class serveur : public QObject {
Q_OBJECT



public:
    explicit serveur(QObject *parent = nullptr);
    void startServeur();
    void stopSeveur();
    Q_INVOKABLE void openElec();
    Q_INVOKABLE void closeElec();


private:
    QWebSocketServer *server;
    QWebSocket *client;
    bool etasServeeur;
    static QString test;

private slots:
    void Connection();
    void Message(QString message);
    void ClientDeco();

signals:
    void changClasse(float enbddec, float enbddef);




















};
#endif // SERVEUR_H

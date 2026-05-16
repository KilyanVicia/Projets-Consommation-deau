#include "serveur.h"
#include "labdd.h"

serveur::serveur(QObject *parent) : QObject(parent) {
    server = new QWebSocketServer(QStringLiteral("Serveur WS"), QWebSocketServer::NonSecureMode, this);
    client = new QWebSocket;
    startServeur();
}

void serveur::startServeur()
{
    etasServeeur = server->listen(QHostAddress::Any, 1234);
    if(etasServeeur == false){
        qDebug() << "problem";
    }
    else{
        qDebug() << "ces ok";
        connect(server, SIGNAL(newConnection()), this, SLOT(Connection()));
    }
}

void serveur::stopSeveur()
{
    disconnect(client, SIGNAL(textMessageReceived(QString)), this, SLOT(Message()));
    disconnect(client, SIGNAL(disconnected()), this, SLOT(ClientDeco()));
    disconnect(server, SIGNAL(newConnection()), this, SLOT(Connection()));
    server->close();
}

void serveur::openElec()
{
client -> sendTextMessage("OE");
}

void serveur::closeElec()
{
client -> sendTextMessage("FE");
}

void serveur::Connection()
{
    client = server->nextPendingConnection();
    connect(client, &QWebSocket::textMessageReceived, this, &serveur::Message);
    connect(client, SIGNAL(disconnected()), this, SLOT(ClientDeco()));

}

void serveur::Message(QString message)
{
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());
    if(socket){
        qDebug() << message;
        float efef;
        float ecec;
        if(message == "EF"){
            efef = 0.15;
            ecec = 0;
        }
        else if (message == "EC"){
            efef = 0;
            ecec = 0.15;
        }

        // qDebug() << efef << "    " << ecec;
        // if(efef > 0 || ecec > 0 ){
        //     qDebug() << "nombre supp";
        emit changClasse(ecec,efef);
        // }



    }
}

void serveur::ClientDeco()
{
    if (client != 0){
        client->deleteLater();
        //texte = tr("Un client vient de se déconnecter !");
    } else {
        qDebug("Pas de client à deconnecter !");
    }
}

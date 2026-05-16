#ifndef GESTION_H
#define GESTION_H

#include <QObject>
#include <QString>
#include <iostream>

class Gestion : public QObject
{
    Q_OBJECT
public:
    explicit Gestion(QObject *parent = nullptr);


private:
    QString userPrenom;
    QString userimg;

signals:
};

#endif // GESTION_H

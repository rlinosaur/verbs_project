#ifndef VERBS_DATABASE_H
#define VERBS_DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QObject>

#include "defines.h"




class VerbsDatabase : public QObject
{
    Q_OBJECT
public:
    explicit VerbsDatabase(QObject *parent = 0);
    void init(QString fileName="verbsbase.db");
    bool isOpen();
    bool close();
    bool deleteDatabase();
    bool createTables();
    QSqlDatabase getDb(){return db;}

    QString addVerb(QString verb,languageEnum lang);
    bool deleteVerb(QString verbId, languageEnum lang);
    bool addVerbEsConnection(QString verbEsId, QString verbConnId);
    bool cleanDatabase();
    bool changeVerb(QString verbId, QString newName, languageEnum lang);
private:
    QSqlDatabase db;
    QString fName;
    void mess(QString message);

    
signals:
    void sendMessage(QString message, MessageType messtype);
public slots:
    
};

#endif // VERBS_DATABASE_H

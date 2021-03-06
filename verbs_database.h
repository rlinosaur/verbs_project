#ifndef VERBS_DATABASE_H
#define VERBS_DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QObject>

#include "verbfunctions.h"
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
    bool createIndices();
    bool clearTable(QString tableName);
    bool transactionStart();
    bool transactionEnd();
    QSqlDatabase getDb(){return db;}

    QString addVerb(QString verb,languageEnum lang);
    bool deleteVerb(QString verbId, languageEnum lang);
    bool addVerbEsConnection(QString verbEsId, QString verbConnId);
    bool cleanDatabase();
    bool changeVerb(QString verbId, QString newName, languageEnum lang);
    bool createTensesEs();
    bool addTenseEs(int id, QString name, QString nameEn, QString nameRu);
    QString addVerbFormEs(QString verb_id,QString form,int tense,int pronoun);
    bool updateVerbFormEs(QString id,QString form);//остальное да будет вам известно.

    QString findVerbId(QString verb);
    bool verbEsConnectionExists(QString verbEsId,QString verbNoEsId);
    bool deleteVerbEsConnection(QString verbEsId, QString verbConnId);

    QString addEsExample(QString verbFormId, QString example);
    bool updateEsExampleTranslation(QString exampleId,QString translation,languageEnum lang);
    bool updateEsExample(QString exampleId,QString exampleNew);

private:
    QSqlDatabase db;
    QString fName;
    void mess(QString message);

    
signals:
    void sendMessage(QString message, MessageType messtype);
public slots:


    
};



#endif // VERBS_DATABASE_H

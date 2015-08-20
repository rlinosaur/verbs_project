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
    bool createTensesEs();
    bool addTenseEs(int id, QString name, QString nameEn, QString nameRu);
    QString addVerbFormEs(QString verb_id,QString form,int tense,int pronoun);
    bool updateVerbFormEs(QString id,QString form);//остальное да будет вам известно.
private:
    QSqlDatabase db;
    QString fName;
    void mess(QString message);

    
signals:
    void sendMessage(QString message, MessageType messtype);
public slots:


    
};

//Spanish verb Tenses
#define TENSE_NINGUNO                                   0
#define TENSE_PRESENTE                                  1
#define TENSE_PRETERITO_PERFECTO_COMPUESTO              2
#define TENSE_PRETERITO_IMPERFECTO                      3
#define TENSE_PRETERITO_PERFECTO_SIMPLE                 4
#define TENSE_PRETERITO_PLUSCAMPERFECTO                 5
#define TENSE_FUTURO                                    6
#define TENSE_FUTURO_PERFECTO                           7
#define TENSE_CONDICIONAL                               8
#define TENSE_CONDICIONAL_PERFECTO                      9
#define TENSE_PRETERITO_PERFECTO                        10
#define TENSE_SUBJUNCTIVO_PRESENTE                      11
#define TENSE_SUBJUNCTIVO_PRETERITO_PERFECTO            12
#define TENSE_SUBJUNCTIVO_PRETERITO_IMPERFECTO          13
#define TENSE_SUBJUNCTIVO_PRETERITO_IMPERFECTO_2        14
#define TENSE_SUBJUNCTIVO_PRETERITO_PLUSCUAMPERFECTO    15
#define TENSE_SUBJUNCTIVO_PRETERITO_PLUSCUAMPERFECTO_2  16
#define TENSE_SUBJUNCTIVO_FUTURO                        17
#define TENSE_SUBJUNCTIVO_FUTURO_PERFECTO               18
#define TENSE_IMPERATIVO                                19
#define TENSE_IMPERATIVO_NEGATIVO                       20

#define VERBFORM_INFINITIVO_PRESENTE                101
#define VERBFORM_INFINITIVO_COMPUESTO               102
#define VERBFORM_GERUNDIO_PRESENTE                  103
#define VERBFORM_GERUNDIO_COMPUESTO                 104
#define VERBFORM_PARTICIPIO                         105

//Spanish pronouns for verb forms
#define PRONOUN_NINGUNO     0
#define PRONOUN_YO          1
#define PRONOUN_TU          2
#define PRONOUN_EL          3
#define PRONOUN_NOSOTROS    4
#define PRONOUN_VOSOTROS    5
#define PRONOUN_ELLOS       6

#endif // VERBS_DATABASE_H

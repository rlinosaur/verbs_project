#include <QStringList>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QUuid>
#include <QFile>

#include "verbs_database.h"


/**
 * @brief VerbsDatabase::VerbsDatabase Unexpectable, but it's the class constructor
 * @param parent
 */
VerbsDatabase::VerbsDatabase(QObject *parent) :
    QObject(parent)
{

}
/**
 * @brief VerbsDatabase::deleteDatabase Deleting database
 * @return
 */
bool VerbsDatabase::deleteDatabase()
{
    if(this->isOpen())this->close();    
    return QFile::remove(fName);
}

/**
 * @brief VerbsDatabase::init Database opening
 * @param fileName
 */
void VerbsDatabase::init(QString fileName)
{

    QStringList drivers = QSqlDatabase::drivers();
    mess("Database initialization...");
    mess("Available drivers list:"+drivers.join(","));

    db = QSqlDatabase::addDatabase("QSQLITE", QUuid::createUuid().toRfc4122().toHex());
    db.setDatabaseName(fileName);
    db.setHostName("localhost");

    if(db.open())
    {
        fName=fileName;
    }
    else
    {
        mess("Last error"+db.lastError().databaseText()+",driver:"+db.lastError().driverText());
    }
}

/**
 * @brief VerbsDatabase::isOpen Check database is open
 * @return
 */
bool VerbsDatabase::isOpen()
{
    return db.isOpen();
}
/**
 * @brief VerbsDatabase::close Close database
 * @return
 */
bool VerbsDatabase::close()
{
    db.close();
    return true;
}
/**
 * @brief VerbsDatabase::mess Way to send message anywhere
 * @param message Message
 */
void VerbsDatabase::mess(QString message)
{
    qDebug()<<message;
    Q_EMIT sendMessage(message,messageText);
}
/**
 * @brief VerbsDatabase::createTables Creates all the tables
 * @return
 */
bool VerbsDatabase::createTables()
{
    if(!this->isOpen())return false;
    QSqlQuery q(db);

    mess("Creating tables...");
    q.prepare("create table if not exists verbforms_es (id varchar(32) primary key not null,verb_id varchar(32),form text,searchform text,regularity integer,plurality integer,gender integer,pronoun integer,tense integer);");
    q.exec();

    q.prepare("create table if not exists verbs_es(id varchar(32) primary key not null, verb text);");
    q.exec();

    q.prepare("create table if not exists examples_es (id varchar(32) primary key not null, verbform_id varchar(32), example text, example_ru text, example_en text);");
    q.exec();

    q.prepare("create table if not exists verbs_en (id varchar(32) primary key not null, verb text);");
    q.exec();

    q.prepare("create table if not exists verbs_ru (id varchar(32) primary key not null, verb text);");
    q.exec();
    //connections between verbs of different languages.
    q.prepare("create table if not exists verb_es_connections (id varchar(32) primary key not null,verb_es_id varchar(32), verb_conn_id varchar(32),unique (verb_es_is,verb_conn_id));");
    q.exec();

    //Нужен ли перевод каждой словоформе? Я думаю, что нет. Тем более, что на английском это почти всегда одно слово.
    //пожалуй вопрос скорее в том, как и когда. И зачем.

    //пример и связка с идентификаторами для этого примера..не слишком ли, а?
    //Я бы сказал, что ого-го!

    return true;
}

bool VerbsDatabase::createIndices()
{

    if(!this->isOpen())return false;
    QSqlQuery q(db);
    q.exec("create index verbforms_es_index_verb_id on verbforms_es(verb_id);");
    q.exec("create index verbforms_es_index_form on verbforms_es(form);");
    q.exec("create index verbforms_es_index_searchform on verbforms_es(searchform);");
    q.exec("create index verbforms_es_index_gender on verbforms_es(gender);");
    q.exec("create index verbforms_es_index_pronoun on verbforms_es(pronoun);");
    q.exec("create index verbforms_es_index_tense on verbforms_es(tense);");

    q.exec("create index verbs_es_index_verb on verbs_es(verb);");
    q.exec("create index verbs_en_index_verb on verbs_en(verb);");
    q.exec("create index verbs_ru_index_verb on verbs_ru(verb);");

    q.exec("create index examples_es_index_verbform_id on verbforms_es(verbform_id);");

    q.exec("create index verb_es_connections_index_verb_es_id on verbforms_es(verb_es_id);");
    q.exec("create index verb_es_connections_index_verb_conn_id on verbforms_es(verb_conn_id);");

    return true;

}

bool VerbsDatabase::clearTable(QString tableName)
{
    if(!this->isOpen())return false;
     QSqlQuery q(db);
     q.prepare("delete from "+tableName+";");
     return q.exec();
}

bool VerbsDatabase::transactionStart()
{
    if(!this->isOpen())return false;
    return db.transaction();
}

bool VerbsDatabase::transactionEnd()
{
    if(!this->isOpen())return false;
    return db.commit();
}
/**
 * @brief VerbsDatabase::addVerb Add new verb
 * @param verb Verb
 * @param lang Language for table selection
 * @return
 */
QString VerbsDatabase::addVerb(QString verb, languageEnum lang)
{
    if(!this->isOpen())return QString();
    QString verbId;
    QSqlQuery q(db);
    QString verbTable;
    switch(lang)
    {
    case languageEnglish:
        verbTable="verbs_en";
        break;
    case languageEspanol:
        verbTable="verbs_es";
        break;
    case languageRussian:
        verbTable="verbs_ru";
        break;
    default:
        verbTable="verbs_es";
        break;
    }

    //проверяем наличие, сначала.
    q.prepare("select id from "+verbTable+" where verb=:verb limit 1;");
    q.bindValue(":verb",verb);
    q.exec();
    if(q.first())
    {
        Q_EMIT sendMessage("Verb '"+verb+"' already exists",messageBox);
        return verbId;
    }

    verbId=QUuid::createUuid().toRfc4122().toHex();
    q.prepare("insert into "+verbTable+" (id,verb) values(:id,:verb);");
    q.bindValue(":id",verbId);
    q.bindValue(":verb",verb);
    if(!q.exec())
    {
        verbId.clear();
        Q_EMIT sendMessage("Last error"+db.lastError().databaseText()+",driver:"+db.lastError().driverText(),messageBox);
    }
    return verbId;
}
/**
 * @brief VerbsDatabase::deleteVerb Delete verb
 * @param verbId Verb identificator
 * @param lang Language for table selection
 * @return
 */
bool VerbsDatabase::deleteVerb(QString verbId,languageEnum lang)
{
    if(!this->isOpen())return false;
    QSqlQuery q(db);
    QString verbLangPrefix;
    switch(lang)
    {
    case languageEnglish:
        verbLangPrefix="en";
        break;
    case languageEspanol:
        verbLangPrefix="es";
        break;
    case languageRussian:
        verbLangPrefix="ru";
        break;
    default:
        verbLangPrefix="es";
        break;
    }
    q.prepare("delete from verbs_"+verbLangPrefix+" where id=:id;");
    q.bindValue(":id",verbId);
    bool res=q.exec();
    //Короче, надо делать триггеры и забыть об этом...слишком много всего надо тут упомянуть.
    //ТРИГГЕРЫ
    return res;
}
/**
 * @brief VerbsDatabase::changeVerb Change verb
 * @param verbId Verb identificator
 * @param newName New Verb text
 * @param lang Language for table selection
 * @return
 */
bool VerbsDatabase::changeVerb(QString verbId,QString newName,languageEnum lang)
{
    if(!this->isOpen())return false;
    QSqlQuery q(db);
    QString verbTable;
    switch(lang)
    {
    case languageEnglish:
        verbTable="verbs_en";
        break;
    case languageEspanol:
        verbTable="verbs_es";
        break;
    case languageRussian:
        verbTable="verbs_ru";
        break;
    default:
        verbTable="verbs_es";
        break;
    }
    q.prepare("update "+verbTable+" set verb=:verb where id=:id;");
    q.bindValue(":verb",newName);
    q.bindValue(":id",verbId);
    return q.exec();
}

bool VerbsDatabase::createTensesEs()
{
    if(!this->isOpen())return false;
    QSqlQuery q(db);
    q.prepare("create table if not exists tenses_es (id integer primary key not null, name text, name_en text,name_ru text);");
    if(!q.exec())
        qDebug()<<"[WARNING]"<<db.lastError().text();
    q.prepare("delete from tenses_es;");
    q.exec();

    this->addTenseEs(TENSE_NINGUNO,"Ninguno","None","Нет");
    this->addTenseEs(TENSE_PRESENTE,"Presente","Present","Настоящее");
    this->addTenseEs(TENSE_PRETERITO_PERFECTO_COMPUESTO,"Pretérito perfecto compuesto","Present Perfect","Настоящее совершенное");
    this->addTenseEs(TENSE_PRETERITO_IMPERFECTO,"Pretérito imperfecto","Imperfect","Несовершенное");
    this->addTenseEs(TENSE_PRETERITO_PERFECTO_SIMPLE,"Pretérito perfecto simple","Preterite","Preterite");
    this->addTenseEs(TENSE_PRETERITO_PLUSCAMPERFECTO,"Pretérito pluscuamperfecto","Pluperfect","Pluperfect");
    this->addTenseEs(TENSE_FUTURO,"Futuro","Future","Future");
    this->addTenseEs(TENSE_FUTURO_PERFECTO,"Futuro perfecto","Future Perfect","FuturePerfect");
    this->addTenseEs(TENSE_CONDICIONAL,"Condicional","Conditional","Условное");
    this->addTenseEs(TENSE_CONDICIONAL_PERFECTO,"Condicional perfecto","Conditional Perfect","Условное совершенное");
    this->addTenseEs(TENSE_PRETERITO_ANTERIOR,"Pretérito anterior","Past Perfect","Pretérito anterior");
    this->addTenseEs(TENSE_SUBJUNCTIVO_PRESENTE,"Subjuntivo presente","subjPresent","subjPresent");
    this->addTenseEs(TENSE_SUBJUNCTIVO_PRETERITO_PERFECTO,"Subjuntivo Pretérito perfecto","subjPresentPerfect","subjPresentPerfect");
    this->addTenseEs(TENSE_SUBJUNCTIVO_PRETERITO_IMPERFECTO,"Subjuntivo Pretérito imperfecto","subjImperfect","subjImperfect");
    this->addTenseEs(TENSE_SUBJUNCTIVO_PRETERITO_IMPERFECTO_2,"Subjuntivo Pretérito imperfecto 2","subjImperfect2","subjImperfect2");
    this->addTenseEs(TENSE_SUBJUNCTIVO_PRETERITO_PLUSCUAMPERFECTO,"Subjuntivo Pretérito pluscuamperfecto","subjPlurperfect","subjPlurperfect");
    this->addTenseEs(TENSE_SUBJUNCTIVO_PRETERITO_PLUSCUAMPERFECTO_2,"Subjuntivo Pretérito pluscuamperfecto 2","subjPlurperfect2","subjPlurperfect2");
    this->addTenseEs(TENSE_SUBJUNCTIVO_FUTURO,"Subjuntivo Futuro","subjFuture","subjFuture");
    this->addTenseEs(TENSE_SUBJUNCTIVO_FUTURO_PERFECTO,"Subjuntivo Futuro perfecto","subjFuturePerfect","subjFuturePerfect");
    this->addTenseEs(TENSE_IMPERATIVO,"Imperativo","impAffirmative","impAffirmative");
    this->addTenseEs(TENSE_IMPERATIVO_NEGATIVO,"Imperativo negativo","impNegative","impAffirmative");

    this->addTenseEs(VERBFORM_INFINITIVO_PRESENTE,"Infinitivo presente","Infinitivo presente","Infinitivo presente");
    this->addTenseEs(VERBFORM_INFINITIVO_COMPUESTO,"Infinitivo compuesto","Infinitivo presente","Infinitivo presente");
    this->addTenseEs(VERBFORM_GERUNDIO_PRESENTE,"Gerundio presente","Gerundio presente","Gerundio presente");
    this->addTenseEs(VERBFORM_GERUNDIO_COMPUESTO,"Gerundio compuesto","Gerundio compuesto","Gerundio compuesto");
    this->addTenseEs(VERBFORM_PARTICIPIO,"Participio","Participio","Participio");



    return true;

}

bool VerbsDatabase::addTenseEs(int id,QString name,QString nameEn,QString nameRu)
{
    if(!this->isOpen())return false;
    QSqlQuery q(db);
    q.prepare("insert into tenses_es (id, name,name_en, name_ru) values (:id,:name,:name_en,:name_ru);");
    q.bindValue(":id",id);
    q.bindValue(":name",name);
    q.bindValue(":name_en",nameEn);
    q.bindValue(":name_ru",nameRu);
    return q.exec();

}

QString VerbsDatabase::addVerbFormEs(QString verb_id, QString form, int tense, int pronoun)
{
    if(!this->isOpen())return "";
    qDebug()<<"Adding verb form...";
    QSqlQuery q(db);
    QString uuid=QUuid::createUuid().toRfc4122().toHex();

    q.prepare("insert into verbforms_es (id,verb_id,form,tense,pronoun) values (:id,:verb_id,:form,:tense,:pronoun);");
    q.bindValue(":id",uuid);
    q.bindValue(":verb_id",verb_id);
    q.bindValue(":form",form);
    q.bindValue(":tense",tense);
    q.bindValue(":pronoun",pronoun);
    if(q.exec()) return uuid;
    return "";
}

bool VerbsDatabase::updateVerbFormEs(QString id, QString form)
{
    if(!this->isOpen())return false;
    QSqlQuery q(db);
    qDebug()<<"Updating verb form...";
    q.prepare("update verbforms_es set form=:form where id=:id;");
    q.bindValue(":id",id);
    q.bindValue(":form",form);
    return q.exec();
}

QString VerbsDatabase::findVerbId(QString verb)
{
    if(!this->isOpen())return "";
    QSqlQuery q(db);
    q.prepare("select id from verbs_en where verb=:verb1 union select id from verbs_ru where verb=:verb2 union select id from verbs_es where verb=:verb3 limit 1;");

     q.bindValue(":verb1",verb);
     q.bindValue(":verb2",verb);
     q.bindValue(":verb3",verb);
     q.exec();
     if(q.first())
     {
         qDebug()<<"VERB FOUND";
         return q.record().value("id").toString();
     }

     return "";
    q.prepare("select id from verbs_ru where verb=:verb limit 1;");
    q.bindValue(":verb",verb);
    q.exec();
    if(q.first())
    {
        qDebug()<<"Found Russian verb "<<q.record().value("id").toString();
        return q.record().value("id").toString();
    }
    q.clear();
    q.prepare("select id from verbs_en where verb=:verb limit 1;");
    q.bindValue(":verb",verb);
    q.exec();

    if(q.first())
    {
        qDebug()<<"Found English verb "<<q.record().value("id").toString();
        return q.record().value("id").toString();
    }

    return "";
}


bool VerbsDatabase::verbEsConnectionExists(QString verbEsId, QString verbNoEsId)
{
    if(!this->isOpen())return false;
    QSqlQuery q(db);
    q.prepare("select id,verb_es_id,verb_conn_id from verb_es_connections where verb_es_id=:verb_es_id and verb_conn_id=:verb_conn_id limit 1;");
    q.bindValue(":verb_es_id",verbEsId);
    q.bindValue(":verb_conn_id",verbNoEsId);
    q.exec();
    if(q.first())
    {
       // qDebug()<<"He speaks that connection is found:"<<q.record().value("id").toString()<<","<<q.record().value("verb_es_id").toString()<<"."<<q.record().value("verb_conn_id").toString();
        return true;
    }
    return false;
}

bool VerbsDatabase::deleteVerbEsConnection(QString verbEsId, QString verbConnId)
{
    if(!this->isOpen())return false;
    QSqlQuery q(db);
    q.prepare("delete from verb_es_connections where verb_es_id=:verb_es_id and verb_conn_id=:vern_conn_id;");
    q.bindValue(":verb_es_id",verbEsId);
    q.bindValue(":verb_conn_id",verbConnId);
    return q.exec();
}

QString VerbsDatabase::addEsExample(QString verbFormId, QString example)
{
    if(!this->isOpen())return "";
    QSqlQuery q(db);
    QString  uuid;
    uuid=QUuid::createUuid().toRfc4122().toHex();
    q.prepare("insert into examples_es (id, verbform_id,example) values (:id,:verbform_id,:example);");
    q.bindValue(":id",uuid);
    q.bindValue(":verbform_id",verbFormId);
    q.bindValue(":example",example);
    if(q.exec())
        return uuid;
    return "";
}

bool VerbsDatabase::updateEsExampleTranslation(QString exampleId, QString translation, languageEnum lang)
{
    if(!this->isOpen())return false;
    QSqlQuery q(db);
    if(lang==languageEnglish)
    {
        q.prepare("update examples_es set example_en=:translation where id=:id;");
    }
    else if(lang==languageRussian)
    {
        q.prepare("update examples_es set example_ru=:translation where id=:id;");
    }
    q.bindValue("translation",translation);
    q.bindValue(":id",exampleId);
    return q.exec();
}

bool VerbsDatabase::updateEsExample(QString exampleId, QString exampleNew)
{
    if(!this->isOpen())return false;
    QSqlQuery q(db);
    q.prepare("update examples_es set example=:example where id=:id;");
    q.bindValue("example",exampleNew);
    q.bindValue(":id",exampleId);
    return q.exec();
}


/**
 * @brief VerbsDatabase::addVerbEsConnection Add connection for Spanish verb to another language verb
 * @param verbEsId Spanish verb identificator
 * @param verbConnId Another language verb idetificator
 * @return
 */
bool VerbsDatabase::addVerbEsConnection(QString verbEsId, QString verbConnId)
{
    if(!this->isOpen())return false;

    QSqlQuery q(db);
    q.prepare("insert into verb_es_connections (id, verb_es_id,verb_conn_id) values (:id,:verb_es_id,:verb_conn_id);");
    q.bindValue(":id",QUuid::createUuid().toRfc4122().toHex());
    q.bindValue(":verb_es_id",verbEsId);
    q.bindValue(":verb_conn_id",verbConnId);
    return q.exec();
}
/**
 * @brief VerbsDatabase::cleanDatabase Clean possible trash
 * @return
 */
bool VerbsDatabase::cleanDatabase()
{
    if(!this->isOpen())return false;
    QSqlQuery q(db);
    q.exec("delete from verbforms_es where verb_id not in (select id from verbs_es);");
//áéíñóúü
//áéíñóúüÁÉÍÑÓÚÜ
    /**
      Что прибавить:
      1. Английские и русские глаголы, которые ни с кем не связаны (артефакты добавления испанских).
      */
    return true;
}

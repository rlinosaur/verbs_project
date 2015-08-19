#include <QStringList>
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

    q.prepare("create table if not exists examples_es (id varchar(32) primary key not null, verbform_id varchar(32), example text, example_ru text, example_en text");    
    q.exec();

    q.prepare("create table if not exists verbs_en (id varchar(32) primary key not null, verb text);");
    q.exec();

    q.prepare("create table if not exists verbs_ru (id varchar(32) primary key not null, verb text);");
    q.exec();
    //connections between verbs of different languages.
    q.prepare("create table if not exists verb_es_connections (id varchar(32) primary key not null,verb_es_id varchar(32), verb_conn_id varchar(32));");
    q.exec();

    //Нужен ли перевод каждой словоформе? Я думаю, что нет. Тем более, что на английском это почти всегда одно слово.
    //пожалуй вопрос скорее в том, как и когда. И зачем.

    //пример и связка с идентификаторами для этого примера..не слишком ли, а?
    //Я бы сказал, что ого-го!

    return true;
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
    return true;
}

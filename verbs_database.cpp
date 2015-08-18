#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QUuid>
#include <QFile>

#include "verbs_database.h"


VerbsDatabase::VerbsDatabase(QObject *parent) :
    QObject(parent)
{

}
bool VerbsDatabase::deleteDatabase()
{
    if(this->isOpen())this->close();    
    return QFile::remove(fName);
}

void VerbsDatabase::init(QString fileName)
{

    QStringList drivers = QSqlDatabase::drivers();
    mess("Database initialization...");
    mess("Available drivers list:"+drivers.join(","));

    db = QSqlDatabase::addDatabase("QSQLITE", QUuid::createUuid());
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

bool VerbsDatabase::isOpen()
{
    return db.isOpen();
}

bool VerbsDatabase::close()
{
    db.close();
    return true;
}

void VerbsDatabase::mess(QString message)
{
    qDebug()<<message;
    Q_EMIT sendMessage(message);
}

bool VerbsDatabase::createTables()
{
    if(!this->isOpen())return false;
    QSqlQuery q;
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

    q.prepare("create table if not exists verb_es_connections (id varchar(32) primary key not null,verb_es_id varchar(32), verb_conn_id varchar(32));");
    q.exec();
    //Нужен ли перевод каждой словоформе? Я думаю, что нет. Тем более, что на английском это почти всегда одно слово.
    //пожалуй вопрос скорее в том, как и когда. И зачем.

    //пример и связка с идентификаторами для этого примера..не слишком ли, а?
    //Я бы сказал, что ого-го!

    return true;
}

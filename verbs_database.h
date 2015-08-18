#ifndef VERBS_DATABASE_H
#define VERBS_DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QObject>


class VerbsDatabase : public QObject
{
    Q_OBJECT
public:
    explicit VerbsDatabase(QObject *parent = 0);
    void init(QString fileName="verbsbase.db");
    bool isOpen();
    bool close();
private:
    QSqlDatabase db;
    QString fName;
    void mess(QString message);

    
signals:
    void sendMessage(QString message);
public slots:
    
};

#endif // VERBS_DATABASE_H

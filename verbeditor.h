#ifndef VERBEDITOR_H
#define VERBEDITOR_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDialog>

#include "verbs_database.h"

namespace Ui {
class VerbEditor;
}

class VerbEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit VerbEditor(QString verbId,VerbsDatabase *database,QWidget *parent = 0);
    ~VerbEditor();
    
private slots:
    void on_pushButtonVerbChange_clicked();

    void on_pushButtonVerbDelete_clicked();

private:
    Ui::VerbEditor *ui;
    QSqlTableModel *verbsmodel;
    QString verbIdent;
    QString verbVerb;
    VerbsDatabase *db;

};

#endif // VERBEDITOR_H

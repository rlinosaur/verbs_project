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
    explicit VerbEditor(QString verbId,VerbsDatabase *db,QWidget *parent = 0);
    ~VerbEditor();
    
private:
    Ui::VerbEditor *ui;
    QSqlTableModel *verbsmodel;
    QString verbIdent;
    QString verbVerb;

};

#endif // VERBEDITOR_H

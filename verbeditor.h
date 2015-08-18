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
    explicit VerbEditor(QWidget *parent = 0,VerbsDatabase *db= new VerbsDatabase());
    ~VerbEditor();
    
private:
    Ui::VerbEditor *ui;

     QSqlTableModel *verbsmodel;
};

#endif // VERBEDITOR_H

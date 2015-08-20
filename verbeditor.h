#ifndef VERBEDITOR_H
#define VERBEDITOR_H

#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QLineEdit>
#include <QDialog>

#include "lineeditforverbs.h"
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

    void on_pushButtonCaps_clicked();

    void letterClickedSlot();
    void lineEditInFocusSlot();

private:
    Ui::VerbEditor *ui;
    QSqlTableModel *verbsmodel;
    QString verbIdent;
    QString verbVerb;
    VerbsDatabase *db;

    bool capitalLettersFlag;
    LineEditForVerbs *lineEditInFocus;


    void loadSamples(QString verbformId);

};

#endif // VERBEDITOR_H

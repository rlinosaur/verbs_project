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

    void on_listViewTenses_activated(const QModelIndex &index);

    void on_pushButtonClearEdits_clicked();

    void on_pushButtonSaveTense_clicked();

    void on_pushButtonAutoFillTense_clicked();

    void on_pushButtonConnectionAdd_clicked();

    void on_listViewConnections_activated(const QModelIndex &index);

    void on_pushButtonAddSample_clicked();

    void on_listViewSamples_activated(const QModelIndex &index);

    void on_pushButtonEditSample_clicked();

private:
    Ui::VerbEditor *ui;
    QSqlTableModel *verbsmodel;
    QString verbIdent;
    QString verbVerb;
    VerbsDatabase *db;

    bool capitalLettersFlag;
    LineEditForVerbs *lineEditInFocus;

    QSqlQueryModel *tensesModel;
    QSqlQueryModel *examplesModel;
    QSqlQueryModel *connectionsModel;

    int currentTense;
    QList<LineEditForVerbs *> pronounEditList;

    QString currentVerbformId;


    void loadSamples(QString verbformId);
    void reloadConnectionsModel();
    void reloadExamplesModel(QString verbformId);
};

#endif // VERBEDITOR_H

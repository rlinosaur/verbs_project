#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>

#include "verbeditor.h"
#include "ui_verbeditor.h"

VerbEditor::VerbEditor(QString verbId, VerbsDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerbEditor)
{
    ui->setupUi(this);

    if(!db->isOpen())
    {
        QMessageBox::warning(this,"Warning","Database isn't opened.");
        return;
    }
    if(verbId.isEmpty())
    {
        QMessageBox::warning(this,"Warning","Verb isn't selected, please repeat.");
        return;
    }

    verbsmodel= new QSqlTableModel(this,db->getDb());
    verbsmodel->setTable("verbs_es");
    verbsmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    verbsmodel->select();//Это ещё зачем?

    ui->tableView->setModel(verbsmodel);
    ui->tableView->hideColumn(0);

    verbIdent=verbId;
    QSqlQuery q(db->getDb());
    q.prepare("select verb from verbs_es where id=:id;");
    q.bindValue(":id",verbId);
    q.exec();
    if(q.first())
    {
        verbVerb=q.record().value("verb").toString();
        ui->labelVerb->setText("Our verb:"+verbVerb);
    }
    else
    {
        QMessageBox::warning(this,"Warning","Unfortunately information about verb isn't found, please repeat.");
    }
    this->setWindowTitle("Edit verb '"+verbVerb+"'");

}

VerbEditor::~VerbEditor()
{
    delete ui;
}

#include <QMessageBox>

#include "verbeditor.h"
#include "ui_verbeditor.h"

VerbEditor::VerbEditor(QWidget *parent, VerbsDatabase *db) :
    QDialog(parent),
    ui(new Ui::VerbEditor)
{
    ui->setupUi(this);

    if(!db->isOpen())
    {
        QMessageBox::warning(this,"Warning","Database isn't opened");
        return;
    }
    verbsmodel= new QSqlTableModel(this,db->getDb());
    verbsmodel->setTable("verbs_es");
    verbsmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    verbsmodel->select();//Это ещё зачем?

    ui->tableView->setModel(verbsmodel);
    ui->tableView->hideColumn(0);

}

VerbEditor::~VerbEditor()
{
    delete ui;
}

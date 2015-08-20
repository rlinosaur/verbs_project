#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QListView>

#include "verbeditor.h"
#include "ui_verbeditor.h"

VerbEditor::VerbEditor(QString verbId, VerbsDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerbEditor)
{
    ui->setupUi(this);

    db=database;

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
/*
    verbsmodel= new QSqlTableModel(this,db->getDb());
    verbsmodel->setTable("verbs_es");
    verbsmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    verbsmodel->select();//Это ещё зачем?

    ui->tableView->setModel(verbsmodel);
    ui->tableView->hideColumn(0);
*/
    verbIdent=verbId;
    QSqlQuery q(db->getDb());
    q.prepare("select verb from verbs_es where id=:id;");
    q.bindValue(":id",verbId);
    q.exec();
    if(q.first())
    {
        verbVerb=q.record().value("verb").toString();
  //      ui->labelVerb->setText("Our verb:"+verbVerb);
        ui->lineEditVerb->setText(verbVerb);
    }
    else
    {
        QMessageBox::warning(this,"Warning","Unfortunately information about the verb isn't found, please repeat.");
    }
    this->setWindowTitle("Edit verb '"+verbVerb+"'");

    //Заполнить список.
    //enum for cicle..how to? Just I don't know.


    capitalLettersFlag=false;

    ui->lineEditVerb->setFocus();
    lineEditInFocus=ui->lineEditVerb;

    connect(ui->pushButtonA,SIGNAL(clicked()),this,SLOT(letterClickedSlot()));
    connect(ui->pushButtonE,SIGNAL(clicked()),this,SLOT(letterClickedSlot()));
    connect(ui->pushButtonI,SIGNAL(clicked()),this,SLOT(letterClickedSlot()));
    connect(ui->pushButtonN,SIGNAL(clicked()),this,SLOT(letterClickedSlot()));
    connect(ui->pushButtonO,SIGNAL(clicked()),this,SLOT(letterClickedSlot()));
    connect(ui->pushButtonU1,SIGNAL(clicked()),this,SLOT(letterClickedSlot()));
    connect(ui->pushButtonU2,SIGNAL(clicked()),this,SLOT(letterClickedSlot()));

    connect(ui->lineEditConnectionSearch,SIGNAL(inFocus()),this,SLOT(lineEditInFocusSlot()));
    connect(ui->lineEditEl,SIGNAL(inFocus()),this,SLOT(lineEditInFocusSlot()));
    connect(ui->lineEditEllos,SIGNAL(inFocus()),this,SLOT(lineEditInFocusSlot()));
    connect(ui->lineEditNosotros,SIGNAL(inFocus()),this,SLOT(lineEditInFocusSlot()));
    connect(ui->lineEditParticiplePast,SIGNAL(inFocus()),this,SLOT(lineEditInFocusSlot()));
    connect(ui->lineEditParticiplePresent,SIGNAL(inFocus()),this,SLOT(lineEditInFocusSlot()));
    connect(ui->lineEditSample,SIGNAL(inFocus()),this,SLOT(lineEditInFocusSlot()));
    connect(ui->lineEditTu,SIGNAL(inFocus()),this,SLOT(lineEditInFocusSlot()));
    connect(ui->lineEditVerb,SIGNAL(inFocus()),this,SLOT(lineEditInFocusSlot()));
    connect(ui->lineEditVosotros,SIGNAL(inFocus()),this,SLOT(lineEditInFocusSlot()));
    connect(ui->lineEditYo,SIGNAL(inFocus()),this,SLOT(lineEditInFocusSlot()));
}

VerbEditor::~VerbEditor()
{
    delete ui;
}

void VerbEditor::on_pushButtonVerbChange_clicked()
{
    if(QMessageBox::question(this,"Are you sure?","Verb "+verbVerb+" will change the name. Are you sure about it?",QMessageBox::Yes,QMessageBox::No)!=QMessageBox::Yes)
    {
        ui->lineEditVerb->setText(verbVerb);
        return;
    }
    if(db->changeVerb(verbIdent,ui->lineEditVerb->text(),languageEspanol))
        verbVerb=ui->lineEditVerb->text();

}

void VerbEditor::on_pushButtonVerbDelete_clicked()
{

    if(QMessageBox::question(this,"Are you sure?","Verb "+verbVerb+" will be deleted. Are you sure about it?",QMessageBox::Yes,QMessageBox::No)!=QMessageBox::Yes)return;
    //Yes, i'm sure
    db->deleteVerb(verbIdent,languageEspanol);
    this->close();
}

void VerbEditor::on_pushButtonCaps_clicked()
{
    //áéíñóúüÁÉÍÑÓÚÜ
    //флаг знака, да..
    if(capitalLettersFlag)
    {
        capitalLettersFlag=false;
        ui->pushButtonA->setText("á");
        ui->pushButtonE->setText("é");
        ui->pushButtonI->setText("í");
        ui->pushButtonN->setText("ñ");
        ui->pushButtonO->setText("ó");
        ui->pushButtonU1->setText("ú");
        ui->pushButtonU2->setText("ü");
    }
    else
    {
        capitalLettersFlag=true;
        ui->pushButtonA->setText("Á");
        ui->pushButtonE->setText("É");
        ui->pushButtonI->setText("Í");
        ui->pushButtonN->setText("Ñ");
        ui->pushButtonO->setText("Ó");
        ui->pushButtonU1->setText("Ú");
        ui->pushButtonU2->setText("Ü");
    }
}
void VerbEditor::letterClickedSlot()
{
    QPushButton *senderButton = qobject_cast<QPushButton*>( sender() );
    if(senderButton)
        lineEditInFocus->insert(senderButton->text());
}

void VerbEditor::lineEditInFocusSlot()
{
    QLineEditWithFocus *senderEdit=qobject_cast<QLineEditWithFocus*>(sender());
    if(senderEdit)
        lineEditInFocus=senderEdit;
}

#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>
#include <QListView>
#include <QDebug>

#include "ui_verbeditor.h"
#include "verbeditor.h"
#include "verbform.h"


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
    q.prepare("select verb from verbs_es where id=:id limit 1;");
    q.bindValue(":id",verbId);
    q.exec();
    if(q.first())
    {
        verbVerb=q.record().value("verb").toString();  
        ui->lineEditVerb->setText(verbVerb);
    }
    else
    {
        QMessageBox::warning(this,"Warning","Unfortunately information about the verb isn't found, please repeat.");
    }
    this->setWindowTitle("Edit verb '"+verbVerb+"'");


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


    //Initialization of tenses
    tensesModel = new QSqlQueryModel(this);
    tensesModel->setQuery("select id,name,name_en,name_ru from tenses_es where id<100 and id>0;",db->getDb());
    ui->listViewTenses->setModel(tensesModel);
    ui->listViewTenses->setModelColumn(1);
    currentTense=TENSE_NINGUNO;

    ui->lineEditYo->pronoun=PRONOUN_YO;
    ui->lineEditTu->pronoun=PRONOUN_TU;
    ui->lineEditEl->pronoun=PRONOUN_EL;
    ui->lineEditNosotros->pronoun=PRONOUN_NOSOTROS;
    ui->lineEditVosotros->pronoun=PRONOUN_VOSOTROS;
    ui->lineEditEllos->pronoun=PRONOUN_ELLOS;
    pronounEditList.append(ui->lineEditYo);
    pronounEditList.append(ui->lineEditTu);
    pronounEditList.append(ui->lineEditEl);
    pronounEditList.append(ui->lineEditNosotros);
    pronounEditList.append(ui->lineEditVosotros);
    pronounEditList.append(ui->lineEditEllos);

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
    {
        lineEditInFocus->insert(senderButton->text());
        lineEditInFocus->setFocus();
    }
}
/*
 *так..что делать-то...
 *А делать надо следующее...
 *
 **/
void VerbEditor::lineEditInFocusSlot()
{
    LineEditForVerbs *senderEdit=qobject_cast<LineEditForVerbs*>(sender());
    if(senderEdit)
    {
        lineEditInFocus=senderEdit;
        loadSamples(lineEditInFocus->dataId);
    }
}
/**
 * @brief VerbEditor::loadSamples Load samples to editor by verbform id
 * @param verbformId id of verb form to load
 */
void VerbEditor::loadSamples(QString verbformId)
{
    if(verbformId.isEmpty())return;
    ui->lineEditSample->setText("Our id is "+verbformId);
}

void VerbEditor::on_listViewTenses_activated(const QModelIndex &index)
{
    //Отобразить всё, что нам нужно...пожалуйста.
    /**
      1. Узнать идентификатор времени из модели
      2. Сделать запрос к БД, получить все формы, которые хранятся для этого глагола и для этого времени
      (храним сразу в структуру, чего беспокоиться-то)...
      Может даже структуру эту зашьём в редактор...вар..не будем торопиться.
      3. Раскидать формы по редакторам...как-то так.
      4. Мысль о хранении объекта в эдиторе (там, где он нужен) вызывает интерес.
      */
    on_pushButtonClearEdits_clicked();
    ui->lineEditYo->dataId.clear();
    ui->lineEditTu->dataId.clear();
    ui->lineEditEl->dataId.clear();
    ui->lineEditNosotros->dataId.clear();
    ui->lineEditVosotros->dataId.clear();
    ui->lineEditEllos->dataId.clear();
    //tensesModel->data(tensesModel->index(index.row(),0)).toStrin;//идентификатор записи о времени в таблице.
    currentTense=tensesModel->data(tensesModel->index(index.row(),0)).toInt();
    QSqlQuery q(db->getDb());
    q.prepare("select id,form,pronoun from verbforms_es where verb_id=:verb_id and tense=:tense;");
    q.bindValue(":verb_id",verbIdent);
    q.bindValue(":tense",currentTense);
    if(!q.exec())
    {
        qDebug()<<"DEBUGGIO LAST ERROR "<<db->getDb().lastError();
        return;
    }
    qDebug()<<"Query executed";

    if(!q.first())return;
    qDebug()<<"There are records in the database";




    qDebug()<<"Clearing edits";

    QSqlRecord r;

    //далее опрос, пока не надоест..ибо так сказано.
    do
    {
       // col1 << r.value("id").toString();
       // col2 << r.value("name").toString().toUpper();
        LineEditForVerbs *loadedLineEdit=NULL;
        r=q.record();
        switch(r.value("pronoun").toInt())
        {
        case PRONOUN_YO:
            loadedLineEdit=ui->lineEditYo;
            break;
        case PRONOUN_TU:
            loadedLineEdit=ui->lineEditTu;
            break;
        case PRONOUN_EL:
            loadedLineEdit=ui->lineEditEl;
            break;
        case PRONOUN_NOSOTROS:
            loadedLineEdit=ui->lineEditNosotros;
            break;
        case PRONOUN_VOSOTROS:
            loadedLineEdit=ui->lineEditVosotros;
            break;
        case PRONOUN_ELLOS:
            loadedLineEdit=ui->lineEditEllos;
            break;

        }
        if(loadedLineEdit!=NULL)
        {
            loadedLineEdit->setText(r.value("form").toString());
            loadedLineEdit->dataId=r.value("id").toString();
        }

    }while(q.next());

}

void VerbEditor::on_pushButtonClearEdits_clicked()
{
    ui->lineEditYo->clear();;
    ui->lineEditTu->clear();
    ui->lineEditEl->clear();
    ui->lineEditNosotros->clear();
    ui->lineEditVosotros->clear();
    ui->lineEditEllos->clear();
}

void VerbEditor::on_pushButtonSaveTense_clicked()
{
    qDebug()<<"Currenmt tense:"<<currentTense;
    if(currentTense==TENSE_NINGUNO) return;

    //далее всё по порядку...му-ха-ха...
    for(int i=0;i<pronounEditList.size();i++)
    {
        if(pronounEditList[i]->dataId.isEmpty())
        {
            if(!pronounEditList[i]->text().isEmpty())
                db->addVerbFormEs(verbIdent,pronounEditList[i]->text(),currentTense,pronounEditList[i]->pronoun);
        }
        else
           db->updateVerbFormEs(pronounEditList[i]->dataId,pronounEditList[i]->text());

    }

}

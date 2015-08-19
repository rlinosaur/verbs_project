#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>


#include <QDebug>

#include "verbeditor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)  
{
    connect(&db,SIGNAL(sendMessage(QString,MessageType)),this,SLOT(messView(QString,MessageType)));
    ui->setupUi(this);
    QString fName("verbsbase.db");
    //QFile::remove(fName);
    db.init(fName);
    db.createTables();

    //QSqlQueryModelPrivate
    verbsmodel = new QSqlQueryModel(this);
    verbsmodel->setQuery("select * from verbs_es;",db.getDb());
    /*
    QSqlQuery q(db.getDb());
    q.prepare("select * from verbs_es;");
     q.exec();
    verbsmodel->setQuery(q);
*/

    //verbsmodel= new QSqlTableModel(this,db.getDb());
    //verbsmodel->setTable("verbs_es");

    //verbsmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //verbsmodel->select();//Это ещё зачем?

    ui->tableViewVerbs->setModel(verbsmodel);
    ui->tableViewVerbs->hideColumn(0);

    //ui->tableViewVerbs->setSelectionModel(QItemSelectionModel::Rows);

    /*
    QSqlTableModel *model = new QSqlTableModel(parentObject, database);
         model->setTable("employee");
         model->setEditStrategy(QSqlTableModel::OnManualSubmit);
         model->select();
         model->setHeaderData(0, Qt::Horizontal, tr("Name"));
         model->setHeaderData(1, Qt::Horizontal, tr("Salary"));

         QTableView *view = new QTableView;
         view->setModel(model);
         view->hideColumn(0); // don't show the ID
         view->show();
         */

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //open database
    //maintain tables structure
    //create tables
    //watch the result.


    //собственно
}


void MainWindow::messView(QString message, MessageType messType,  MessageEmotion emotion)
{
    switch (messType)
    {
    case messageBox:
        switch(emotion)
        {
        case messageInformation:
            QMessageBox::information(this,"Information",message);
        break;
        case messageWarning:
            QMessageBox::warning(this,"Warning",message);
        break;
        case messageCritical:
            QMessageBox::critical(this,"Critical",message);
        break;
        }
        break;
    default:
        ui->textBrowser->append(message);
        break;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->lineEditVerbEs->text().isEmpty())
    {
        messView("Verb field is empty. Please write something.",messageBox,messageWarning);
        return;
    }
    QString verbEsId=db.addVerb(ui->lineEditVerbEs->text(),languageEspanol);
    if(verbEsId.isEmpty())return;
    if(!ui->lineEditVerbEn->text().isEmpty())
    {
        QString verbEnId=db.addVerb(ui->lineEditVerbEn->text(),languageEnglish);
        if(!verbEnId.isEmpty())
            db.addVerbEsConnection(verbEsId,verbEnId);
    }
    if(!ui->lineEditVerbRu->text().isEmpty())
    {
        QString verbRuId=db.addVerb(ui->lineEditVerbRu->text(),languageRussian);
        if(!verbRuId.isEmpty())
            db.addVerbEsConnection(verbEsId,verbRuId);
    }
    //verbsmodel->select();//по-моему так.
     verbsmodel->setQuery("select * from verbs_es;",db.getDb());
    return;


}

void MainWindow::on_pushButtonVerbSearch_clicked()
{

    reloadVerbsTable();
    //verbsmodel->setQuery("select * from verbs_es where verb like '%"+ui->lineEditVerbSearch->text()+"%';",db.getDb());
}

void MainWindow::on_tableViewVerbs_doubleClicked(const QModelIndex &index)
{
    //1. выбрать по индексу, какой глагол там был...
    //2. считать содержимое нулевого столбца (скрытого).
    //3. Открыть диалог.
    VerbEditor ve(verbsmodel->data(verbsmodel->index(index.row(),0)).toString(),&db,this);
    ve.exec();
    reloadVerbsTable();
    return;
}

void MainWindow::reloadVerbsTable()
{
    QSqlQuery q(db.getDb());
    q.prepare("select * from verbs_es where verb like :verb;");
    q.bindValue(":verb","%"+ui->lineEditVerbSearch->text()+"%");
    q.exec();
    verbsmodel->setQuery(q);
}

void MainWindow::on_tableViewVerbs_pressed(const QModelIndex &index)
{
    if(QApplication::mouseButtons()!=Qt::RightButton)return;
/*
    QMessageBox question;
    question.setWindowTitle("Are you sure?");
    question.setText();
    */
    if(QMessageBox::question(this,"Are you sure??","Are you sure that you want to delete verb "+verbsmodel->data(verbsmodel->index(index.row(),1)).toString()+"?",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)
    {
       bool res=db.deleteVerb(verbsmodel->data(verbsmodel->index(index.row(),0)).toString(),languageEspanol);
       if(!res)
           messView("What the..."+db.getDb().lastError().text());
    }
    reloadVerbsTable();
}

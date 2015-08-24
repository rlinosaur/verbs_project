#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QMimeData>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QFile>

#include "settingsdialog.h"
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
    db.createIndices();
    db.createTensesEs();

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

    clipBoard = QApplication::clipboard();
    connect(clipBoard,SIGNAL(changed(QClipboard::Mode)),this, SLOT(clipBoardEventSlot(QClipboard::Mode)));


}

void MainWindow::clipBoardEventSlot(QClipboard::Mode)
{
    //if(QApplication::clipboard()->mimeData()->mimeData()->hasText())

    if(QApplication::clipboard()->mimeData()->hasText() && clipBoard->text().size()<1024)
           messView("Clipboards text detected:"+clipBoard->text());



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

void MainWindow::on_toolButton_clicked()
{
    SettingsDialog settings;
    settings.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    /*
     * +1. Почистить таблицы.
     * 2. получить список времён.
     * 3.сделать цикл на н записей (можно даже цифры, кстати, чего заморачиваться).
     *4. заполнить вербформы
     *5. заполнить примеры на двух языках
     *6. заполнить соединения с иностранными глаголами на двух языках.
     **/
    db.clearTable("verb_es");
    db.clearTable("verb_en");
    db.clearTable("verb_ru");
    db.clearTable("examples_es");
    db.clearTable("verb_es_connections");
    db.clearTable("verbforms_es");


    //времена, родной.
    int verbNum=1000;

    QString verbId,verbEnId,verbRuId,verbformId;
    for(int i=0;i<verbNum;i++)
    {
        db.transactionStart();
        verbId=db.addVerb(QString::number(i),languageEspanol);
        verbEnId=db.addVerb(QString::number(i),languageEnglish);
        verbRuId=db.addVerb(QString::number(i),languageRussian);
        db.addVerbEsConnection(verbId,verbEnId);
        db.addVerbEsConnection(verbId,verbRuId);

        for(int j=1;j<=20;j++)
        {
            for(int k=1;k<=6;k++)
            {
                verbformId=db.addVerbFormEs(verbId,QString::number(i)+"_"+QString::number(j)+"_"+QString::number(k),j,k);
                db.addEsExample(verbformId,verbformId);
                db.updateEsExampleTranslation(verbformId,verbformId,languageEnglish);
                db.updateEsExampleTranslation(verbformId,verbformId,languageRussian);


            }
        }
        db.transactionEnd();
        qDebug()<<"Verb "<<i;

    }


}

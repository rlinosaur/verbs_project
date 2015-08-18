#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>


#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect(&db,SIGNAL(sendMessage(QString)),this,SLOT(messView(QString)));
    ui->setupUi(this);
    QString fName("verbsbase.db");
    QFile::remove(fName);
    db.init(fName);
    db.createTables();

    verbsmodel= new QSqlTableModel(this,db.getDb());
    verbsmodel->setTable("verbs_es");
    verbsmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    verbsmodel->select();//Это ещё зачем?

    ui->tableViewVerbs->setModel(verbsmodel);
    ui->tableViewVerbs->hideColumn(0);

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


void MainWindow::messView(QString message)
{
    ui->textBrowser->append(message);
}

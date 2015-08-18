#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>


#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect(&db,SIGNAL(sendMessage(QString)),this,SLOT(messView(QString));
    ui->setupUi(this);
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

    QString fName("verbsbase.db");
    QFile::remove(fName);
    db.init(fName);
    //собственно
}


void MainWindow::messView(QString message)
{
    ui->textBrowser->append(message);
}

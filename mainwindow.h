#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSqlQueryModel>
#include <QMetaObject>
#include <QClipboard>
#include <QMainWindow>

#include "verbs_database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    

private slots:
    void on_pushButton_clicked();
    void messView(QString message,MessageType messType=messageText, MessageEmotion emotion=messageInformation);
    void on_pushButton_2_clicked();
    void on_pushButtonVerbSearch_clicked();

    void on_tableViewVerbs_doubleClicked(const QModelIndex &index);

    void on_tableViewVerbs_pressed(const QModelIndex &index);

    void clipBoardEventSlot(QClipboard::Mode);

    void on_toolButton_clicked();

private:
    Ui::MainWindow *ui;
    VerbsDatabase db;
    QSqlQueryModel *verbsmodel;
    QClipboard *clipBoard;
    QMetaObject::Connection clipBoardConnection;

    void reloadVerbsTable();

};

#endif // MAINWINDOW_H

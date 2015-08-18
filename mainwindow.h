#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSqlTableModel>
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
    void messView(QString message);
private:   
    Ui::MainWindow *ui;
    VerbsDatabase db;
    QSqlTableModel *verbsmodel;
};

#endif // MAINWINDOW_H

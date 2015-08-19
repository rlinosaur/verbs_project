#include <QMessageBox>

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_pushButtonCancel_clicked()
{
    this->close();
}

void SettingsDialog::on_pushButtonSace_clicked()
{
    QMessageBox::information(this,"Not yet","Sorry, we aren't ready");
}

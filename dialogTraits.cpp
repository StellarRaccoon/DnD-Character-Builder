#include "dialog.h"
#include "ui_dialog.h"
#include<QJsonObject>
Dialog::Dialog(QWidget *parent, QJsonObject *dataObj)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->dialogTitle->setText(dataObj->value("name").toString());
    ui->dialogTitle->setReadOnly(true);
}

Dialog::~Dialog()
{
    delete ui;
}

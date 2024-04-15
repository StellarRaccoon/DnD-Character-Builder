#include "ClassesDialog.h"
#include "ui_ClassesDialog.h"
#include <QBoxLayout>
#include <QGroupBox>
#include <QJsonDocument>
#include <QPlainTextEdit>

ClassesDialog::ClassesDialog(QString className,QString spellcast, int hitDie, QString savingThrows, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ClassesDialog)
{

    qDebug() << "In Dialog";
    ui->setupUi(this);
    ui->pageTitle->setText(className);


    //create a vertical layout box to add traits to the ui
    ui->hitDieField->setText(QString::number(hitDie));
    ui->hitDieField->setReadOnly(true);

    ui->savingThrowsField->setText(savingThrows);
    ui->savingThrowsField->setReadOnly(true);

    ui->spellCastingField->setText(spellcast);
    ui->spellCastingField->setReadOnly(true);
}

ClassesDialog::~ClassesDialog()
{
    delete ui;
}

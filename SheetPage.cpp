#include "SheetPage.h"

#include "ui_SheetPage.h"

#include<QTextDocument>
#include<QVBoxLayout>
#include<QGridLayout>
#include<QtCore>
#include<QtGui>
SheetPage::SheetPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SheetPage)
{
    ui->setupUi(this);

    //set class
    ui->classBox->setText(userChar->getUserRace());
    //set race
    //set saving throws
    //set profs
    ui->playerNameBox->setText(userChar->getPlayerName());
    ui->charNameBox->setText(userChar->getCharacterName());
    ui->backgroundNameBox->setText(userChar->getCharacterBackground());
    ui->alignmentBox->setText(userChar->getCharacterAlignment());



}


SheetPage::~SheetPage()
{
    delete ui;
}

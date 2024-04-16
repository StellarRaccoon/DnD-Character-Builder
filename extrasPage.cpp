#include "extrasPage.h"
#include "ui_extrasPage.h"

extrasPage::extrasPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::extrasPage)
{
    ui->setupUi(this);
}

extrasPage::~extrasPage()
{
    delete ui;
}
QString extrasPage::getCharacterBackground(){
    return ui->backgroundBox->currentText();
}
QString extrasPage::getPlayerName(){
    return ui->playerNameBox->text();
}
QString extrasPage::getCharacterAlignment(){
    return ui->alignmentBox->currentText();
}
QString extrasPage::getCharacterName(){
    return ui->characterNameBox->text();
}

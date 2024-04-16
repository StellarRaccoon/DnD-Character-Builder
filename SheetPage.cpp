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
    ui->classBox=MainWindow::userCharacter
    //set race
    //set saving throws
    //set profs


}


SheetPage::~SheetPage()
{
    delete ui;
}

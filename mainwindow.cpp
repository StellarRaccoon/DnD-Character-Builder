#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "secdialog.h"
#include<QLabel>
#include<QNetworkReply>
#include<QDebug>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QTreeWidget>
#include<QTreeWidgetItem>
#include "TreePage.h"
#include"UserCharacter.h"
#include<QMessageBox>

/**
 * Main Window Consturctor
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    userCharacter = new UserCharacter();
    stackedWidget = ui->stackedWidget;
    /*insert a page into the stacked widget*/
    // QHBoxLayout *layout = new QHBoxLayout;
    // TreePage *newForm=new TreePage("Race");
    // layout->addWidget(newForm);
    // ui->stackedWidget->insertWidget(0,newForm);
    // newForm->populateTree("/api/races");

    //TreePage *classPage=new TreePage("Classes");
    //layout->addWidget(classPage);
    //ui->stackedWidget->insertWidget(0,classPage);
    ui->page_5->populateTree("/api/races");
    ui->page_6->populateTree("/api/classes");

    this->classPage= ui->page_6;
    this->racePage= ui->page_5;
    currentIndex = ui->stackedWidget->currentIndex();
    /*set Up Button Clicks*/
    connect(ui->nextPageButton, SIGNAL(QPushButton::clicked()), this,SLOT(on_nextPageButton_clicked()));
    connect(ui->backPageButton, SIGNAL(QPushButton::clicked()), this,SLOT(on_backPageButton_clicked()));
}

/**
 * Main Window Destructor
*/
MainWindow::~MainWindow()
{
    delete ui;
}

/*This should eventually cause the character sheet to update*/
void MainWindow::on_nextPageButton_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
    if (currentIndex == 0){
        userCharacter->setUserRace(this->racePage->getCurrentItem());
    }
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);

    currentIndex = ui->stackedWidget->currentIndex();
    //qDebug()<<userCharacter->toString();
    QMessageBox msgBox;
    msgBox.setText(userCharacter->toString());
    msgBox.exec();
}
void MainWindow::on_backPageButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
    currentIndex = ui->stackedWidget->currentIndex();
}

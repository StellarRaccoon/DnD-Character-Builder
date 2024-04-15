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
#include"SheetPage.h"
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
    ui->racePage->populateTree("/api/races");
    ui->classPage->populateTree("/api/classes");

    this->classPage= ui->classPage;
    this->racePage= ui->racePage;
    this->scorePage= ui->scorePage;
    this->docPage = ui->docPage;
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
    else if(currentIndex==1){
        userCharacter->setUserClass(this->classPage->getCurrentItem());
        scorePage->updatedScores = userCharacter->getAbilityScores();
    }
    else if(currentIndex==2){
        QMapIterator<QString, int> i(scorePage->updatedScores);
        while (i.hasNext()) {
            i.next();

            userCharacter->increaseAbilityScore(i.key(), i.value());
            //cout << qPrintable(i.key()) << ": " << i.value() << endl;
        }
    }
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);

    currentIndex = ui->stackedWidget->currentIndex();

}
void MainWindow::on_backPageButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
    currentIndex = ui->stackedWidget->currentIndex();
}

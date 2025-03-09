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
#include"extrasPage.h"
/**
 * Main Window Consturctor
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    userCharacter = new UserCharacter();
    /**
     * Change the stacked widget to a TabWidget
     */
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
   // this->docPage = ui->docPage;
    this->extraInfoPage = ui->extraInfoPage;
    currentIndex = ui->stackedWidget->currentIndex();
   // docPage->userChar = this->userCharacter;
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
        //qDebug()<<"userClass: "<<this->classPage->getCurrentItem();
        //scorePage->updatedScores = userCharacter->getAbilityScores();
        //⚠️send the base scores to the score page

    }
    else if(currentIndex==2){
        //⚠️update the character scores
        // userCharacter->setAbilityScore("str",scorePage->updatedScores.getValueFromIndex("str"));
        // userCharacter->setAbilityScore("int",scorePage->updatedScores.getValueFromIndex("int"));
        // userCharacter->setAbilityScore("con",scorePage->updatedScores.getValueFromIndex("con"));
        // userCharacter->setAbilityScore("cha",scorePage->updatedScores.getValueFromIndex("cha"));
        // userCharacter->setAbilityScore("dex",scorePage->updatedScores.getValueFromIndex("dex"));
        // userCharacter->setAbilityScore("wis",scorePage->updatedScores.getValueFromIndex("wis"));

    }
    else if(currentIndex==3){
        //get data from extras page
        userCharacter->setCharacterName(this->extraInfoPage->getCharacterName());
        userCharacter->setCharacterBackground(extraInfoPage->getCharacterBackground());
        userCharacter->setCharacterAlignment(extraInfoPage->getCharacterAlignment());
        userCharacter->setPlayerName(this->extraInfoPage->getPlayerName());
        userCharacter->setCharacterAlignment(this->extraInfoPage->getCharacterAlignment());
        userCharacter->setUserAbilityMod();
        userCharacter->setSkillMod();

    }

    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);

    currentIndex = ui->stackedWidget->currentIndex();

}
void MainWindow::on_backPageButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
    currentIndex = ui->stackedWidget->currentIndex();
}

void MainWindow::on_pushButton_clicked()
{
    SheetPage *wdg = new SheetPage(this->userCharacter);

    wdg->show();
    hide();//this will disappear main window
}


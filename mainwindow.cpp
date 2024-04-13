#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "secdialog.h"
#include<QLabel>
#include "dialogTraits.h"
#include<QNetworkReply>
#include<QDebug>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QTreeWidget>
#include<QTreeWidgetItem>
#include"jsonmanipulation.h"
#include "TreePage.h"

/**
 * Main Window Consturctor
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*insert a page into the stacked widget*/
    QHBoxLayout *layout = new QHBoxLayout;
    TreePage *newForm=new TreePage("Race");
    layout->addWidget(newForm);
    ui->stackedWidget->insertWidget(0,newForm);
    newForm->populateTree("/api/races");
    //ui->stackedWidget->setLayout(layout);
    //ui->centralwidget->addWidget->TreePage("race");
    //std::vector<std::string> raceNames {"Elf", "Human", "Dwarf", "Halfling", "Gnome"};

    /*------------------------------------*/
    /*Display race names in tree
    * Call to API for all races returns {"count":num-of-races, "results":[{"index":race-index,"name":race-name, "url":race-url}]}
    * Want to display race-name in tree and keep race-url for further use
    */

    /*create the race tree
    * column 0 is the name of the race
    * column 1 is hidden and contains the race url
    */
    /*
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->setColumnHidden(1,true);
    ui->treeWidget->setHeaderLabels(QStringList()<<"Races");


    //Empty array to hold all the race names
    QJsonArray jsonArrayRaceNames = {};
    //empty JSON document to hold the result of the api call to get the race names
    QJsonDocument doc;

    //should probably do something if these fail (like try again)
    //place api race call in doc
    jason.fetchData("/api/races", doc);
    //put "results" into an array, jsonArrayRaceNames is now an array of JSon objects
    jason.getNamesFromJson(doc,jsonArrayRaceNames);

    //Create an tree root for every race name object in the array
    for(auto raceNames: jsonArrayRaceNames){
        //turn the current array item into an object
        QJsonObject raceNameData = raceNames.toObject();
        //select the race-name and race-url from the current object
        QString raceName = raceNameData.value("name").toString();
        QString raceUrl = raceNameData.value("url").toString();
        //add a new root to the tree
        QTreeWidgetItem *raceRoot= new QTreeWidgetItem(ui->treeWidget);
        //set the text of the item
        raceRoot->setText(0,raceName);
        raceRoot->setText(1,raceUrl);

        qDebug()<<"url:"<<raceRoot->text(0);
    }
*/
    /*------------------------------------*/
}

/**
 * Main Window Destructor
*/
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Add Root to a tree
 * @param name - text displayed in column 0 of child
 * @param description - text displayed in column 1 of child
*/
/*
void MainWindow::AddRoot(QString name, QString description){
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0, name); //name in column0
    itm->setText(1,description);
    ui->treeWidget->addTopLevelItem(itm);

}
*/
/**
 * Add a child to a tree root
 * @param *parent - root thee child is under
 * @param name - text displayed in column 0 of child
 * @param description - text displayed in column 1 of child
*/
/*void MainWindow::addChild(QTreeWidgetItem *parent, QString name, QString description){
    //create a the child item
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);

    //set the text of the child
    itm->setText(0, name); //name in column0
    itm->setText(1,description);

    //add child to the parent
    parent->addChild(itm);

}*/
/**
 * When a Race is clicked, display a dialof box with the race name, all the traits of a race with a description of the trait
 * @brief MainWindow::on_listWidget_itemClicked
 * @param item the race tree item selected, contains the race name in col 0, race url in col 1
 */
/*
void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    //get the race name from the tree item
    QString raceName = item->text(0);

    //document to store the API call data in
    QJsonDocument dataDoc;

    //document to store the API call to race traits
    //should contain the keys "count" and "results" which is an array of [index, trait names, traitUrl]
    QJsonDocument traitsDoc;

    //get the url of the item for the call from the document
    //jason.fetchData(item->text(1),dataDoc);

    //empty array to store the names and urls of a traits which belong to a race
    QJsonArray traitsArray = {};

    //get the names and urls of the traits belonging to a race
    //call to race\traits which returns all the traits of a race{"count": numberofTraits, "results":[{"index":traits-index, "name":trait-name, "url":trait-url}]}
    jason.fetchData(item->text(1).append("/traits"),traitsDoc);
    jason.getNamesFromJson(traitsDoc, traitsArray);

    qDebug()<<"racial-trait url:"<<item->text(1).append("/traits");

    //create a new racial trait dialog box
    Dialog infoDialog(this,raceName, traitsArray);

    //block the main page from being acceses
    infoDialog.setModal(true);

    //launch dialog box
    infoDialog.exec();
}*/


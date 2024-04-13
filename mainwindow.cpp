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

/**
 * Main Window Consturctor
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::vector<std::string> raceNames {"Elf", "Human", "Dwarf", "Halfling", "Gnome"};

    QJsonArray jsonArrayRaceNames = {};
    QJsonDocument doc(jsonArrayRaceNames);

    //should probably do something if these fail (like try again)
    qDebug()<<jason.fetchData("/api/races", doc);
    jason.getNamesFromJson(doc,jsonArrayRaceNames);

    //get the names and urls from each to get more data
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->setColumnHidden(1,true);
    ui->treeWidget->setHeaderLabels(QStringList()<<"Hey"<<"Cowboy");

    AddRoot("Hello", "World");

    for(auto raceNames: jsonArrayRaceNames){
        QJsonObject raceNameData = raceNames.toObject();
        QString raceName = raceNameData.value("name").toString();
        QString raceUrl = raceNameData.value("url").toString();
        QTreeWidgetItem *raceRoot= new QTreeWidgetItem(ui->treeWidget);
        raceRoot->setText(0,raceName);
        raceRoot->setText(1,raceUrl);
        qDebug()<<"url:"<<raceRoot->text(0);
    }
}

/**
 * Main Window destructor
*/
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Add Root to tree in the widget page
*/
void MainWindow::AddRoot(QString name, QString description){
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0, name); //name in column0
    itm->setText(1,description);
    ui->treeWidget->addTopLevelItem(itm);

}

/**
 * Add a child to a tree root
*/
void MainWindow::addChild(QTreeWidgetItem *parent, QString name, QString description){
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0, name); //name in column0
    itm->setText(1,description);
    parent->addChild(itm);

}
/**
 * Display a Dialog box which provides additional details about the Item clicked
 * @brief MainWindow::on_listWidget_itemClicked
 * @param item
 */

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QJsonDocument dataDoc;
    //get the url of the item for the call

    jason.fetchData(item->text(1),dataDoc);

    //convert doc to a JsonObject
    QString raceName = item->text(0);
    //QJsonObject dataObj = dataDoc.object();
    //create a new dialog box object
    QJsonDocument traitsDoc;
    QJsonArray traitsArray = {};
    jason.fetchData(item->text(1).append("/traits"),traitsDoc);
    jason.getNamesFromJson(traitsDoc, traitsArray);
    qDebug()<<item->text(1).append("/traits");
    Dialog infoDialog(this,raceName, traitsArray);
    infoDialog.setModal(true); //blocks interactions with main windows
    infoDialog.exec(); //launch the dialog box
}


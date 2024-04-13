#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "secdialog.h"
#include<QLabel>
#include "dialog.h"
#include<QNetworkReply>
#include<QDebug>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QTreeWidget>
#include<QTreeWidgetItem>
#include"jsonmanipulation.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
    ui->progressBar->setValue(30);
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)), ui->progressBar, SLOT(setValue(int)));
    //disconnect(ui->horizontalSlider,SIGNAL(valueChanged(int)), ui->progressBar, SLOT(setValue(int)));
    */

    std::vector<std::string> raceNames {"Elf", "Human", "Dwarf", "Halfling", "Gnome"};
    //connect(&manager, &QNetworkAccessManager::finished, this, &MainWindow::onManagerFinished);
/*
    QNetworkRequest request(QUrl(urlBase.arg("races")));

    QNetworkReply *reply =manager.get(request);

    QEventLoop loop;
    QObject::connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();

    if(reply->error()==QNetworkReply::NoError){
        qDebug()<<"Error: "<<reply->errorString();
        QString Response = reply->readAll();
        qDebug()<<"API Response: "<<Response;

    }else{
        qDebug()<<"Error: "<<reply->errorString();
    }
*/
    //fetchData("races");

    QJsonArray jsonArrayRaceNames = {};
    QJsonDocument doc(jsonArrayRaceNames);
    //QJsonArray jsonRaces = {};
    //should probably do something if these fail (like try again)
    qDebug()<<jason.fetchData("/api/races", doc);
    //JsonManipulation *jason = new JsonManipulation();

    jason.getNamesFromJson(doc,jsonArrayRaceNames);
    //ui->textEdit->setPlainText(doc["results"].toString());

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
        //QListWidgetItem *newItem=new QListWidgetItem();
        //newItem->setText(raceName);
        //newItem->setWhatsThis(raceUrl);//theres gotta be a better way to store some hidden data
        qDebug()<<"url:"<<raceRoot->text(0);
        //ui->treeWidget->addItem(raceName);

/*TODO: Use correct data in dialouge when clicked*/
        //should only do this if clicked
        //QJsonDocument raceData = QJsonDocument();
        //fetchData(raceUrl, raceData);

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*
void MainWindow::on_pushButton_clicked()
{
    // SecDialog secDialog;
    // secDialog.setModal(true);
    // secDialog.exec();
    hide();
    secDialog=new SecDialog(this);
    secDialog->show();

}
*/

void MainWindow::AddRoot(QString name, QString description){
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0, name); //name in column0
    itm->setText(1,description);
    ui->treeWidget->addTopLevelItem(itm);

}
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

    QJsonObject dataObj = dataDoc.object();
    //create a new dialog box object
    Dialog infoDialog(this,&dataObj);
    infoDialog.setModal(true); //blocks interactions with main windows
    infoDialog.exec(); //launch the dialog box
}


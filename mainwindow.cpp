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
    QJsonDocument doc = QJsonDocument(jsonArrayRaceNames);
    //QJsonArray jsonRaces = {};
    //should probably do something if these fail (like try again)
    qDebug()<<fetchData("/api/races", doc);
    getNamesFromJson(doc,jsonArrayRaceNames);
    //ui->textEdit->setPlainText(doc["results"].toString());

    //get the names and urls from each to get more data

    for(auto raceNames: jsonArrayRaceNames){
        QJsonObject raceNameData = raceNames.toObject();
        QString raceName = raceNameData.value("name").toString();
        QString raceUrl = raceNameData.value("url").toString();
        ui->listWidget->addItem(raceName);
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
    ui->label->setText("button is clicked");

}
*/
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
bool MainWindow::fetchData(QString urlPath, QJsonDocument &document){
    QString urlBase ="https://www.dnd5eapi.co%1";

    QNetworkRequest request(QUrl(urlBase.arg(urlPath)));

    QNetworkReply *reply =manager.get(request);

    QEventLoop loop;
    QObject::connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();
    QString Response;
    bool success= false;
    if(reply->error()==QNetworkReply::NoError){
        qDebug()<<"Error: "<<reply->errorString();
        QByteArray Response = reply->readAll();
        qDebug()<<"API Response: "<<Response;

        QJsonParseError jsonError;
        document = QJsonDocument::fromJson( Response, &jsonError );
        if( jsonError.error != QJsonParseError::NoError )
        {
            qDebug() << "fromJson failed: " << jsonError.errorString().toStdString();

        }else{

            success = true;

        }

        /*
        if( document.isObject() )
        {
            QJsonObject jsonObj = document.object();
            //...
            qDebug() << "sucess";
            if( jsonObj.contains( "results") )
            {

                QJsonArray jsonArray = jsonObj.value("results").toArray();

                qDebug()<<"Found";
                QStringList keys = jsonObj.keys();
                qDebug()<<keys;
            }
        }
*/
    }else{
        qDebug()<<"Error: "<<reply->errorString();
    }

    return success;
}

/** Convert JSON Document to JSON Array
 *  @param jsonDoc: a Json Document consisting of count and result, where results will be the JSONArray
 *  @param jsonArray: stores the found JSONArray
 *  @return arrayLength: if successful, the value of "count" is returned, if the function fails, -1 is returned
*/
int MainWindow::getNamesFromJson(QJsonDocument jsonDoc, QJsonArray &jsonArray){
    int arrayLength = -1; //if -1 is returned, then the function was not sucessful
    //check if what is in the document is a viable object
    if( jsonDoc.isObject())
    {
        QJsonObject jsonObj = jsonDoc.object();
        //check if the keys are count and an array of results
        if(jsonObj.keys().contains("count")&&jsonObj.keys().contains("results"))
        {
            jsonArray = jsonObj.value("results").toArray();
            arrayLength=jsonObj.value("count").toInt(-1); //set default value to -1 if it fails
            qDebug() << "sucess";
        }
    }
    return arrayLength;//if -1 is returned, then the function was not sucessful
}

/**
 * Display a Dialog box which provides additional details about the Item clicked
 * @brief MainWindow::on_listWidget_itemClicked
 * @param item
 */
void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    Dialog infoDialog;
    infoDialog.setModal(true);
    infoDialog.exec();
}


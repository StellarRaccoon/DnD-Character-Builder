#include "jsonmanipulation.h"
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QNetworkReply>
#include<QDebug>
#include<QEventLoop>
JsonManipulation::JsonManipulation() {

}

bool JsonManipulation::fetchData(QString urlPath, QJsonDocument &document){
    QString urlBase ="https://www.dnd5eapi.co%1";
    qDebug()<<urlBase.arg(urlPath);
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
int JsonManipulation::getNamesFromJson(QJsonDocument jsonDoc, QJsonArray &jsonArray){
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

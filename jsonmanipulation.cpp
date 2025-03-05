#include "jsonmanipulation.h"
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QNetworkReply>
#include<QDebug>
#include<QEventLoop>
JsonManipulation::JsonManipulation() {

}

/**
 *
 * @brief connect to the DnD API with a asynch API call
 * @param urlPath path to the API request, typically starting with "/api/"
 * @return if sucessful, a QJsonDocument with the data from the API. If not sucessful the document will be empty
 */
QJsonDocument JsonManipulation::fetchData(QString urlPath){
    QString urlBase ="https://www.dnd5eapi.co%1";
    qDebug()<<urlBase.arg(urlPath);
    QNetworkRequest request(QUrl(urlBase.arg(urlPath)));

    QNetworkReply *reply =manager.get(request);

    //this is a synchronus network request method which can make the app unresponsive because loop.exec() block the main thread.
    //📌Add a loading page or symbol to prevent page freezing as data loads in
    //📌should try to make it asynch
    QEventLoop loop;
    QObject::connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();
    //QString Response;

    QJsonDocument jsonDoc;
    if(reply->error()==QNetworkReply::NoError){
        //qDebug()<<"Error: "<<reply->errorString();
        QByteArray Response = reply->readAll();
        //qDebug()<<"API Response: "<<Response;

        QJsonParseError jsonError;
        jsonDoc= QJsonDocument::fromJson( Response, &jsonError );
        if( jsonError.error != QJsonParseError::NoError )
        {
            qDebug() << "fromJson failed: " << jsonError.errorString().toStdString();
        }else{
            qDebug() << "Successful API call";
        }

    }else{
        qDebug()<<"Error: "<<reply->errorString();
    }

    return jsonDoc;
}


/** Convert JSON Document to JSON Array
 *  @param jsonDoc: a Json Document consisting of count and result, where results will be the JSONArray
 *  @param jsonArray: stores the found JSONArray
 *  @return arrayLength: if successful, the value of "count" is returned, if the function fails, -1 is returned
*/
QJsonArray JsonManipulation::getArrayFromJson(QString key,QJsonDocument jsonDoc){
    //check if what is in the document is a viable object
    QJsonArray jsonArray={};
    if( jsonDoc.isObject())
    {
        QJsonObject jsonObj = jsonDoc.object();
        //check if the keys are count and an array of results
        jsonArray = jsonObj.value(key).toArray();

    }
    return jsonArray;//if -1 is returned, then the function was not sucessful
}
//QString JsonMainpulation::getStringFromObjValue



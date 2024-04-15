#include "jsonmanipulation.h"
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QNetworkReply>
#include<QDebug>
#include<QEventLoop>
JsonManipulation::JsonManipulation() {

}

QJsonDocument JsonManipulation::fetchData(QString urlPath){
    QString urlBase ="https://www.dnd5eapi.co%1";
    qDebug()<<urlBase.arg(urlPath);
    QNetworkRequest request(QUrl(urlBase.arg(urlPath)));

    QNetworkReply *reply =manager.get(request);

    QEventLoop loop;
    QObject::connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();
    QString Response;

    QJsonDocument jsonDoc;
    bool success= false;
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
            success = true;
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



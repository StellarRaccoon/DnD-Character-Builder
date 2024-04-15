#ifndef JSONMANIPULATION_H
#define JSONMANIPULATION_H
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QNetworkReply>

class JsonManipulation
{
public:
    JsonManipulation();
    //int getArrayFromJson(QJsonDocument jsonDoc, QJsonArray &jsonArray);
    QJsonDocument fetchData(QString urlPath);
    QJsonArray getArrayFromJson(QString key,QJsonDocument jsonDoc);
private:
    QNetworkAccessManager manager;
};

#endif // JSONMANIPULATION_H

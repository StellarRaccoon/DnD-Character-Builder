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
    int getNamesFromJson(QJsonDocument jsonDoc, QJsonArray &jsonArray);
    bool fetchData(QString urlPath, QJsonDocument &document);
    QJsonArray getArrayFromJson(QString key,QJsonDocument jsonDoc, QJsonArray &jsonArray);
private:
    QNetworkAccessManager manager;
};

#endif // JSONMANIPULATION_H

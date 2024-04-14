#ifndef USERCHARACTER_H
#define USERCHARACTER_H
#include <QString>
#include <QList>
#include <QMap>
#include <QJsonArray>
#include"jsonmanipulation.h"
class UserCharacter
{
public:
    UserCharacter();
    void setUserRace(QString raceURL);
    QString getUserRace();
    QString toString();
private:
    QList<QString> userProficiencyUrls; //should be seperated by types?
    QString userClass;
    QString userRaceURL; //one for the url one for the name
    QMap<QString, int> userSkills;
    QMap<QString, int> userAbilityScore;
    QList<QString> userLanguages;
    QList<QString> userRaceTraits;
    JsonManipulation jason;
    //QList<QString> userRaceTraits;



};

#endif // USERCHARACTER_H

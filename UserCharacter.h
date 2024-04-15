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
    void setUserRace(QString raceUrl);
    void setUserClass(QString classUrl);
    QString getUserRace();
    QString toString();
    QMap<QString, int> getAbilityScores();
    void increaseAbilityScore(QString index, int value);
private:
    QMap<QString, int> userAbilityScore;
    QList<QJsonObject> userProficiencyUrls; //should be seperated by types?
    QString userClass;
    QString userClassUrl;
    QString userRaceURL; //one for the url one for the name
    QMap<QString, int> userSkills;
    QList<QString> userLanguages;
    QList<QJsonObject> userRaceTraits;
    JsonManipulation jason;
    QList<QString> userSavingThrows;
    void addProficiency(QJsonObject profBasic);
    int userHitDie;
    QMap<QString, int> userStartingEquipment;
    //QList<QString> userRaceTraits;



};

#endif // USERCHARACTER_H

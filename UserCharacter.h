#ifndef USERCHARACTER_H
#define USERCHARACTER_H
#include <QString>
#include <QList>
#include <QMap>
#include <QJsonArray>
#include"jsonmanipulation.h"
#include"SmallClasses.h"

class UserCharacter
{
public:
    UserCharacter();
    /** when a user race is slected..
     *  set ability bonuses
     *  proficienes
     *  langs
     *
    */
    void setUserRace(QString raceUrl);
    void setUserClass(QString classUrl);
    QString getUserRace();
    QString toString();
    AbilityValues getAbilityScores();
    void setAbilityScore(QString index, int value);
    QString getUserClass();
    void setCharacterName(QString characterName);
    QString getCharacterName();
    void setCharacterBackground(QString characterBackground);
    QString getCharacterBackground();
    void setPlayerName(QString playerName);
    QString getPlayerName();
    void setCharacterAlignment(QString characterAlignment);
    QString getCharacterAlignment();
    QList<QString> getCharacterProfs(char profsToGet);
private:
    QString characterName;
    QString characterBackground;
    QString playerName;
    QString characterAlignment;
    QString userClass;
    QString userClassUrl;
    QString userRaceURL; //one for the url one for the name
    int userHitDie;
    int userProfMod;
    AbilityValues *isSavingThrow;

    QList<QString> userLanguages;
    QList<QString> armorProfs;
    QList<QString> weaponProfs;
    QList<QString> toolProfs;
    QList<QString> otherProfs;
    QList<UserTrait> userRaceTraits;
    //QList<QString> userSavingThrows;

    AbilityValues *userAbilityScore; //need to fix in the main window and on ability score page
    QMap<QString, int> userAbilityMod;
    QMap<QString, int> userSkills;
    QMap<QString, int> userStartingEquipment;



    JsonManipulation jason;

    void addProficiency(QJsonObject profBasic);
    int calculateAbilityMod(int score, int bonus);

    //QList<QString> userRaceTraits;
//create a from json
};


#endif // USERCHARACTER_H

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
    UserCharacter(){
        Ability userChaScore = new Ability();
        Ability userConScore = new Ability();
        Ability userDexScore = new Ability();
        Ability userIntScore = new Ability();
        Ability userStrScore = new Ability();
        Ability userWisScore = new Ability();
        abilities.insert("cha",userChaScore);
        abilities.insert("con",userConScore);
        abilities.insert("dex",userDexScore);
        abilities.insert("int",userIntScore);
        abilities.insert("str",userStrScore);
        abilities.insert("wis",userWisScore);
    }
    /** when a user race is slected..
     *  set ability bonuses
     *  proficienes
     *  langs
     *
    */
    int userProfMod;
    int userSpeed;
    void setUserRace(QString raceUrl);
    void setUserClass(QString classUrl);
    QString toString();

    void setCharacterName(QString characterName);
    void setCharacterBackground(QString characterBackground);
    void setPlayerName(QString playerName);
    void setCharacterAlignment(QString characterAlignment);



    QString getUserRace();
    QString getUserClass();
    QString getCharacterName();
    QString getCharacterBackground();
    QString getPlayerName();
    QString getCharacterAlignment();
    QString getCharacterLanguages();
    QList<UserTrait> getUserTraits();
    void setSkillMod();
    QStringList getCharacterProfs(char profsToGet);
    QList<Skill> skills;

    QList<Equipment> userStartingEquipment;


private:
    QMap<QString,Ability*> abilities;
    QString characterName;
    QString characterBackground;
    QString playerName;
    QString characterAlignment;
    QString userClass;
    QString userClassUrl;
    QString userRaceURL; //one for the url one for the name
    int userHitDie;
    QString userRaceName;
    QList<QString> userLanguages;
    QList<QString> armorProfs;
    QList<QString> weaponProfs;
    QList<QString> toolProfs;
    QList<QString> otherProfs;
    QList<UserTrait> userRaceTraits;

    void setIsProficientSkill(QString skillName);
    //QList<QString> userSavingThrows;
    QMap<QString, int> userSkills;



    JsonManipulation jason;

    void addProficiency(QJsonObject profBasic);
    int calculateAbilityModFromIndex(QString abilityName);

    //QList<QString> userRaceTraits;
//create a from json
};


#endif // USERCHARACTER_H

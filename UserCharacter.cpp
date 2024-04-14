#include "UserCharacter.h"
#include<QJsonDocument>
#include"jsonmanipulation.h"
#include<QString>
UserCharacter::UserCharacter() {
    userAbilityScore["cha"] = 0;
    userAbilityScore["con"] = 0;
    userAbilityScore["dex"] = 0;
    userAbilityScore["int"] = 0;
    userAbilityScore["str"] = 0;
    userAbilityScore["wis"] = 0;
}

/** when a user race is slected..
 *  set ability bonuses
 *  proficienes
 *  langs
 *
*/
void UserCharacter::setUserRace(QString raceUrl){
    userRaceURL=raceUrl;

    QJsonDocument raceDoc;
    jason.fetchData(raceUrl,raceDoc);
    //jason.getArrayFromJson("traits",raceDoc, userRaceTraits);
    QJsonObject raceObj = raceDoc.object();
    QJsonArray startingProficencies={};
    QJsonArray languages={};
    QJsonArray abilityBonuses={};
    QJsonArray traits={};
    //will need to check for ability bonus options and starting profficency options
    if(raceObj.contains("ability_bonuses")){
        qDebug()<<"Abilities  True!";
        //jason.getArrayFromJson("ability_bonuses",raceDoc, abilityBonuses);
        abilityBonuses = raceObj.value("ability_bonuses").toArray();
        //set ability bonuses
        for(auto abilityBonus: abilityBonuses){
            QJsonObject bonusData = abilityBonus.toObject();
            QString abilityIndex=bonusData.value("ability_score").toObject().value("index").toString();
            userAbilityScore[abilityIndex]= bonusData.value("bonus").toInt();
            qDebug()<<abilityIndex<<": "<<userAbilityScore[abilityIndex];
        }
    }
    if(raceObj.contains("starting_proficiencies")){
        qDebug()<<"StartProfs True!";
        //jason.getArrayFromJson("starting_proficiencies",raceDoc, startingProficencies);
        startingProficencies= raceObj.value("starting_proficiencies").toArray();
        for(auto profs: startingProficencies){
            QJsonObject profObj = profs.toObject();
            userProficiencyUrls.append(profObj.value("index").toString());
            if(!userProficiencyUrls.isEmpty()){
            qDebug()<<userProficiencyUrls.last()<<": ";
            }
        }
    }
    if(raceObj.contains("languages")){
        languages= raceObj.value("languages").toArray();
        //jason.getArrayFromJson("languages",raceDoc, languages);
        for(auto langs: languages){
            QJsonObject langObj = langs.toObject();
            userLanguages.append(langObj.value("index").toString());
            if(!userLanguages.isEmpty()){
                qDebug()<<userLanguages.last()<<": ";
            }
        }
    }
    if(raceObj.contains("traits")){
        traits= raceObj.value("traits").toArray();
        for(auto trait:  traits){
            QJsonObject traitObj = trait.toObject();
            userRaceTraits.append(traitObj.value("index").toString());
            if(!userRaceTraits.isEmpty()){
                qDebug()<<userRaceTraits.last()<<": ";
            }
        }
    }

}

QString UserCharacter::toString(){
    QString characterStr = QString("Character Race: %1").arg(userRaceURL);
    QString abilityStr="\nAbilities: ";
    QMapIterator<QString, int> i(userAbilityScore);
    while (i.hasNext()) {
        i.next();
        abilityStr.append(QString("%1: %2, ").arg(i.key()).arg(i.value()));
    }
    QString langs = "\nLanguages: ";
    for(int i=0;i<userLanguages.size(); i++){
        langs.append(QString("%1, ").arg(userLanguages.at(i)));
    }
    QString profs = "\nProficiencies: ";
    for(int i=0;i<userProficiencyUrls.size(); i++){
        profs.append(QString("%1, ").arg(userProficiencyUrls.at(i)));
    }
    QString traitStr ="\ntraits: ";
    for(int i=0;i<userRaceTraits.size(); i++){
        traitStr.append(QString("%1, ").arg(userRaceTraits.at(i)));
    }
    characterStr=characterStr.append(abilityStr);
    characterStr=characterStr.append(langs);
    characterStr=characterStr.append(profs);
    characterStr=characterStr.append(traitStr);
    return characterStr;
}

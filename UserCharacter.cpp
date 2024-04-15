#include "UserCharacter.h"
#include<QJsonDocument>
#include"jsonmanipulation.h"
#include<QString>
#include<QJsonArray>
UserCharacter::UserCharacter() {
    userAbilityScore["cha"] = 0;
    userAbilityScore["con"] = 0;
    userAbilityScore["dex"] = 0;
    userAbilityScore["int"] = 0;
    userAbilityScore["str"] = 0;
    userAbilityScore["wis"] = 0;
}

/**
 * Add the full proficiency json obj to the user character array from a mini prof object
 * */
void UserCharacter::addProficiency(QJsonObject profBasic)
{
    userProficiencyUrls.append(jason.fetchData(profBasic.value("url").toString()).object());
}
void UserCharacter::setUserClass(QString classUrl){
    userClassUrl=classUrl;


    QJsonObject classObj = jason.fetchData(classUrl).object();



    userClass=classObj.value("name").toString();
    userHitDie=classObj.value("hit_die").toInt();


    //add starting profs
    if(classObj.contains("proficiencies")){
        QJsonArray classProficiencies= classObj.value("proficiencies").toArray();
        for(auto prof: classProficiencies){
            addProficiency(prof.toObject());
            if(!userProficiencyUrls.isEmpty()){
                qDebug()<<userProficiencyUrls.last()<<": ";
            }
        }
    }
    if(classObj.contains("saving_throws")){
        QJsonArray savingThrows= classObj.value("saving_throws").toArray();
        for(auto st: savingThrows){
            userSavingThrows.append(st.toObject().value("name").toString());
        }
    }
    if(classObj.contains("saving_throws")){
        QJsonArray startingEquipments= classObj.value("starting_equipment").toArray();
        for(auto equip: startingEquipments){
            QJsonObject equipData = equip.toObject();
            QString equipName=equipData.value("equipment").toObject().value("name").toString();
            userStartingEquipment[equipName]= equipData.value("quantity").toInt();
        }
    }



}
/** when a user race is slected..
 *  set ability bonuses
 *  proficienes
 *  langs
 *
*/
void UserCharacter::setUserRace(QString raceUrl){
    userRaceURL=raceUrl;


    QJsonObject raceObj = jason.fetchData(raceUrl).object();
    QJsonArray startingProficencies={};
    QJsonArray languages={};
    QJsonArray abilityBonuses={};
    QJsonArray raceTraits={};


    //Add Ability Scores to character. Ability scoresis a map of Ability: score
    //these are bonuses and will be added to the dice roll
    if(raceObj.contains("ability_bonuses")){
        abilityBonuses = raceObj.value("ability_bonuses").toArray();
        for(auto abilityBonus: abilityBonuses){
            QJsonObject bonusData = abilityBonus.toObject();
            QString abilityIndex=bonusData.value("ability_score").toObject().value("index").toString();
            userAbilityScore[abilityIndex]= bonusData.value("bonus").toInt();
            qDebug()<<abilityIndex<<": "<<userAbilityScore[abilityIndex];
        }
    }

    //add starting profs
    if(raceObj.contains("starting_proficiencies")){
        startingProficencies= raceObj.value("starting_proficiencies").toArray();
        for(auto prof: startingProficencies){
            addProficiency(prof.toObject());
            if(!userProficiencyUrls.isEmpty()){
            qDebug()<<userProficiencyUrls.last()<<": ";
            }
        }
    }
    if(raceObj.contains("languages")){
        languages= raceObj.value("languages").toArray();
        for(auto langs: languages){
            QJsonObject langObj = langs.toObject();
            userLanguages.append(langObj.value("index").toString());
            if(!userLanguages.isEmpty()){
                qDebug()<<userLanguages.last()<<": ";
            }
        }
    }

    //Add the Json Object of the trait to the character array of traits
    //need to loop through all the traits in the array, go to the url, get the object
    if(raceObj.contains("traits")){
        //get the array of traits from the race object, and loop through them
        raceTraits = raceObj.value("traits").toArray();
        for(auto trait:raceTraits){
            //get the url of the current trait
            QString traitUrl=trait.toObject().value("url").toString();
            //call the api on the trait and get the trait object
            //convert into an object
            QJsonObject traitObj = jason.fetchData(traitUrl).object();
            //check if the trait has  proficencies to add
            QJsonArray traitProfs = traitObj.value("proficiencies").toArray();
            if(!traitProfs.isEmpty()){
                for(auto prof:traitProfs){
                    addProficiency(prof.toObject());
                }
            }
            //add all languages from trait
            if(!traitObj.contains("languages")){
                languages= traitObj.value("languages").toArray();
                for(auto langs: languages){
                QJsonObject langObj = langs.toObject();
                userLanguages.append(langObj.value("index").toString());
                }

            }
            //add the object of the trait to the character array
            userRaceTraits.append(traitObj);
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
    // QString profs = "\nProficiencies: ";
    // for(int i=0;i<userProficiencyUrls.size(); i++){
    //     profs.append(QString("%1, ").arg(userProficiencyUrls.at(i)));
    // }
    // QString traitStr ="\ntraits: ";
    // for(int i=0;i<userRaceTraits.size(); i++){
    //     traitStr.append(QString("%1, ").arg(userRaceTraits.at(i)));
    // }
    characterStr=characterStr.append(abilityStr);
    characterStr=characterStr.append(langs);
    //characterStr=characterStr.append(profs);
    //characterStr=characterStr.append(traitStr);
    return characterStr;
}

QMap<QString, int> UserCharacter::getAbilityScores(){
    return userAbilityScore;
}
void UserCharacter::increaseAbilityScore(QString index, int value){
    userAbilityScore[index] = userAbilityScore[index]+value;

}

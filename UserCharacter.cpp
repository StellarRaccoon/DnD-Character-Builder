#include "UserCharacter.h"
#include<QJsonDocument>
#include"jsonmanipulation.h"
#include<QString>
#include<QJsonArray>
#include"SmallClasses.h"

UserCharacter::UserCharacter() {


    isSavingThrow = new AbilityValues();
    userAbilityScore=new AbilityValues();
    userProfMod =2;

    //fill out skills list
    QJsonArray skillArray=jason.getArrayFromJson("results",jason.fetchData("/api/skills"));
    for(auto skillRef:skillArray){
        QString skillUrl=skillRef.toObject().value("url").toString();
        //call the api on the trait and get the trait object
        //convert into an object
        QJsonObject skillObj = jason.fetchData(skillUrl).object();
        QString type = skillObj.value("nameability_score").toObject().value("index").toString();
        QString desc=skillObj.value("desc").toString();
        QString name=skillObj.value("name").toString();
        Skill newSkill =*new Skill(name,type,desc);
        skills.append(newSkill);
    }


}
void UserCharacter::setAbilityScore(QString key, int value){
    userAbilityScore->setFromIndex(key,value);
}

void UserCharacter::setIsProficientSkill(QString skillName){
    for(auto skill :skills){
        if(QString::compare(skill.name, skillName)==0){
            skill.isProficent=true;
        }
    }
}
/**
 * Add the full proficiency json obj to the user character array from a mini prof object
 * */
void UserCharacter::addProficiency(QJsonObject profBasic)
{

    QJsonObject profObj=jason.fetchData(profBasic.value("url").toString()).object();
    //get the name
    //get the type
    QString profType = profObj.value("type").toString();
    QString profName= profObj.value("name").toString();
    qDebug()<<"adding "<<profName<<" of type: "<<profType;
    if(QString::compare("Armor", profType)==0){
        armorProfs.append(profName);
    }else if(QString::compare("Weapons", profType)==0){
        weaponProfs.append(profName);
    }else if(QString::compare("Tools", profType)==0){
        toolProfs.append(profName);

    }else if(QString::compare("Skill", profType,Qt::CaseInsensitive)==0){
        setIsProficientSkill(profName);
    }else if(QString::compare("Saving Throws", profType)&QString::compare("Language", profName)){
        otherProfs.append(profName);
    }


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

        }
    }
    if(classObj.contains("saving_throws")){
        QJsonArray savingThrows= classObj.value("saving_throws").toArray();

        for(auto st: savingThrows){
            QString stString =st.toObject().value("index").toString();
            isSavingThrow->setFromIndex(stString, 1);

        }
    }
    if(classObj.contains("starting_equipment")){
        QJsonArray startingEquipments= classObj.value("starting_equipment").toArray();
        QList<Equipment> startEquip = {};
        for(auto equip: startingEquipments){
            QJsonObject equipData = equip.toObject();
            QString equipName=equipData.value("equipment").toObject().value("name").toString();
            Equipment *newEquip= new Equipment(equipName,equipData.value("quantity").toInt());
            startEquip.append(*newEquip);
        }
        userStartingEquipment=startEquip;
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

    userRaceName=raceObj.value("name").toString();
    userSpeed=raceObj.value("speed").toInt();
    //Add Ability Scores to character. Ability scoresis a map of Ability: score
    //these are bonuses and will be added to the dice roll
    if(raceObj.contains("ability_bonuses")){
        abilityBonuses = raceObj.value("ability_bonuses").toArray();
        for(auto abilityBonus: abilityBonuses){
            QJsonObject bonusData = abilityBonus.toObject();
            QString abilityIndex=bonusData.value("ability_score").toObject().value("index").toString();
            //isSavingThrow->setFromIndex(abilityIndex,bonusData.value("bonus").toInt());
            userAbilityScore->setFromIndex(abilityIndex,bonusData.value("bonus").toInt());
        }
    }

    //add starting profs
    if(raceObj.contains("starting_proficiencies")){
        startingProficencies= raceObj.value("starting_proficiencies").toArray();
        for(auto prof: startingProficencies){
            addProficiency(prof.toObject());

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
        QList<UserTrait> tempTraits;
        for(auto trait:raceTraits){
            //get the url of the current trait
            QString traitUrl=trait.toObject().value("url").toString();
            //call the api on the trait and get the trait object
            //convert into an object
            QJsonObject traitObj = jason.fetchData(traitUrl).object();
            //check if the trait has  proficencies to add
            QJsonArray traitProfs = traitObj.value("proficiencies").toArray();
            UserTrait *uT = new UserTrait(traitObj.value("name").toString(), traitObj.value("desc").toString());
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
            qDebug()<<"adding: "<<uT->getTraitName()<<" --- "<<uT->getTraitDesc();

            tempTraits.append(*uT);
        }
        userRaceTraits=tempTraits;
    }
}

AbilityValues UserCharacter::getAbilityScores(){
    return *userAbilityScore;
}

QString UserCharacter::getUserRace(){
    return userRaceName;

}
QString UserCharacter::getUserClass(){
    return userClass;

}
QString UserCharacter::getCharacterName(){
    return characterName;
}
QString UserCharacter::getCharacterBackground(){
    return characterBackground;
}
QString UserCharacter::getPlayerName(){
    return playerName;
}
QString UserCharacter::getCharacterAlignment(){
    return characterAlignment;
}
void UserCharacter::setCharacterName(QString characterName){
    this->characterName=characterName;
}

int UserCharacter::calculateAbilityModFromIndex(QString abilityName){
    //qDebug()<<userAbilityValue.getValueFromIndex(abilityName);
    return ceil((userAbilityScore->getValueFromIndex(abilityName)-10)/2);
}
void UserCharacter::setCharacterBackground(QString characterBackground){
    this->characterBackground=characterBackground;
}
void UserCharacter::setPlayerName(QString playerName){
    this->playerName=playerName;
}
void UserCharacter::setCharacterAlignment(QString characterAlignment){
    this->characterAlignment=characterAlignment;
}
QStringList UserCharacter::getCharacterProfs(char profsToGet){
    QStringList profs;
    if(profsToGet=='w'){
        profs=weaponProfs;
    }else if(profsToGet=='t'){
        profs=toolProfs;
    }else if(profsToGet=='a'){
        profs=armorProfs;
    }else if(profsToGet=='l'){
        profs=userLanguages;
    }
    else{
        profs=otherProfs;
    }
    return profs;
}
QList<UserTrait> UserCharacter::getUserTraits(){
    return userRaceTraits;
}
AbilityValues UserCharacter::getIsSavingThrows(){
    return *isSavingThrow;
}

AbilityValues UserCharacter::getAbilityMod(){

    return userAbilityMod;
}
void UserCharacter::setUserAbilityMod(){

    userAbilityMod.strength=calculateAbilityModFromIndex("str");
    userAbilityMod.dexterity=calculateAbilityModFromIndex("dex");
    userAbilityMod.constitution=calculateAbilityModFromIndex("con");
    userAbilityMod.intelligence=calculateAbilityModFromIndex("int");
    userAbilityMod.wisdom=calculateAbilityModFromIndex("wis");
    userAbilityMod.charisma=calculateAbilityModFromIndex("cha");

}
AbilityValues UserCharacter::getSavingThrowValues(){
    userSavingThrows.strength = userAbilityMod.getValueFromIndex("str")+(isSavingThrow->strength*userProfMod);
    userSavingThrows.intelligence = userAbilityMod.getValueFromIndex("int")+(isSavingThrow->intelligence*userProfMod);
    userSavingThrows.wisdom = userAbilityMod.getValueFromIndex("wis")+(isSavingThrow->wisdom*userProfMod);
    userSavingThrows.constitution = userAbilityMod.getValueFromIndex("con")+(isSavingThrow->constitution*userProfMod);
    userSavingThrows.dexterity = userAbilityMod.getValueFromIndex("dex")+(isSavingThrow->dexterity*userProfMod);
    userSavingThrows.charisma = userAbilityMod.getValueFromIndex("cha")+(isSavingThrow->charisma*userProfMod);
    return userSavingThrows;
}
void UserCharacter::setSkillMod(){

    for(auto skill :skills){
        skill.modifier = userAbilityMod.getValueFromIndex(skill.abilityIndex);
        if(skill.isProficent){
            skill.modifier=skill.modifier+2;
        }
    }

}


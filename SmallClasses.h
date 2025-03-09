#ifndef SMALLCLASSES_H
#define SMALLCLASSES_H
#include<QString>
class UserTrait{
    QString name;
    QString description;
public:
    UserTrait(QString name, QString desc){
        this->name=name;
        this->description=desc;
    }
    QString getTraitName(){
        return name;
    }
    QString getTraitDesc(){
        return description;
    }
};
class Skill{
public:
    QString name;
    QString abilityIndex;
    QString description;
    int modifier;
    bool isProficent;
    Skill(QString name, QString type, QString desc){
        this->name=name;
        this->abilityIndex=type;
        this->description=desc;
        this->isProficent=false;
        this->modifier=0;
    }
};

class Ability{
public:
    int getTotal() const;

    int getBaseScore() const;
    void setBaseScore(int newBaseScore);
    void setBaseScore(QString newBaseScore);

    int getModScore() const;

    int getBonusScore() const;
    void setBonusScore(int newBonusScore);

    bool getIsSavingThrow() const;
    void setIsSavingThrow(bool newIsSavingThrow);

private:
    bool isSavingThrow =false;
    int baseScore;
    int modScore;
    int bonusScore;
};
inline int Ability::getTotal() const{
    return this->bonusScore+this->baseScore;
}
inline int Ability::getBaseScore() const
{
    return baseScore;
}

inline void Ability::setBaseScore(int newBaseScore)
{
    baseScore = newBaseScore;
}
/**
 * @brief Overload accepting a string of the score value
 * @param newBaseScore
 */
inline void Ability::setBaseScore(QString newBaseScore)
{
    baseScore = newBaseScore.toInt();
}
inline int Ability::getModScore() const
{
    return ceil((getTotal()-10)/2);
}

inline int Ability::getBonusScore() const
{
    return bonusScore;
}

inline void Ability::setBonusScore(int newBonusScore)
{
    bonusScore = newBonusScore;
}

inline bool Ability::getIsSavingThrow() const
{
    return isSavingThrow;
}

inline void Ability::setIsSavingThrow(bool newIsSavingThrow)
{
    isSavingThrow = newIsSavingThrow;
}



class AbilityValues{
public:
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
    AbilityValues(){
        this->strength=0;
        this->dexterity=0;
        this->constitution=0;
        this->intelligence=0;
        this->wisdom=0;
        this->charisma=0;
    }
    void setFromIndex(QString abilityName, int value){
        if(QString::compare("str",abilityName,Qt::CaseInsensitive)==0){
            this->strength =value+this->strength;
        }
        else if(QString::compare("wis",abilityName,Qt::CaseInsensitive)==0){
            this->wisdom=value+this->wisdom;
        }else if(QString::compare("dex",abilityName,Qt::CaseInsensitive)==0){
            this->dexterity=value+this->dexterity;
        }else if(QString::compare("con",abilityName,Qt::CaseInsensitive)==0){
            this->constitution =value+this->constitution;
        }
        else if(QString::compare("int",abilityName,Qt::CaseInsensitive)==0){
            this->intelligence =value+this->intelligence;
        }else if(QString::compare("cha",abilityName,Qt::CaseInsensitive)==0){
            this->charisma =value+this->charisma;
        }
    }
    void increaseScoreIndex(QString abilityName, int value){
        if(QString::compare("str",abilityName,Qt::CaseInsensitive)==0){
            this->strength =value+this->strength;
        }
        else if(QString::compare("wis",abilityName,Qt::CaseInsensitive)==0){
            this->wisdom=value+this->wisdom;
        }else if(QString::compare("dex",abilityName,Qt::CaseInsensitive)==0){
            this->dexterity=value+this->dexterity;
        }else if(QString::compare("con",abilityName,Qt::CaseInsensitive)==0){
            this->constitution =value+this->constitution;
        }
        else if(QString::compare("int",abilityName,Qt::CaseInsensitive)==0){
            this->intelligence =value+this->intelligence;
        }else if(QString::compare("cha",abilityName,Qt::CaseInsensitive)==0){
            this->charisma =value+this->charisma;
        }
    }

    int getValueFromIndex(QString abilityName){
        int value=0;
        if(QString::compare("str",abilityName,Qt::CaseInsensitive)==0){
            value=this->strength;
        }
        else if(QString::compare("wis",abilityName,Qt::CaseInsensitive)==0){
            value=this->wisdom;
        }else if(QString::compare("dex",abilityName,Qt::CaseInsensitive)==0){
            value=this->dexterity;
        }else if(QString::compare("con",abilityName,Qt::CaseInsensitive)==0){
            value=this->constitution;
        }
        else if(QString::compare("int",abilityName,Qt::CaseInsensitive)==0){
            value=this->intelligence;
        }else if(QString::compare("cha",abilityName,Qt::CaseInsensitive)==0){
            value=this->charisma;
        }
        return value;
    }
};
class Equipment{
public:
    QString name;
    int quantity;
    QString description;
    QString category;
    Equipment(QString name, int quant){
        this->name=name;
        this->quantity=quant;
    }
};


#endif // SMALLCLASSES_H

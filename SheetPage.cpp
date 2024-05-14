#include "SheetPage.h"

#include "ui_SheetPage.h"

#include<QTextDocument>
#include<QVBoxLayout>
#include<QGridLayout>
#include<QtCore>
#include<QtGui>
#include<QSpinBox>
#include"SmallClasses.h" //want to eventually not include this
#include"UserCharacter.h"
SheetPage::SheetPage(UserCharacter *inuserChar,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SheetPage)
{
    ui->setupUi(this);
    userChar=inuserChar;
    qDebug()<<userChar->getUserClass();
    //set class
    ui->classBox->setText(userChar->getUserClass());
    //set race
    ui->raceBox->setText(userChar->getUserRace());
    //set basic info
    ui->playerNameBox->setText(userChar->getPlayerName());
    ui->charName->setText(userChar->getCharacterName());
    ui->backgroundNameBox->setText(userChar->getCharacterBackground());
    ui->profBonusBox->setPlainText(QString::number(userChar->userProfMod));
    ui->alignmentBox->setText(userChar->getCharacterAlignment());
    //set prof tab
    ui->languageProficienciesBox->setPlainText(userChar->getCharacterProfs('l').join(", "));
    ui->armorProficienciesBox->setPlainText(userChar->getCharacterProfs('a').join(", "));
    ui->toolProficienciesBox->setPlainText(userChar->getCharacterProfs('t').join(", "));
    ui->weaponProficienciesBox->setPlainText(userChar->getCharacterProfs('w').join(", "));
    ui->otherProficienciesBox->setPlainText(userChar->getCharacterProfs('o').join(", "));

    //set Ability Scores
    AbilityValues abScore =userChar->getAbilityScores();
    ui->strScoreBox->setText(QString::number(abScore.getValueFromIndex("str")));
    ui->wisScoreBox->setText(QString::number(abScore.getValueFromIndex("wis")));
    ui->dexScoreBox->setText(QString::number(abScore.getValueFromIndex("dex")));
    ui->intScoreBox->setText(QString::number(abScore.getValueFromIndex("int")));
    ui->chaScoreBox->setText(QString::number(abScore.getValueFromIndex("cha")));
    ui->conScoreBox->setText(QString::number(abScore.getValueFromIndex("con")));

    //set ability mods
    AbilityValues abMods=userChar->getAbilityMod();
    ui->wisModBox->setText(QString::number(abMods.getValueFromIndex("wis")));
    ui->strModBox->setText(QString::number(abMods.getValueFromIndex("str")));
    ui->dexModBox->setText(QString::number(abMods.getValueFromIndex("dex")));
    ui->intModBox->setText(QString::number(abMods.getValueFromIndex("int")));
    ui->chaModBox->setText(QString::number(abMods.getValueFromIndex("cha")));
    ui->conModBox->setText(QString::number(abMods.getValueFromIndex("con")));

    //getSavingThrow Values
    AbilityValues stValue=userChar->getSavingThrowValues();
    ui->strThrowBox->setText(QString::number(stValue.getValueFromIndex("str")));
    ui->wisThrowBox->setText(QString::number(stValue.getValueFromIndex("wis")));
    ui->dexThrowBox->setText(QString::number(stValue.getValueFromIndex("dex")));
    ui->intThrowBox->setText(QString::number(stValue.getValueFromIndex("int")));
    ui->chaThrowBox->setText(QString::number(stValue.getValueFromIndex("cha")));
    ui->conThrowBox->setText(QString::number(stValue.getValueFromIndex("con")));

    //check saving throw buttons
    AbilityValues isThrow=userChar->getIsSavingThrows();
    ui->strThrowProfBox->setChecked(isThrow.getValueFromIndex("str")==1);
    ui->wisThrowProfBox->setChecked(isThrow.getValueFromIndex("wis")==1);
    ui->dexThrowProfBox->setChecked(isThrow.getValueFromIndex("dex")==1);
    ui->intThrowProfBox->setChecked(isThrow.getValueFromIndex("int")==1);
    ui->chaThrowProfBox->setChecked(isThrow.getValueFromIndex("cha")==1);
    ui->conThrowProfBox->setChecked(isThrow.getValueFromIndex("con")==1);



    //set race trait tab
    QVBoxLayout *traitTabLayout =new QVBoxLayout();


    for(auto trait:userChar->getUserTraits()){
        QHBoxLayout *traitLayout=new QHBoxLayout();
        QPlainTextEdit *traitDescription = new QPlainTextEdit();
        traitDescription->setPlainText(trait.getTraitDesc());
        qDebug()<<trait.getTraitDesc();
        QLabel *traitName = new QLabel();
        traitName->setText(trait.getTraitName());
        traitLayout->addWidget(traitName);
        traitLayout->addWidget(traitDescription);
        traitTabLayout->addItem(traitLayout);
    }

    ui->traitTab->setLayout(traitTabLayout);
    QVBoxLayout *equipTabLayout =new QVBoxLayout();
    for(auto equip:userChar->userStartingEquipment){
        QHBoxLayout *equipLayout=new QHBoxLayout();

        QLabel *equipName = new QLabel();
        QLabel *equipQuant = new QLabel();
        equipName->setText(equip.name);
        equipQuant->setText(QString::number(equip.quantity));
        equipLayout->addWidget(equipName);
        equipLayout->addWidget(equipQuant);
        equipTabLayout->addItem(equipLayout);
    }
    ui->equipTab->setLayout(equipTabLayout);

    QVBoxLayout *skillsBoxLayout =new QVBoxLayout();

    for(auto skill:userChar->skills){
        qDebug()<<"adding skill";
        QHBoxLayout *skillLayout=new QHBoxLayout();
        QLabel *skillAbility= new QLabel();
        skillAbility->setText(skill.abilityIndex.toUpper());
        QLabel *skillName = new QLabel();
        skillName->setText(skill.name);
        QCheckBox *isProfCheck = new QCheckBox();
        isProfCheck->setChecked(skill.isProficent);
        QLineEdit *skillMod = new QLineEdit();
        skillMod->setText(QString::number(skill.modifier));

        skillLayout->addWidget(isProfCheck);
        skillLayout->addWidget(skillName);
        skillLayout->addWidget(skillAbility);
        skillLayout->addWidget(skillMod);
        skillsBoxLayout->addItem(skillLayout);
    }
    ui->skillsBox->setLayout(skillsBoxLayout);


}


SheetPage::~SheetPage()
{
    delete ui;
}

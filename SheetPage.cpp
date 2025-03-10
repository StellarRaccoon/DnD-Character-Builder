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
    qDebug()<<"-----------Sheet Page--------";
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

    //set Ability Scoresfrom the user score map

    //AbilityValues abScore =userChar->get();
    ui->strScoreBox->setText(QString::number(userChar->getAbility("str")->getTotal()));
    ui->wisScoreBox->setText(QString::number(userChar->getAbility("wis")->getTotal()));
    ui->dexScoreBox->setText(QString::number(userChar->getAbility("dex")->getTotal()));
    ui->intScoreBox->setText(QString::number(userChar->getAbility("int")->getTotal()));
    ui->chaScoreBox->setText(QString::number(userChar->getAbility("cha")->getTotal()));
    ui->conScoreBox->setText(QString::number(userChar->getAbility("con")->getTotal()));

    //set ability mods
    //AbilityValues abMods=userChar->getAbilityMod();
    ui->strModBox->setText(QString::number(userChar->getAbility("str")->getModScore()));
    ui->wisModBox->setText(QString::number(userChar->getAbility("wis")->getModScore()));
    ui->dexModBox->setText(QString::number(userChar->getAbility("dex")->getModScore()));
    ui->intModBox->setText(QString::number(userChar->getAbility("int")->getModScore()));
    ui->chaModBox->setText(QString::number(userChar->getAbility("cha")->getModScore()));
    ui->conModBox->setText(QString::number(userChar->getAbility("con")->getModScore()));

    //getSavingThrow Values
    //AbilityValues stValue=userChar->getSavingThrowValues();
    ui->strThrowBox->setText(QString::number(userChar->getAbility("str")->getModScore()+(userChar->userProfMod * userChar->getAbility("str")->getIsSavingThrow())));
    ui->wisThrowBox->setText(QString::number(userChar->getAbility("wis")->getModScore()+(userChar->userProfMod * userChar->getAbility("wis")->getIsSavingThrow())));
    ui->dexThrowBox->setText(QString::number(userChar->getAbility("dex")->getModScore()+(userChar->userProfMod * userChar->getAbility("dex")->getIsSavingThrow())));
    ui->intThrowBox->setText(QString::number(userChar->getAbility("int")->getModScore()+(userChar->userProfMod * userChar->getAbility("int")->getIsSavingThrow())));
    ui->chaThrowBox->setText(QString::number(userChar->getAbility("cha")->getModScore()+(userChar->userProfMod * userChar->getAbility("cha")->getIsSavingThrow())));
    ui->conThrowBox->setText(QString::number(userChar->getAbility("con")->getModScore()+(userChar->userProfMod * userChar->getAbility("con")->getIsSavingThrow())));

    //check saving throw buttons
    //AbilityValues isThrow=userChar->getIsSavingThrows();
    ui->strThrowProfBox->setChecked(userChar->getAbility("str")->getIsSavingThrow());
    ui->wisThrowProfBox->setChecked(userChar->getAbility("wis")->getIsSavingThrow());
    ui->dexThrowProfBox->setChecked(userChar->getAbility("dex")->getIsSavingThrow());
    ui->intThrowProfBox->setChecked(userChar->getAbility("int")->getIsSavingThrow());
    ui->chaThrowProfBox->setChecked(userChar->getAbility("cha")->getIsSavingThrow());
    ui->conThrowProfBox->setChecked(userChar->getAbility("con")->getIsSavingThrow());



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

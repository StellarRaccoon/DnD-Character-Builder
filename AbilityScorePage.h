#ifndef ABILITYSCOREPAGE_H
#define ABILITYSCOREPAGE_H
#include<QSignalMapper>
#include <QWidget>
#include<QComboBox>
#include<QVBoxLayout>
#include<QLabel>
#include"SmallClasses.h"
#include <QStandardItemModel>
#include "ScoreComboBox.h"
#include <QMap>
namespace Ui {
class AbilityScorePage;
}

class AbilityScorePage : public QWidget
{
    Q_OBJECT

public:
    //void extracted(int &i);
    explicit AbilityScorePage(QWidget *parent = nullptr);
    ~AbilityScorePage();
    QList<int> updatedScores;
    int getBoxScore(QString abIndex);

    QMap<QString, int> getCharAbilityBonus() const;
    void setCharAbilityBonus(QString abilityIndex, int bonusValue); //set a key:value pair

private:
    QStandardItemModel *scoreModel;
    AbilityValues userScores;
    QStringList comboOptions;
    //QList <ScoreComboBox *> boxes;
    QMap<QString,ScoreComboBox*> boxes;
    Ui::AbilityScorePage *ui;
    QMap<QString, int> charAbilityBonus; //ability bonus for the character, keyed by the ability index, loaded when page is loaded into


public slots:
    void on_comboBox_text_changed(QString boxIndex, int scoreIndex);
};


#endif // ABILITYSCOREPAGE_H

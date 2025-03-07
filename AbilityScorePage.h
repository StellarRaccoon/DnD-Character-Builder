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

namespace Ui {
class AbilityScorePage;
}

class AbilityScorePage : public QWidget
{
    Q_OBJECT

public:
    void extracted(int &i);
    explicit AbilityScorePage(QWidget *parent = nullptr);
    ~AbilityScorePage();
    // public slots:
    //QMap<QString,int> &startingScores;
    AbilityValues updatedScores;
private:
    QStandardItemModel *scoreModel;
    AbilityValues userScores;
    QStringList comboOptions;
    //QStringList currentOptions;
    QHBoxLayout * hbox;
    QStringList labels;
    QList <ScoreComboBox *> boxes;
    QMap <QComboBox *, QString> m_previousText;
    QList<QLabel *> totalScores;

    Ui::AbilityScorePage *ui;
public slots:
    void on_comboBox_activated(int boxIndex, int scoreIndex);
    void on_score_selected(QString score);

};


#endif // ABILITYSCOREPAGE_H

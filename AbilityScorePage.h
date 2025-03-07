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
    AbilityValues updatedScores;
private:
    QStandardItemModel *scoreModel;
    AbilityValues userScores;
    QStringList comboOptions;
    QList <ScoreComboBox *> boxes;
    Ui::AbilityScorePage *ui;
public slots:
    void on_comboBox_text_changed(int boxIndex, int scoreIndex);
};


#endif // ABILITYSCOREPAGE_H

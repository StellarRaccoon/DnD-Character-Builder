#ifndef ABILITYSCOREPAGE_H
#define ABILITYSCOREPAGE_H
#include<QSignalMapper>
#include <QWidget>
#include<QComboBox>
#include<QVBoxLayout>
#include<QLabel>
#include"SmallClasses.h"
#include <QStandardItemModel>
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
    void on_comboBox_activated(int index);
    void on_score_selected(QString score);
    AbilityValues updatedScores;
private:
    QStandardItemModel *scoreModel;
    AbilityValues userScores;
    QStringList comboOptions;
    //QStringList currentOptions;
    QHBoxLayout * hbox;
    QStringList labels;
    QList <QComboBox *> boxes;
    QMap <QComboBox *, QString> m_previousText;
    QList<QLabel *> totalScores;
    int prevScoreIndex;
    Ui::AbilityScorePage *ui;

};

#endif // ABILITYSCOREPAGE_H

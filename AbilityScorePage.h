#ifndef ABILITYSCOREPAGE_H
#define ABILITYSCOREPAGE_H
#include<QSignalMapper>
#include <QWidget>
#include<QComboBox>
#include<QVBoxLayout>
#include<QLabel>
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
    void on_comboBox_activated(int optionSelected, int activeBoxIndex);
    QMap<QString, int> updatedScores;
private:
    QMap<QString, int> userScores;
    QStringList comboOptions;
    //QStringList currentOptions;
    QHBoxLayout * hbox;
    QStringList labels;
    QList <QComboBox *> boxes;
    QMap <QComboBox *, QString> m_previousText;
    QList<QLabel *> totalScores;
   // QSignalMapsper *comboMapper;
    Ui::AbilityScorePage *ui;

};

#endif // ABILITYSCOREPAGE_H

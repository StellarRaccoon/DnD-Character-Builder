#ifndef EXTRASPAGE_H
#define EXTRASPAGE_H

#include <QWidget>

namespace Ui {
class extrasPage;
}

class extrasPage : public QWidget
{
    Q_OBJECT

public:
    explicit extrasPage(QWidget *parent = nullptr);
    ~extrasPage();
   QString getCharacterName();
    QString getCharacterBackground();
    QString getPlayerName();
    QString getCharacterAlignment();

private:
    Ui::extrasPage *ui;
};

#endif // EXTRASPAGE_H

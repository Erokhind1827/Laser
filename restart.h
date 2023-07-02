#ifndef RESTART_H
#define RESTART_H

#include <QWidget>
#include <QObject>
#include <QtWidgets>

class Restart : public QWidget//окошечко рестарта
{
    Q_OBJECT

public:
    Restart(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    ~Restart();
private:
    QImage bg;
    bool opened=false;
    QPushButton *restart, *menu, *save;
    QLabel* scr;
    QLabel *pl, *ri;
    QPixmap* pix;
signals:
    void setActive(int);
private slots:
    void goMenu();
    void goRestart();
    void goSave();
public slots:
    void getScore(double);
};
#endif // RESTART_H

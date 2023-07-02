#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QObject>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class menu; }
QT_END_NAMESPACE

class menu : public QWidget// сам лазер
{
    Q_OBJECT

public:
    menu(QWidget *parent = nullptr);
    ~menu();
protected:
    void paintEvent(QPaintEvent*);
private:
    QImage bg;
    QLineEdit* usernm;
    QRadioButton *easy,*hard;
//    double g=9.8;
    int amount=5;
    int r=154,g=205,b=50;
    QString level="easy",username="";
//    bool showt=false;
    QTableWidget* leaderboard;
    Ui::menu *ui;
signals:
    void setActiveWidget(int);// поменять активное окно
    void transferP(int,int,int,int,QString,QString);// передать параметры лазеру
public slots:
    void rChanged(int red);
    void gChanged(int green);
    void bChanged(int blue);//три слота для изменения цвета лазера
    void aChanged(int a);// менять макс колво зеркал
    void pressEasy(bool);
    void pressHard(bool);// для выбора уровня сложности
//    void pressMars(bool);
    void start();// нажата кнопка старт
    void getScore(double);// получение результата после окончания лазера
};
#endif // MENU_H

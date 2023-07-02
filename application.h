#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include "menu.h"
#include "laser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class application; }
QT_END_NAMESPACE

class application : public QMainWindow// основное приложение, связующее для всех виджетов
{
    Q_OBJECT

public:
    application(QWidget *parent = nullptr);
    ~application();
public slots:
    void transfer(int,int,int,int,QString,QString);// передаем в виджет лазера данные, которые мы выбрали в меню
//    void newThrow(int){missile1=new missile;};
    void getScore(double);// получаем резульат от нашего лазера и отправляем в меню в таблицу лидеров
    void goMenu();// переход в меню по кнопке menu
signals:
    void transferForvard(int,int,int,int,QString,QString);// сигнал в котором передаем данные лазеру
//    void sendResults(double,double,double,double,double);
    void sendScore(double);// сигнал по которому передаем результат в меню

private:
    menu* Menu;
    laser* Laser;
    QStackedWidget* mWidget;
    QMenuBar *menuBar1;
    QMenu* pmnu;
    QString Username;
    double score;
    bool menuActive=false;
    Ui::application *ui;
};
#endif // APPLICATION_H

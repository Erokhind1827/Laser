#ifndef LASER_H
#define LASER_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <ctime>
#include <random>
#include <cmath>
#include <QPrinter>
#include <restart.h>
//#include <QPair>

QT_BEGIN_NAMESPACE
namespace Ui { class laser; }
QT_END_NAMESPACE

class laser : public QWidget//окошко меню
{
    Q_OBJECT

public:
    laser(QWidget *parent = nullptr);
    ~laser();
protected:
    void paintEvent(QPaintEvent*);// рисовашка
    void mouseReleaseEvent (QMouseEvent* pe);// событие отпуска мыши
    void mouseMoveEvent (QMouseEvent* pe);// событие передвижения зажатой мыши
    void mousePressEvent (QMouseEvent* pe);// событие нажатия мыши
    void resizeEvent(QResizeEvent* re);// изменение размера
    void keyPressEvent(QKeyEvent* ke);// нажатие клавишы
private:
    void draw(QPainter& paint);// ф-я рисования движущегося участка лазера
    void drawBorders(QPainter& paint);// ф-я рисования зеркал
    void drawLines(QPainter& paint);// ф-я рисования статичного участка лазера
    void drawLaser(QPainter& paint);// ф-я рисования фонарика
    void drawAim(QPainter& paint);// ф-я рисования мишени
    bool intersect(QPair<QPair<double,double>,QPair<double,double>>,int i);// ф-я просчета пересечения луча с и-тым зеркалом (тру/фолс)
    void changeDirection(int);// ф-я сменынаправления для лазера
    double xcord=0,ycord=0,x=0,y=0,dx=0,dy=0,xstart,ystart,yAim=800,da=0.5,aimSize=0;/*,xintrs=0,yintrs=0*/;// всевозможные координаты
    double *xintrs,*yintrs;// будут массивы с точками пересечения
    double h=0,w=0,score=0;
    int borderAmount=0,clicks=0,lWidth=2,maxRefl=7;
    int* rgb;
    QImage aim;
    QPair<double,double> vector/* направляющий вектор*/,bstart,bend;// пары для задания зеркал
    QString level="easy",username;
    bool reflected=false,ready=false;
    QVector<bool> intersected;// вектор с тру/фолс переменными проверяющих пересечение
    QVector<QPair<QPair<double,double>,QPair<double,double>>> lines,borders;// векторы зеркал и статичных отрезков лазера
    QTimer* timer;
    QPixmap res;
    Restart* r;//окно рестарта
    Ui::laser *ui;
private slots:
    void OnTimer();
public slots:
    void setP(int,int,int,int,QString,QString);// получили параметры из меню - задали их в лазере
    void restart();// вроде логично
    void save();// тоже логично
    void send(){emit sendFinalScore(score);};// отправить результат в меню
//    void save(QPixmap&);
signals:
    void setActiveWidget(int);// сделать активным другое окно
    void sendScore(double);// отправить результат в окно рестарта
    void sendFinalScore(double);// отправить результат в меню
};
#endif // LASER_H

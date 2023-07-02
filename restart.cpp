#include "restart.h"

Restart::Restart(QWidget *parent)
    : QWidget(parent)
{
    bg=QImage("menubg");
    restart=new QPushButton("Restart");
    menu=new QPushButton("Menu");
    save=new QPushButton("Save");
    QFont fontbtns("Helvetica");
    fontbtns.setBold(true);
    restart->setFont(fontbtns);
    menu->setFont(fontbtns);
    restart->setMinimumHeight(50);
    save->setFont(fontbtns);
    save->setMinimumHeight(50);
    menu->setMinimumHeight(50);
    QHBoxLayout* btns=new QHBoxLayout();
    btns->addWidget(restart);
    btns->addWidget(menu);
    btns->addWidget(save);
    connect(restart,SIGNAL(clicked()),this,SLOT(goRestart()));
    connect(menu,SIGNAL(clicked()),this,SLOT(goMenu()));
    connect(save,SIGNAL(clicked()),parent,SLOT(save()));
//    connect(this,SIGNAL(sendPrtSc(QPixmap&)),parent,SLOT(save(QPixmap&)));
    QLabel* ysi=new QLabel("Your score is:");
    ysi->setMaximumHeight(parent->height()/12);
    scr=new QLabel();
    scr->setMaximumHeight(parent->height()/12);
    QFont font("Helvetica",12,QFont::DemiBold);
    ysi->setFont(font);
    scr->setFont(font);
    QVBoxLayout* layout=new QVBoxLayout();
    layout->addWidget(ysi,Qt::AlignHCenter);
    layout->addWidget(scr,Qt::AlignHCenter);
    layout->addSpacing(parent->height()*0.02);
//    layout->addLayout(traj)
//    QHBoxLayout* gifs=new QHBoxLayout();
//    pl=new QLabel;
//    platon=new QMovie();
//    ri=new QLabel;
//    rita=new QMovie();
//    platon->setScaledSize(QSize(250,250));
//    pl->setMovie(platon);
//    platon->start();
//    pl->setMinimumHeight(250);
//    pl->setMaximumWidth(250);
//    rita->setScaledSize(QSize(250,250));
//    ri->setMovie(rita);
//    rita->start();
//    ri->setMinimumHeight(250);
//    ri->setMaximumWidth(250);
//    layout->addSpacing(parent->height()*0.02);
//    gifs->addWidget(pl);
//    gifs->setSpacing(40);
//    gifs->addWidget(ri);
//    layout->addLayout(gifs);
//    layout->addSpacing(parent->height()*0.50);
    layout->addLayout(btns);
//    layout->setObjectName("l");

//    font.setFamily();
//    setFocus();
    connect(this,SIGNAL(setActive(int)),parent->parent(),SLOT(setCurrentIndex(int)));
    this->setStyleSheet("QPushButton { background-color : #FAE3D9;"
                                      "border: 2px solid #2B2E4A;"
                                      "border-radius: 8px;"
                                      "font-size: 16px;}"
                        "QPushButton:hover {background-color : #FFB6B9;"
                                           "color : rgb(255,255,255);}"
                        "QLabel {color: #2B2E4A;}"
//                                 "font: bold 24px;}"
                        /*"QWidget {  border: 4px solid rgba(0,0,0,255);"
                                   "border-radius: 10px;}"*/
                        );
    connect(restart,SIGNAL(clicked()),parent,SLOT(restart()));
    connect(menu,SIGNAL(clicked()),parent,SLOT(send()));// задаем расположение всего, коннектим с соответсвующими слотами
    setLayout(layout);
}

void Restart::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    bg=bg.scaled(this->width(),this->height());
    paint.drawImage(0,0,bg);// рисуем фон
}

Restart::~Restart()
{
//    delete pl;
//    delete ri;
}

void Restart::goMenu()
{
    setActive(0);
    this->close();
}

void Restart::goRestart()
{
//    setActive(1);
    this->close();
}

void Restart::goSave()
{
//    pix=new QPixmap();
//    *pix=this->grab(QRect(0,75,width(),height()-145));
////    QPixmap pix;
//    emit sendPrtSc(*pix);
    //    delete pix;
}

void Restart::getScore(double s)
{
    scr->setText(QString::number(s));// получили результат от лазера - вывели на экран
}


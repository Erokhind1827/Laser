#include "application.h"
#include "ui_application.h"

application::application(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::application)
{
    mWidget=new QStackedWidget(this);// стэкд виджет можно воспринимать как стопку листов, в которой можно менять верхний лист, а один лист - это виджет
    Menu=new menu(mWidget);
    Laser=new laser(mWidget);
    mWidget->addWidget(Menu);
    mWidget->addWidget(Laser);// добавляем в нашу стопку виджеты меню и лазера
    mWidget->setCurrentWidget(Menu);// делаем "обложкой" виджет меню
    this->setCentralWidget(mWidget);// устанавливаем нашу стопку виджетов в приложение
    menuBar1=new QMenuBar();
    pmnu = new QMenu("Menu");
    pmnu->addAction("&Menu", this, SLOT(goMenu()));
    menuActive=true;
    pmnu->addAction("&Quit",this, SLOT(close()));
    menuBar1->addMenu(pmnu);
    this->setMenuBar(menuBar1);// кнопочка menu сверху, когда появляется лазер
    menuBar1->setVisible(false);// делаем невидимым в основном меню
    connect(this,SIGNAL(transferForvard(int,int,int,int,QString,QString)),Laser,SLOT(setP(int,int,int,int,QString,QString)));
    connect(this,SIGNAL(sendScore(double)),Menu,SLOT(getScore(double)));
    this->setStyleSheet("QMenuBar {"
//                        "color: white;"
                        "font: bold 16px;}");// дизайним кнопочку menu
    this->setMinimumSize(1400,800);
//    ui->setupUi(this);
}

application::~application()
{
    delete ui;
}

void application::transfer(int r, int g, int b, int a, QString l,QString u)
{
    Username=u;
    mWidget->removeWidget(Laser);
    delete Laser;
    Laser=new laser(mWidget);// удаляем и создаем новый лазер при получении новых данных из меню
    mWidget->addWidget(Laser);
    menuBar1->setVisible(true);// делаем кнопочку menu видимой
    connect(this,SIGNAL(transferForvard(int,int,int,int,QString,QString)),Laser,SLOT(setP(int,int,int,int,QString,QString)));
    emit transferForvard(r,g,b,a,l,u);// заного коннектим и отправляем данные
}

void application::getScore(double s)
{
    emit sendScore(s);// получили результат от лазера - сразу переправили в меню
    if(menuActive){
        menuBar1->setVisible(false);// скрыли кнопочку menu
    }
    update();
}

void application::goMenu()
{
    mWidget->setCurrentIndex(0);// сделали наше основное меню обложкой стопки
    if(menuActive){
        menuBar1->setVisible(false);// скрыли кнопочку menu
    }
    update();
}


#include "menu.h"
#include "ui_menu.h"

menu::menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
{
    bg=QImage("menubg");
    QHBoxLayout* layout=new QHBoxLayout;
    layout->addSpacing(200);
    QVBoxLayout* columns=new QVBoxLayout[3];
    QGroupBox* gbx= new QGroupBox("Уровень");
    easy = new QRadioButton("Легкий");
    hard = new QRadioButton("Тяжелый");
//    mars = new QRadioButton("Mars");
    connect(easy, SIGNAL(toggled(bool)),this,SLOT(pressEasy(bool)));
    connect(hard, SIGNAL(toggled(bool)),this,SLOT(pressHard(bool)));
//    connect(mars, SIGNAL(toggled(bool)),this,SLOT(pressMars(bool)));
    easy->setChecked(true);
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(easy);
    pvbxLayout->addWidget(hard);
//    pvbxLayout->addWidget(mars);
    gbx->setLayout(pvbxLayout);
    gbx->setMinimumHeight(this->height()/3);
    QSlider* R = new QSlider(Qt::Vertical);
    QLabel* RValue = new QLabel("154");
    R->setRange(0, 255);
    R->setSingleStep(5);
    R->setValue(154);
//    mass->setTickInterval(30);
//    mass->setTickPosition(QSlider::TicksLeft);
    connect(R, SIGNAL(valueChanged(int)),RValue, SLOT(setNum(int)));
    connect(R, SIGNAL(valueChanged(int)),this, SLOT(rChanged(int)));
    QVBoxLayout* slider=new QVBoxLayout();
    QLabel* lr=new QLabel("R");
    slider->addWidget(lr);
    slider->addWidget(R);
//    columns[0].addWidget(lm,1,Qt::Alignment(Qt::AlignHCenter));
//    columns[0].addLayout(slider,1);
    QSlider* G = new QSlider(Qt::Vertical);
    QLabel* GValue = new QLabel("205");
    G->setRange(0, 255);
    G->setSingleStep(5);
    G->setValue(205);
//    mass->setTickInterval(30);
//    mass->setTickPosition(QSlider::TicksLeft);
    connect(G, SIGNAL(valueChanged(int)),GValue, SLOT(setNum(int)));
    connect(G, SIGNAL(valueChanged(int)),this, SLOT(gChanged(int)));
    QVBoxLayout* slider1=new QVBoxLayout();
    QLabel* lg=new QLabel("G");
    slider1->addWidget(lg);
    slider1->addWidget(G);
    QSlider* B = new QSlider(Qt::Vertical);
    QLabel* BValue = new QLabel("50");
    B->setRange(0, 255);
    B->setSingleStep(5);
    B->setValue(50);
    R->setMinimumHeight(50);
    G->setMinimumHeight(50);
    B->setMinimumHeight(50);
//    mass->setTickInterval(30);
//    mass->setTickPosition(QSlider::TicksLeft);
    connect(B, SIGNAL(valueChanged(int)),BValue, SLOT(setNum(int)));
    connect(B, SIGNAL(valueChanged(int)),this, SLOT(bChanged(int)));
    QVBoxLayout* slider2=new QVBoxLayout();
    QLabel* lb=new QLabel("B");
    slider2->addWidget(lb);
    slider2->addWidget(B);
    QHBoxLayout* sliders=new QHBoxLayout;
    sliders->addLayout(slider);
    sliders->addWidget(RValue);
    sliders->addLayout(slider1);
    sliders->addWidget(GValue);
    sliders->addLayout(slider2);
    sliders->addWidget(BValue);
    QSlider* Amount = new QSlider(Qt::Horizontal);
    QLabel* AValue = new QLabel("5");
    Amount->setRange(1, 10);
    Amount->setSingleStep(1);
    Amount->setValue(5);
    Amount->setTickInterval(2);
    Amount->setTickPosition(QSlider::TicksBelow);
    connect(Amount, SIGNAL(valueChanged(int)),AValue, SLOT(setNum(int)));
    connect(Amount, SIGNAL(valueChanged(int)),this, SLOT(aChanged(int)));
    QHBoxLayout* slider3=new QHBoxLayout();
    QLabel* la=new QLabel("Количество Зеркал");
//    AValue->setObjectName("l");
    la->setObjectName("l");

//    la->setObjectName("l");
    slider3->addWidget(Amount);
    slider3->addWidget(AValue);
    columns[0].addSpacing(200);

//    columns[0].addWidget(lg,1,Qt::Alignment(Qt::AlignHCenter));
//    columns[0].addLayout(slider1,1);
    columns[0].addSpacing(25);
    QLabel* color=new QLabel("Цвет Лазера:");
    color->setObjectName("l");
    columns[0].addWidget(color);
    columns[0].addLayout(sliders,3);
    columns[0].addSpacing(25);
    columns[0].addWidget(gbx,4);
    columns[0].addWidget(la,1,Qt::AlignHCenter);
    columns[0].addLayout(slider3,1);
    columns[0].addSpacing(200);

    QLabel* grandLabel=new QLabel("Лазер");
//    grandLabel->setObjectName("gL");
    QFont font("Comic Sans MS",36,QFont::Bold);
    grandLabel->setFont(font);
    grandLabel->setMaximumHeight(300);
    grandLabel->setObjectName("gL");
    QFont gbxfont("Comic Sans MS",16,QFont::Bold);
    gbx->setFont(gbxfont);
//    QPushButton* start=new QPushButton("Start");
//    QPushButton* exit=new QPushButton("Close");
    QPushButton* start=new QPushButton("Старт");
    start->setObjectName("b");
    start->setMaximumWidth(300);
    start->setMinimumWidth(300);
//    start->setMaximumHeight(300);
//    start->setMinimumHeight(300);
    start->setMinimumHeight(150);
    QPushButton* exit=new QPushButton("Закрыть");
    exit->setObjectName("b");
    exit->setMaximumWidth(300);
    exit->setMinimumWidth(300);
    exit->setMinimumHeight(150);
    QFont fontbtns("Comic Sans MS");
    fontbtns.setBold(true);
    start->setFont(fontbtns);
    exit->setFont(fontbtns);
    la->setFont(fontbtns);
    gbx->setFont(fontbtns);
    connect(exit, SIGNAL(clicked()),parent->parent(), SLOT(close()));
    connect(start,SIGNAL(clicked()),this,SLOT(start()));
//    columns[1].addSpacing(100);
    columns[1].addSpacing(200);
    columns[1].addWidget(grandLabel,2,Qt::Alignment(Qt::AlignHCenter));
    columns[1].addWidget(start,3,Qt::Alignment(Qt::AlignVCenter));
    columns[1].addWidget(exit,3,Qt::Alignment(Qt::AlignVCenter));
    columns[1].addSpacing(200);
//    columns[1].addSpacing(100);

    QLabel* user=new QLabel("Имя пользователя");
    user->setObjectName("l");
    user->setFont(fontbtns);
    usernm=new QLineEdit;
//    usernm->setMaximumWidth(380);
//    QLabel* records=new QLabel("Leaderboard");
//    leaderboard=new QTableWidget(5,2);
//    leaderboard->horizontalHeader()->setVisible(false);
//    leaderboard->verticalHeader()->setVisible(false);
//    leaderboard->setMinimumHeight(188);
//    leaderboard->setMaximumHeight(188);
//    leaderboard->setMinimumWidth(254);
//    leaderboard->setMaximumWidth(254);
    QLabel* records=new QLabel("Таблица лидеров");
    records->setFont(fontbtns);
    color->setFont(fontbtns);
    RValue->setFont(fontbtns);
    GValue->setFont(fontbtns);
    BValue->setFont(fontbtns);
    lr->setFont(fontbtns);
    lg->setFont(fontbtns);
    lb->setFont(fontbtns);
    AValue->setFont(fontbtns);
    records->setObjectName("l");
    leaderboard=new QTableWidget(5,3);
    for(int i=0;i<5;i++){
        QTableWidgetItem* el=new QTableWidgetItem("");
        leaderboard->setItem(i,0,el);
        QTableWidgetItem* pl=new QTableWidgetItem("");
        leaderboard->setItem(i,1,pl);
        QTableWidgetItem* el1=new QTableWidgetItem("");
        leaderboard->setItem(i,2,el1);
    }
    leaderboard->horizontalHeader()->setVisible(false);
    leaderboard->verticalHeader()->setVisible(false);
    leaderboard->setMinimumHeight(190);
    leaderboard->setMaximumHeight(190);
    leaderboard->setMinimumWidth(380);
    leaderboard->setMaximumWidth(380);
    columns[2].addSpacing(200);
    columns[2].addWidget(user,1,Qt::Alignment(Qt::AlignCenter));
    columns[2].addWidget(usernm,1,Qt::Alignment(Qt::AlignVCenter));
    columns[2].addWidget(records,1,Qt::Alignment(Qt::AlignCenter));
    columns[2].addWidget(leaderboard,6,Qt::Alignment(Qt::AlignJustify));
    columns[2].addSpacing(200);
    layout->addLayout(&columns[2],1);
    layout->addSpacing(this->width()/6);
    layout->addLayout(&columns[1],1);
    layout->addSpacing(this->width()/6);
    layout->addLayout(&columns[0],1);
    layout->addSpacing(200);
    QVBoxLayout* bigLayout=new QVBoxLayout;
//    bigLayout->addSpacing(this->height()/6);
    bigLayout->addLayout(layout);
//    bigLayout->addSpacing(this->height()/6);
    this->setStyleSheet("QPushButton#b { background-color : #FAE3D9;"
                                      "border: 4px solid #2B2E4A;"
                                      "border-radius: 36px;"
                                      "font-size: 30px;}"
                        "QPushButton#b:hover {background-color : #FFB6B9;"
                                           "color : rgb(255,255,255);}"
                        "QSlider::groove:horizontal {border: 1px solid #2B2E4A;"
                                                    "height: 8px;" /* по умолчанию бороздка расширяется до размеров ползунка. задав высоту она принимает фиксированный размер */
                                                    "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FAE3D9, stop:1 #FFB6B9);"
                                                    "margin: 2px 0;}"
                        "QSlider::handle:horizontal {background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #2B2E4A, stop:1 #E23E57);"
                                                    "border: 1px solid #2B2E4A;"
                                                    "width: 18px;"
                                                    "margin: -2px 0;" /* рукоятка располагается по умолчанию в прямоугольнике содержимого бороздки. Расширяется наружу от бороздки */
                                                    "border-radius: 3px;}"
                        "QSlider::groove:vertical {border: 1px solid #2B2E4A;"
                                                    "width: 8px;" /* по умолчанию бороздка расширяется до размеров ползунка. задав высоту она принимает фиксированный размер */
                                                    "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #FAE3D9, stop:1 #FFB6B9);"
                                                    "margin: 2px 0;}"
                        "QSlider::handle:vertical {background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #2B2E4A, stop:1 #E23E57);"
                                                    "border: 1px solid #2B2E4A;"
                                                    "height: 18px;"
                                                    "width: 8px;"
                                                    "margin: -2px 0;" /* рукоятка располагается по умолчанию в прямоугольнике содержимого бороздки. Расширяется наружу от бороздки */
                                                    "border-radius: 3px;}"
                        "QLineEdit {border: 2px solid #2B2E4A;"
                                   "border-radius: 5px;"
                                   "font: bold 16px;"
                                   "padding: 0 8px;"
                                   "background: #FAE3D9;"
                                   "selection-background-color: #2B2E4A;}"
                        "QTableView {color: #364F6B;"
                                 "background-color: #FAE3D9;" /* background color in the table*/
//                                 "alternate-background-color: #71C9CE;"
//                                 "selection-color: solid #364F6B;" /* The text color of the selected area*/
//                                 "selection-background-color: solid #11999E);" /*The background color of the selected area*/
                                 "font: bold 16px;"
                                 "border: 2px solid #2B2E4A;"
                                 "border-radius: 5px;}"
                        "QLabel#l {color: #2B2E4A;"
                                 "font: bold 24px;}"
                        "QLabel#gL {color: #2B2E4A;}"
                        "QGroupBox {background-color: #FAE3D9;"/*qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #FAE3D9, stop: 1 #FFB6B9)*/
                            "border: 4px solid #2B2E4A;"
                            "border-radius: 36px;"
                           " margin-top: 1ex;" /* оставляем пространство вверху для заголовка */
                        "}"

                        "QGroupBox::title {subcontrol-origin: margin;"
                            "subcontrol-position: top center;" /* помещаем вверху по центру */
                            "padding: 0 3px;"
                            "font: bold 24px;"
                            "border-radius: 2px;"
                            "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #FAE3D9, stop: 1 #FFB6B9);"
                        "}"
                        "QRadioButton {"
//                            "background-color:       gray;"
                            "font: 16px;"
                            "color:                  black;"
                        "}"

                        "QRadioButton::indicator {"
                            "width:                  12px;"
                            "height:                 12px;"
                            "border-radius:          7px;"
                        "}"

                        "QRadioButton::indicator:checked {"
                            "background-color:       #E23E57;"
                            "border:                 2px solid black;"
                        "}"

                        "QRadioButton::indicator:unchecked {"
                            "background-color:       #2B2E4A;"
                            "border:                 2px solid black;"
                        "}"

                        );// длинная компановка виджета меню
    connect(this,SIGNAL(transferP(int,int,int,int,QString,QString)),parent->parent(),SLOT(transfer(int,int,int,int,QString,QString)));
    this->setLayout(bigLayout);
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::pressEasy(bool b)
{
    if(b){
        level="easy";
//        planet="earth";
//        g=9.82;
    }
}

void menu::pressHard(bool b)
{
    if(b){
        level="hard";
//        planet="Moon";
//        g=1.62;
    }
}

void menu::paintEvent(QPaintEvent*)
{
    QPainter paint(this);
    bg=bg.scaled(this->width(),this->height());//рисуем фон
    paint.drawImage(0,0,bg);
    QPen pen1;
    pen1.setColor(Qt::white);
    pen1.setWidth(3);
    paint.setPen(pen1);
    paint.setBrush(QColor(r,g,b));
    paint.drawEllipse(this->width()*4/6+50,this->height()/6+73,30,30);// рисуем кружочек с цветом лазера
    update();
}

void menu::rChanged(int red)
{
    r=red;
}

void menu::gChanged(int green)
{
    g=green;
}

void menu::bChanged(int blue)
{
    b=blue;
}

void menu::aChanged(int a)
{
    amount=a;
}
//void menu::pressMars(bool b)
//{
//    if(b){
//        planet="Mars";
//        g=3.71;
//    }
//}

void menu::start()
{
    username=usernm->text();
    if(username=="")
        username="NoName";// считываем имя пользователя или если его нет даем свое
//    if(amount!=5){
//        QTableWidgetItem* it=new QTableWidgetItem(username);
//        QTableWidgetItem* v=new QTableWidgetItem(QString::number(amount+1));
//        leaderboard->setItem(amount,0,it);
//        leaderboard->setItem(amount,1,v);
//        amount++;
//    }
    emit transferP(r,g,b,amount,level,username);// передаем данные лазеру
}

void menu::getScore(double score)
{
    for(int i=0;i<5;i++){
        QString result=leaderboard->item(i,2)->text();
        double s;
        if (result=="")
            s=-1;
        else
            s=result.toDouble();
        if(score>s&&i==4){
            QTableWidgetItem* el=new QTableWidgetItem(username);
            leaderboard->setItem(i,0,el);
            QTableWidgetItem* lvl=new QTableWidgetItem(level);
            leaderboard->setItem(i,1,lvl);
            QTableWidgetItem* el1=new QTableWidgetItem(QString::number(score));
            leaderboard->setItem(i,2,el1);
        }
        else if(score>s){
            for(int j=3;j>=i;j--){
                QTableWidgetItem* el=new QTableWidgetItem(*leaderboard->item(j,0));
                leaderboard->setItem(j+1,0,el);
                QTableWidgetItem* lvl=new QTableWidgetItem(*leaderboard->item(j,1));
                leaderboard->setItem(j+1,1,lvl);
                QTableWidgetItem* el1=new QTableWidgetItem(*leaderboard->item(j,2));
                leaderboard->setItem(j+1,2,el1);
            }
            QTableWidgetItem* el=new QTableWidgetItem(username);
            leaderboard->setItem(i,0,el);
            QTableWidgetItem* lvl=new QTableWidgetItem(level);
            leaderboard->setItem(i,1,lvl);
            QTableWidgetItem* el1=new QTableWidgetItem(QString::number(score));
            leaderboard->setItem(i,2,el1);
            break;
        }
    }
    // когда получили результат полета лазера, заносим его в таблицу в нужное место

}


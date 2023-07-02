#include "laser.h"
#include "ui_laser.h"

laser::laser(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::laser)
{
    timer = new QTimer(this);
    timer->setInterval(1);
    connect(timer,SIGNAL (timeout()),this, SLOT(OnTimer()));
    rgb=new int[3];
    rgb[0]=154;
    rgb[1]=205;
    rgb[2]=50;
    aim=QImage("aim");
    connect(this,SIGNAL(sendFinalScore(double)),parent->parent(),SLOT(getScore(double)));
    connect(this,SIGNAL(setActiveWidget(int)),parent,SLOT(setCurrentIndex(int)));
    h=this->height();
    w=this->width();
    ui->setupUi(this);
}

laser::~laser()
{
    delete ui;
}

void laser::paintEvent(QPaintEvent *)
{
    update();
    QPainter paint(this);
    paint.setBrush(QColor(254, 237, 227));
    paint.drawRect(0,0,width(),this->height());
    paint.setBrush(QColor(255, 182, 185));
    paint.drawRect(this->width()-200,0,200,this->height());
    paint.setBrush(QBrush(QColor(226, 62, 87),Qt::Dense5Pattern));
    paint.drawRect(this->width()-200,0,200,this->height());
    drawBorders(paint);
    if(!ready){
        QFont font("Verdana",16,QFont::Bold);
        paint.setFont(font);
//        paint.setPen(Qt::black);
//        paint.drawText(this->width()/4+3,100+3,width()/2,30,Qt::AlignLeft,"Нажмите ЛКМ, чтобы расставить зеркала");
//        paint.drawText(this->width()/4+3,160+3,width()/2,30,Qt::AlignLeft,"Нажмите BACKSPACE, чтобы начать расстановку зеркал заново");
//        paint.drawText(this->width()/4+3,220+3,width()/2,30,Qt::AlignLeft,"Нажмите ENTER, чтобы запускать лазер");
        paint.setPen(QColor(226, 62, 87));
        paint.drawText(this->width()/8,100,width()/2,30,Qt::AlignLeft,"Нажмите ЛКМ, чтобы расставить зеркала");
        paint.drawText(this->width()/8,160,width()*2/3,30,Qt::AlignLeft,"Нажмите BACKSPACE, чтобы начать расстановку зеркал заново");
        paint.drawText(this->width()/8,220,width()/2,30,Qt::AlignLeft,"Нажмите ENTER, чтобы запускать лазер");
    }
    if(hasMouseTracking()){
        QPen pen1;
        pen1.setColor(QColor(90,90,90,128));
        pen1.setWidth(3);
        paint.setPen(pen1);
        paint.drawLine(bstart.first,bstart.second,bend.first,bend.second);// если мы рисуем зеркало, то проводить серую линию
    }
    drawLines(paint);
    if(ready){
        drawLaser(paint);
        drawAim(paint);// если все зеркала расставлены, то рисовать мишень и фонарик
    }
    draw(paint);
//    if(lines.length()==10){
//        timer->stop();
//        xcord=ycord=x=y=0;
//    }

}

void laser::mouseReleaseEvent(QMouseEvent *pe)//отпустили мышку
{
    if(ready){//если всё расставлено и лазер "готов"
        reflected=true;
        double x1=pe->x();
        double y1=pe->y();// считали координаты отпуска
        double r=hypot((x1-xcord),(y1-ycord));//нашли расстояние между точкой нажатия и отпуска кнопки
        if(r!=0){
            dy=-(y1-ycord)/r;
            dx=-(x1-xcord)/r;
            vector.first=dx;
            vector.second=dy;// записываем смещение в вектор, который задает рисование лазера
            for(int i=0;i<borders.length();i++){
                intersected.push_back(intersect(borders.at(i),i));// записываем в массив булевских переменных, пересекается ли луч с нашими зеркалами
            }
            timer->start();// начинаем рисование
        }
    }
    else{//еси еще нет
        double x1=pe->x();
        double y1=pe->y();//считываем координаты отпуска, также считываем количество нажатий
        if(x1<this->width()-200){
            bend.first=x1;
            bend.second=y1;//записываем пару координат конца векторов
            if(clicks%2==0){// если нажатий было четное кол-во

                bstart.first=x1;
                bstart.second=y1;
                setMouseTracking(true);//записываем пару координат начала векторов, включаем слежение за перемещением мыши, чтобы рисовать серую полоску (в программе видно)
            }
            else{// если нажатий было нечетное кол-во
                setMouseTracking(false);//отключаем слежение за перемещением мыши
                QPair<QPair<double,double>,QPair<double,double>> p(bstart,bend);
                borders.append(p);//добавляем зеркало в вектор зеркал
            }
            clicks++;
            if(clicks==2*maxRefl){
                ready=true;//если количество зеркал равно выбранному в меню
                xintrs=new double[borders.length()];
                yintrs=new double[borders.length()];// выделяем память под массив точек пересечения
            }
        }
    }
}

void laser::mouseMoveEvent(QMouseEvent *pe)
{
    bend.first=pe->x();
    bend.second=pe->y();//для рисования серой линии
    if(ready){
        double x1=pe->x();
        double y1=pe->y();
        double r=hypot((x1-xcord),(y1-ycord));
        dy=-(y1-ycord)/r;
        dx=-(x1-xcord)/r;// для рисования фонарика
    }
}

void laser::mousePressEvent(QMouseEvent *pe)
{
    yAim=this->height()/2;
    if(ready){
        if(timer->isActive()){
            timer->stop();
        }
        yAim=this->height()/2;
        borderAmount=0;
        intersected.clear();
        lines.clear();
        xcord=ycord=x=y=dx=dy=0;

        xcord=pe->x();
        ycord=pe->y();// если готовы, то каждое нажатие заново запускает лазер
        x=xcord;
        y=ycord;
        xstart=xcord;
        ystart=ycord;
    }
}

void laser::resizeEvent(QResizeEvent *re)
{
    h=re->size().height();
    w=re->size().width();
}

void laser::keyPressEvent(QKeyEvent *ke)
{
    if(ke->key()==Qt::Key_Return&&!ready){
        xintrs=new double[borders.length()];
        yintrs=new double[borders.length()];
        clicks=0;
        ready=true;// если нажали энтер, то готовы пускать лазер
        setMouseTracking(false);
    }
    if(ke->key()==Qt::Key_Backspace&&ready){
        ready=false;
        xcord=ycord=x=y=dx=dy=vector.first=vector.second=
                score=clicks=0;
        if(!intersected.empty())
            intersected.clear();
        if(!borders.empty())
            borders.clear();
        if(!lines.empty())
            lines.clear();
        if(timer->isActive())
            timer->stop();
        borderAmount=0;// нажали бэкспейс - все стерли
    }
    if(ke->key()==Qt::Key_W&&!ready){
        borders[borders.length()-1].first.second-=5;
        borders[borders.length()-1].second.second-=5;
    }
    if(ke->key()==Qt::Key_S&&!ready){
        borders[borders.length()-1].first.second+=5;
        borders[borders.length()-1].second.second+=5;
    }
    if(ke->key()==Qt::Key_A&&!ready){
        borders[borders.length()-1].first.first-=5;
        borders[borders.length()-1].second.first-=5;
    }
    if(ke->key()==Qt::Key_D&&!ready){
        borders[borders.length()-1].first.first+=5;
        borders[borders.length()-1].second.first+=5;// четыре клавиши для сдвигания последнего нарисованного зеркала
    }
}

void laser::draw(QPainter& paint)
{
    paint.setBrush(QBrush(QColor(Qt::red)));
    QPen pen1;
    pen1.setWidth(lWidth);
    pen1.setColor(QColor(rgb[0],rgb[1],rgb[2]));
    paint.setPen(pen1);
    paint.drawLine(xcord,ycord,x,y);// рисуем лазер от х(у)корд до х(у), х и y меняются в ontimer

}

void laser::drawBorders(QPainter &paint)
{
    QPen pen1;
    pen1.setWidth(5);
    pen1.setColor(QColor(110,212,255));
    paint.setPen(pen1);
    for(int i=0;i<borders.length();i++){
        paint.drawLine(borders.at(i).first.first,borders.at(i).first.second,borders.at(i).second.first,borders.at(i).second.second);// рисует все зеркала
    }
}

void laser::drawLines(QPainter &paint)
{
    QPen pen1;
    pen1.setWidth(lWidth);
    pen1.setColor(QColor(rgb[0],rgb[1],rgb[2]));
    paint.setPen(pen1);
    for(int i=0;i<lines.length();i++){
        paint.drawLine(lines.at(i).first.first,lines.at(i).first.second,lines.at(i).second.first,lines.at(i).second.second);
    }
}

void laser::drawLaser(QPainter &paint)
{
    QPen pen1;
    pen1.setWidth(6);
    pen1.setColor(Qt::black);
    paint.setPen(pen1);
    paint.drawLine(xstart,ystart,xstart-50*dx,ystart-50*dy);
    paint.setBrush(Qt::red);
    paint.setPen(Qt::NoPen);
    paint.drawEllipse(xstart-40*dx-2,ystart-40*dy-2,4,4);
}

void laser::drawAim(QPainter &paint)
{
    if(level=="easy"){
        aimSize=this->height();
        aim=aim.scaled(100,aimSize);

        paint.drawImage(this->width()-150,0,aim);// если легкий уровень, то во весь экран
    }
    else{
        aimSize=this->height()/3;
        aim=aim.scaled(100,aimSize);
        paint.drawImage(this->width()-150,yAim-aimSize/2,aim);// если сложный - рисует маленькую мишень, которая перемещается в зависимости от времени (см ontimer)
    }
}

bool laser::intersect(QPair<QPair<double, double>, QPair<double, double>> p,int i)// пересекается ли луч лазера с и-тым зеркалом
{
    double dely1=p.second.second-p.first.second;
    double delx1=p.second.first-p.first.first;// нашли две координаты, задающие вектор зеркала
    double k1=dely1/delx1,b1=(p.first.second*delx1-p.first.first*dely1)/delx1;// выразили коэффициенты k,b для прямой, на которой лежит зеркало
    double k2=vector.second/vector.first,b2=(ycord*vector.first-xcord*vector.second)/vector.first;// выразили коэффициенты k,b для прямой, на которой лежит луч лазера
    if(k2==INFINITY||k2==-INFINITY){
        xintrs[i]=xcord;
        yintrs[i]=k1*xintrs[i]+b1;
    }
    else if(k1==INFINITY||k1==-INFINITY){
        xintrs[i]=p.second.first;
        yintrs[i]=k2*xintrs[i]+b2;
        delx1=xintrs[i];
    }
    else{
        xintrs[i]=(b2-b1)/(k1-k2);
        yintrs[i]=(k1*b2-k2*b1)/(k1-k2);
    }
    if(dely1==0)
        dely1=yintrs[i];
    if(abs(xintrs[i]-p.first.first)<abs(delx1)&&abs(xintrs[i]-p.second.first)<abs(delx1)
           &&abs(yintrs[i]-p.first.second)<abs(dely1)&&abs(yintrs[i]-p.second.second)<abs(dely1))
        return true;
    else{
        xintrs[i]=0;
        yintrs[i]=0;
        return false;
    }
}

void laser::changeDirection(int i)//смена направления
{
        QPair<double,double> n(0,0);
        double dely1=borders.at(i).second.second-borders.at(i).first.second;
        double delx1=borders.at(i).second.first-borders.at(i).first.first;
        n.first=-dely1/hypot(dely1,delx1);
        n.second=delx1/hypot(dely1,delx1);
        double sc=vector.first*n.first+vector.second*n.second;
//        if(abs(sc)<1.02||abs(sc)>0.98){
//            vector.first=-vector.first;
//            vector.second=-vector.second;
//        }
//        else{
        vector.first=vector.first-2*(sc)*n.first;
        vector.second=vector.second-2*(sc)*n.second;// нашли отраженный вектор(см сообщение 2)
//        }
        lines.push_back(QPair<QPair<double,double>,QPair<double,double>>
                        (QPair<double,double>(xcord,ycord),QPair<double,double>(xintrs[i],yintrs[i])));// записали в вектор статичных элементов лазера наш последний луч, дошедший до зеркала
        xcord=xintrs[i];
        ycord=yintrs[i];//перезаписали начало рисования лазера на точку, которую мы рассчитали, как точку пересесчения с данным зеркалом ранее
        for(int j=0;j<borders.length();j++){

            if(j==i)
                intersected[j]=false;
            else{
                intersected[j]=intersect(borders.at(j),j);// заново просчитали пересечения со всеми зеркалами
            }
        }
//        intrs++;
}

void laser::OnTimer()
{
    for(int i=0;i<2;i++){
        x+=vector.first;
        y+=vector.second;// добавили к координатам конца вектора наш маленьки направляющий вектор лазера
    }
    if(level=="hard"){
        yAim+=da;
        if(yAim>this->height()*5/6)
            da=-0.5;
        if(yAim<this->height()/6)
            da=0.5;
    }// для движения мишени туда-сюда при сложном уровне
    if(ready){
        for(int i=0;i<borders.length();i++){
                if(intersected[i]&&abs(x-xintrs[i])<5&&abs(y-yintrs[i])<5){
                    changeDirection(i);// если мы пересекаемся с и-тым зеркалом, и подошли к точке пересечения на очень маленькое расстояние
                }
        }
    }
    if(x>this->width()-100){// если мы попали на ось расположения мишени => закончилось движение
        timer->stop();
        da=0.5;
        double temp=abs(y-yAim)/(aimSize/2);// нашли отношения расстояний от коорд у конца лазера до середины мишени к радиусу мишени
        if(temp>1)// если это отношение больше 1, то мы не попали в мишень
            score=0;// логично
        else
            score=std::min(10-10*temp+lines.length(),10.0);// учитываем это отношение и количество отражений лазера
    }
    else if(x<0||y<0||y>this->h){// если вылетели за область экрана
        timer->stop();
        score=0;
//        this->close();
    }
    if(!timer->isActive()){// если таймер выключен => лазер достиг цели
        res=this->grab(QRect(0,0,width(),height()));// делаем скриншот траектории
        r=new Restart(this);// создаем окно рестарта
        connect(this,SIGNAL(sendScore(double)),r,SLOT(getScore(double)));
        emit sendScore(score);//отправили результат в окно рестарта
        disconnect(this,SIGNAL(sendScore(double)),r,SLOT(getScore(double)));
//        r->setObjectName(QString("r"));
//        r->setStyleSheet("QWidget#Restart {border: 3px solid rgba(0,0,0,255);"
//                            "border-radius: 8px;}");

//        double v[8];
//        v[0]=score;
//        v[1]=v0;
//        v[2]=ang;
//        v[3]=idlVel;
//        v[4]=idlAng;
//        v[5]=aimCord+size*3;
//        v[6]=xFall+size/2;
//        v[7]=g;
//        connect(this,SIGNAL(sendInfo(double,double,double,double,double,double,double,double)),
//                r,SLOT(getInfo(double,double,double,double,double,double,double,double)));
//        QHBoxLayout* l=new QHBoxLayout();
//        l->setAlignment(Qt::AlignCenter);
//        l->addWidget(r);
//        this->setLayout(l);
//        emit sendInfo(score,v0,ang,idlVel,idlAng,aimCord+size*3,xFall+size/2,g);
//        disconnect(this,SIGNAL(sendInfo(double,double,double,double,double,double,double,double)),
//                   r,SLOT(getInfo(double,double,double,double,double,double,double,double)));
        r->setMaximumSize(this->width()/3,this->height()/4);
        r->setMinimumSize(this->width()/3,this->height()/4);
        r->move(w/3,h*3/8);
//        this->setDisabled(true);
//        r->setDisabled(false);
//        setAttribute(Qt::WA_TransparentForMouseEvents);
//        setAttribute(Qt::mouseevents);
//        ready=false;
        r->show();//настроили размер, показали на экране
    }
}

void laser::setP(int r, int g, int b, int a, QString l, QString u)
{
    rgb[0]=r;
    rgb[1]=g;
    rgb[2]=b;
    maxRefl=a;
    level=l;
    username=u;
    setActiveWidget(1);
}

void laser::restart()
{
//    ready=false;
    xcord=ycord=x=y=dx=dy=vector.first=vector.second=
            score=0;
    da=0.5;
//    clicks=2*maxRefl;
//    if(!intersected.empty())
//        intersected.clear();
//    if(!borders.empty())
//        borders.clear();
    if(!lines.empty())
        lines.clear();
    if(timer->isActive())
        timer->stop();
    setDisabled(false);
//    borderAmount=0;
}

void laser::save()
{
    QString fileName1 = QFileDialog::getSaveFileName(this,
    tr("Сохранить файл"), "",
    tr("PDF (*.pdf)"));
    res.save("res.jpg");
//    prtscr.save("prtscr.jpg");
    res.save(fileName1);
    if (fileName1 != ""){
          QString html ="<h1 align=left>""Level: "+level+"</h1>"
                  "<h2 align=center>"+"</h2>"
//                  "<br>""<br>"
                  "<h3 align=left>""User: "+username +"<br>""Glass amount: "+QString::number(borders.length()) +"<br>"""+"""</h3>"
//                  "<br>""<br>"
                  "<h2 align=left>""Results:""</h2>"
                  "<h3 align=left>"+QString::number(score)+"</h3>"
//                  "<br>""<br>"
                  "<h2 align=left>""Trajectory:""</h2>"
                  "<br>"
                  "<img src=\"res.jpg\" width=\"700\">";
//                  if (score<7){
//                      html+="<h2 align=left>""Ideal trajectories:""</h2>"
//                      "<br>"
//                      "<img src=\"prtscr.jpg\" width=\"500\">";
//                  }
          QTextDocument document;
          document.setHtml(html);
          QPrinter printer(QPrinter::PrinterResolution);
          printer.setOutputFormat(QPrinter::PdfFormat);
          printer.setPageSize(QPrinter::A4);
          printer.setOutputFileName(fileName1);
          printer.setPageMargins(QMarginsF(15, 15, 15, 15));
          document.print(&printer);// сохранение пдф файла после нажатия save в рестарте
    }
}

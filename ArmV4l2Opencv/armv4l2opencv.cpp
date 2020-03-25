#include "armv4l2opencv.h"
#include "ui_armv4l2opencv.h"


ArmV4l2Opencv::ArmV4l2Opencv(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArmV4l2Opencv)
{
    ui->setupUi(this);
    ui->LittleRobotLabel->hide();
    ui->pushButton->hide();

    //开机界面
    ui->StartLabel->setScaledContents(true);
    StartShow = new QMovie(":/resource/images/start.gif");
    ui->StartLabel->setMovie(StartShow);
    StartShow->start();
    StartTime = 0;

    //开机后的界面
    ui->CircleLabel->setScaledContents(true);
    CircleLabelShow = new QMovie(":/resource/images/circle.gif");
    ui->CircleLabel->setMovie(CircleLabelShow);
    CircleLabelShow->stop();
    ui->CircleLabel->hide();

    connect(&vapi, &V4l2Api::sendImage, this, &ArmV4l2Opencv::recvImage);
    //显示员工信息
    connect(&vapi, &V4l2Api::sendPersonInfo, this, &ArmV4l2Opencv::showPersonInfo);
    //显示时间
    connect(&mtimer,&QTimer::timeout,this,&ArmV4l2Opencv::time);
    mtimer.start(1000);//启动计时

    //创建管理员控制界面对象
    AdW = new AdministratorW(this);

    //创建员工信息数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    if(!db.open())
    {
       qDebug() << "open data.db error";
    }

    QSqlQuery query;
    //query.exec("create table info(id integer primary key autoincrement,imagePath text,name text)");
    query.exec("create table info(id integer ,imagePath text primary key,name text,state integer,uptime text,downtime text)");
    //db.close();
}

//显示时间
void ArmV4l2Opencv::time()
{
    QString t = QTime::currentTime().toString();
    ui->lcdNumber->display(t);

    QString d = QDate::currentDate().toString("yyyy-MM-dd");
    ui->DateLable->setText(d);

    ++StartTime;
    if(StartTime == 3)
    {
        StartShow->stop();
        ui->StartLabel->hide();

        ui->pushButton->show();
        ui->CircleLabel->show();
        CircleLabelShow->start();
    }

    ++InfoShowTimes;
    if(InfoShowTimes == 4)
    {
        ui->InfoLabel->clear();
        ui->LittleRobotLabel->hide();
    }
}

ArmV4l2Opencv::~ArmV4l2Opencv()
{
    delete ui;
}

void ArmV4l2Opencv::on_pushButton_clicked()
{
    vapi.start();
    ui->label->show();
    ui->pushButton->hide();
    CircleLabelShow->stop();
    ui->CircleLabel->hide();
}

//显示员工信息
void ArmV4l2Opencv::showPersonInfo(QString name,int id,int state)
{
    QString sql;
    QTime time;

    QString t = QTime::currentTime().toString();
    InfoShowTimes = 0;

    ui->LittleRobotLabel->show();

    QSqlQuery query;
    switch (state) {
    case 0:
        if(time.hour() < 12)
        {
            ui->InfoLabel->setText(QString("'%1' 早上好！上班打卡成功！").arg(name));
        }
        else if(12 < time.hour() < 14)
        {
            ui->InfoLabel->setText(QString("'%1' 中午好！上班打卡成功！").arg(name));
        }
        else if(14 < time.hour() < 19)
        {
            ui->InfoLabel->setText(QString("'%1' 下午好！上班打卡成功！").arg(name));
        }
        else
        {
            ui->InfoLabel->setText(QString("'%1' 晚上好！上班打卡成功！").arg(name));
        }

        //更新数据库上下班状态
        sql = QString("update info set state='%1' where id=%2;").arg(1).arg(id);
        query.exec(sql);
        //更新数据库上班时间
        sql = QString("update info set uptime='%1' where id=%2;").arg(t).arg(id);
        query.exec(sql);
        break;
    case 1:
        if(time.hour() < 12)
        {
            ui->InfoLabel->setText(QString("'%1' 早上好！下班打卡成功！").arg(name));
        }
        else if(12 < time.hour() < 14)
        {
            ui->InfoLabel->setText(QString("'%1' 中午好！下班打卡成功！").arg(name));
        }
        else if(14 < time.hour() < 19)
        {
            ui->InfoLabel->setText(QString("'%1' 下午好！下班打卡成功！").arg(name));
        }
        else
        {
            ui->InfoLabel->setText(QString("'%1' 晚上好！下班打卡成功！").arg(name));
        }

        //更新数据库上下班状态
        sql = QString("update info set state='%1' where id=%2;").arg(0).arg(id);
        query.exec(sql);
        //更新数据库下班时间
        sql = QString("update info set downtime='%1' where id=%2;").arg(t).arg(id);
        query.exec(sql);
    default:
        break;
    }

}

void ArmV4l2Opencv::recvImage(QImage image,QImage headImage)
{
    ui->label->setPixmap(QPixmap::fromImage(image));
    AdW->recvImage(image,headImage);
}


void ArmV4l2Opencv::on_systemLogBt_clicked()
{
    this->hide();
    AdW->show();
}

void ArmV4l2Opencv::on_pCardBt_clicked()
{
    vapi.PCard = true;
}

void ArmV4l2Opencv::on_shutdownButton_clicked()
{
    ui->label->hide();
    ui->pushButton->show();
    CircleLabelShow->start();
    ui->CircleLabel->show();
}

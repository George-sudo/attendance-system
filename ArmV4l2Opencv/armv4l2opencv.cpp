#include "armv4l2opencv.h"
#include "ui_armv4l2opencv.h"
#include <QPixmap>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QFileInfo>

ArmV4l2Opencv::ArmV4l2Opencv(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArmV4l2Opencv)
{
    ui->setupUi(this);
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
}

ArmV4l2Opencv::~ArmV4l2Opencv()
{
    delete ui;
}

void ArmV4l2Opencv::on_pushButton_clicked()
{
    vapi.start();
}

//显示员工信息
void ArmV4l2Opencv::showPersonInfo(QString name,int id,int state)
{
    ui->numLable->setText(QString::number(id));
    ui->nameLabel->setText(name);

    QString t = QTime::currentTime().toString();
    ui->timeLable->setText(t);

    QSqlQuery query;
    if(state == 0)
    {
        ui->stateLable->setText("上班打卡");
        //更新数据库上下班状态
        QString sql = QString("update info set state='%1' where id=%2;").arg(1).arg(id);
        query.exec(sql);
        //更新数据库上班时间
        sql = QString("update info set uptime='%1' where id=%2;").arg(t).arg(id);
        query.exec(sql);
    }
    if(state == 1)
    {
        ui->stateLable->setText("下班打卡");
        //更新数据库上下班状态
        QString sql = QString("update info set state='%1' where id=%2;").arg(0).arg(id);
        query.exec(sql);
        //更新数据库下班时间
        sql = QString("update info set downtime='%1' where id=%2;").arg(t).arg(id);
        query.exec(sql);
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

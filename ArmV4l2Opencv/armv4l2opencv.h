#ifndef ARMV4L2OPENCV_H
#define ARMV4L2OPENCV_H

#include "administratorw.h"

#include <QMainWindow>
#include <v4l2api.h>
#include <QImage>
#include <QTime>
#include <QTimer>
#include <QDate>

namespace Ui {
class ArmV4l2Opencv;
}

class ArmV4l2Opencv : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArmV4l2Opencv(QWidget *parent = nullptr);
    ~ArmV4l2Opencv();

    void showPersonInfo(QString name,int id,int state);
    void time();
private slots:
    void on_pushButton_clicked();
    void recvImage(QImage image,QImage headImage);

    void on_systemLogBt_clicked();

    void on_pCardBt_clicked();

private:
    Ui::ArmV4l2Opencv *ui;
    V4l2Api vapi;
    AdministratorW *AdW;
    QTimer mtimer;
};

#endif // ARMV4L2OPENCV_H

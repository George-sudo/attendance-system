#ifndef ADMINISTRATORW_H
#define ADMINISTRATORW_H

#include <QMainWindow>
#include <QDebug>
#include "v4l2api.h"
#include <QDir>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLineEdit>
#include <QApplication>
#include <QVBoxLayout>
#include "MyLineEdit/mylineedit.h"
#include "Keyboard/Keyboard.h"

namespace Ui {
class AdministratorW;
}

class AdministratorW : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorW(QWidget *parent = nullptr);
    ~AdministratorW();

    void recvImage(QImage image,QImage HImage);
    void getFaceDirinfo();
    void UpdateDatabase_imagePathId(QString dirPath);
    void WindowShow();

private slots:
    void on_retBt_clicked();

    void on_TakePhotoBt_clicked();

    void on_InIofoBt_clicked();

    void on_SureBt_clicked();

    void UserLineEditClicked();
    void PassLineEditClicked();

    void on_pushButton_clicked();

    void on_loginPushButton_clicked();

    void on_KeyboardReturnPushButton_clicked();

    void on_KeyboardSurePushButton_clicked();

private:
    Ui::AdministratorW *ui;
    QPixmap GImage;
    QImage headImage;
    //获取当前人脸数据目录下文件名称的最大值
    int DirFileNum;
    //记录人脸图片拍照的张数
    int FaceNum;
    //键盘
    AeaQt::Keyboard keyboard;
    QWidget KeyboardWindow;
    QLineEdit *textInput;
    QVBoxLayout *v;
    bool UserAndPassLineEditFlag;
    QString SavePass;
    QString Administratoruser;
    QString AdministratorPass;
};

#endif // ADMINISTRATORW_H

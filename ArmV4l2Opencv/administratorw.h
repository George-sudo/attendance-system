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
    void nameLEClicked();
    void NumLineEditClicked();

    void on_pushButton_clicked();

    void on_loginPushButton_clicked();

    void on_KeyboardReturnPushButton_clicked();

    void on_KeyboardSurePushButton_clicked();

    void on_NextBt_clicked();

    void on_NameBt_clicked();

    void on_ReturnAdMBt_clicked();

    void on_DelIofoBt_clicked();

    void on_DelNumSureBt_clicked();

    void on_ReturnDelBt_clicked();

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
    int KeyboardSureLineEditFlag;
    QString SavePass;
    int NextFlag;
    bool SureFlag;
};

#endif // ADMINISTRATORW_H

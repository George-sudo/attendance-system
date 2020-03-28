#include "administratorw.h"
#include "ui_administratorw.h"
#include "v4l2api.h"

using namespace std;
using namespace cv;
using namespace face;

AdministratorW::AdministratorW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorW)
{
    ui->setupUi(this);
    DirFileNum = 0;
    FaceNum = 1;

    connect(ui->UserLineEdit, SIGNAL(clicked()), this, SLOT(UserLineEditClicked()));
    connect(ui->PassLineEdit, SIGNAL(clicked()), this, SLOT(PassLineEditClicked()));

    //创建键盘
//    QWidget window;
    KeyboardWindow.setWindowTitle("QtKeyboard");
    KeyboardWindow.resize(800,420);
    //AeaQt::Keyboard keyboard;

    textInput = new QLineEdit(&keyboard);
    textInput->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    textInput->setStyleSheet(R"(
                            QLineEdit {
                                border-style: none;
                                padding: 3px;
                                border-radius: 5px;
                                border: 1px solid #dce5ec;
                                font-size: 30px;
                            }
                            )");

    v = new QVBoxLayout;
    v->addWidget(textInput, 1);
    v->addWidget(&keyboard, 5);

    KeyboardWindow.setLayout(v);
}

AdministratorW::~AdministratorW()
{
    delete ui;
}

void AdministratorW::on_retBt_clicked()
{
    this->parentWidget()->show();
    this->hide();
}

//拍照并且保存和显示
void AdministratorW::on_TakePhotoBt_clicked()
{
    if(headImage.width()==92 && headImage.height()==112)
    {
        QString path = QString("./faces/%1/%2.jpg").arg(DirFileNum+1).arg(FaceNum);
        headImage.save(path,"jpg",100);

        switch (FaceNum) {
        case 1:
            ui->ImageLb1->setPixmap(QPixmap::fromImage(headImage));
            break;
        case 2:
            ui->ImageLb2->setPixmap(QPixmap::fromImage(headImage));
            break;
        case 3:
            ui->ImageLb3->setPixmap(QPixmap::fromImage(headImage));
            break;
        case 4:
            ui->ImageLb4->setPixmap(QPixmap::fromImage(headImage));
            break;
        case 5:
            ui->ImageLb5->setPixmap(QPixmap::fromImage(headImage));
            break;
        case 6:
            ui->ImageLb6->setPixmap(QPixmap::fromImage(headImage));
            break;
        case 7:
            ui->ImageLb7->setPixmap(QPixmap::fromImage(headImage));
            break;
        case 8:
            ui->ImageLb8->setPixmap(QPixmap::fromImage(headImage));
            break;
        case 9:
            ui->ImageLb9->setPixmap(QPixmap::fromImage(headImage));
            break;
        case 10:
            ui->ImageLb10->setPixmap(QPixmap::fromImage(headImage));
            break;
        default:
            break;
        }
        ++FaceNum;

        if(FaceNum == 11)
        {
           FaceNum = 1;
           ui->messageLable_4->setText("该员工已拍照完成,请输入姓名...");
        }
    }
}

//接收摄像头发送过来的全身图片的脸部图像
void AdministratorW::recvImage(QImage image,QImage HImage)
{
    headImage = HImage;

    image.scaled(ui->CameraLB->width(),ui->CameraLB->height(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->CameraLB->setPixmap(QPixmap::fromImage(image));
}

//准备录入新员工信息
void AdministratorW::on_InIofoBt_clicked()
{
    ui->messageLable->setText("1、请对新员工拍10张头像");
    ui->messageLable_2->setText("2、输入姓名");
    ui->messageLable_3->setText("3、点击确认完成");

    getFaceDirinfo();
    char sys[512] = {0};
    sprintf(sys,"mkdir ./faces/%d -p",DirFileNum+1);
    system(sys);
}

//获取人脸图像目录信息
void AdministratorW::getFaceDirinfo()
{
    QDir DirFile("faces");
    foreach(QFileInfo FileOrDir,DirFile.entryInfoList())
    {
        if(FileOrDir.isDir())//判断是否为目录
        {
            QString DirName = FileOrDir.fileName();
            if(DirName[0] == '.')
            {
                continue;
            }

            if(DirFileNum < DirName.toInt())
            {
               DirFileNum = DirName.toInt();
            }

        }
    }
}

//确认新员工信息，并且录入更新数据库和训练分类器
void AdministratorW::on_SureBt_clicked()
{
    /**更新数据库**/
    UpdateDatabase_imagePathId("faces");

    QString name = ui->nameLE->text();
    QString sql = QString("update info set name='%1' where id=%2;").arg(name).arg(DirFileNum+1);
    qDebug()<<sql;
    QSqlQuery query;
    query.exec(sql);

    /**训练分类器**/
    //删除原来的分类器
    system("rm MyFacePCAModel.xml");
    vector<Mat> images;
    vector<int> labels;

    sql = QString("select imagePath from info");
    qDebug()<<sql;
    query.exec(sql);
    while(query.next())
    {
        //获取人脸图片路径
        string path = query.value(0).toString().toStdString();
        //以灰度方式读取图片数据，压栈到vector<Mat>容器中
        images.push_back(imread(path, 0));
    }

    sql = QString("select id from info");
    qDebug()<<sql;
    query.exec(sql);
    while(query.next())
    {
        int id = query.value(0).toInt();
        //将图片标签压栈到vector<int>容器中
        labels.push_back(id);
    }

    Ptr<FaceRecognizer> model = EigenFaceRecognizer::create();
    model->train(images, labels);
    model->save("MyFacePCAModel.xml");

    //更新人脸数据目录中文件的数目
    ++DirFileNum;

    ui->messageLable->setText(" ");
    ui->messageLable_2->setText(" ");
    ui->messageLable_3->setText(" ");
    ui->messageLable_4->setText("新员工信息存储完成");
}

void AdministratorW::UserLineEditClicked()
{
    UserAndPassLineEditFlag = true;

    keyboard.show();
    KeyboardWindow.show();
    ui->KeyboardReturnPushButton->show();
    ui->KeyboardSurePushButton->show();

    textInput->setText(ui->UserLineEdit->text());
}

void AdministratorW::PassLineEditClicked()
{
    UserAndPassLineEditFlag = false;
    keyboard.show();
    KeyboardWindow.show();
    ui->KeyboardReturnPushButton->show();
    ui->KeyboardSurePushButton->show();

    textInput->setText(ui->PassLineEdit->text());
}


//更新数据库中的图片路径和id,传入人脸数据目录和新人员的名字
void AdministratorW::UpdateDatabase_imagePathId(QString dirPath)
{
    QDir DirFile(dirPath);
    int id = 0;
    //在foreach函数循环获取文件的信息放到QFileInfo变量
    foreach(QFileInfo FileOrDir,DirFile.entryInfoList())
    {
        if(FileOrDir.isDir())//判断是否为目录
        {
            QString DirName = FileOrDir.fileName();
            if(DirName[0] == '.')
            {
                continue;
            }
            QString path = QString("%1/%2").arg(dirPath).arg(DirName);
            id = DirName.toInt();
            QDir ImageDir(path);

            foreach(QFileInfo Image,ImageDir.entryInfoList())
            {
                if(Image.isFile())//判断是否为文件
                {
                    QString ImagePath = QString("%1/%2").arg(path).arg(Image.fileName());

                    QString sql = QString("insert into info(id,imagePath,state) values(%1,'%2',%3)").arg(id).arg(ImagePath).arg(0);
                    qDebug()<<sql;
                    QSqlQuery query;
                    query.exec(sql);
                }
            }
        }
    }
}

void AdministratorW::WindowShow()
{
    if(ui->checkBox->checkState() == Qt::Checked)
        ui->PassLineEdit->setText(SavePass);
    else
        ui->PassLineEdit->clear();

    ui->LoginLabel->show();
    ui->loginPushButton->show();
    ui->pushButton->show();
    ui->UserLineEdit->show();
    ui->PassLineEdit->show();
    ui->checkBox->show();
    ui->KeyboardReturnPushButton->hide();
    ui->KeyboardSurePushButton->hide();
    ui->HintLabel->hide();
    this->show();
}

void AdministratorW::on_pushButton_clicked()
{
    this->parentWidget()->show();
    this->hide();

    if(ui->checkBox->checkState() == Qt::Checked)
        SavePass = textInput->text();
}

void AdministratorW::on_loginPushButton_clicked()
{
    QString sql;
    if(ui->checkBox->checkState() == Qt::Checked)
        SavePass = textInput->text();

    sql = QString("select pass from administrator where user='%1'").arg(ui->UserLineEdit->text());
    QSqlQuery query;
    query.exec(sql);

    if(query.first())
    {
        if(ui->PassLineEdit->text() == query.value(0).toString())
        {
            ui->LoginLabel->hide();
            ui->loginPushButton->hide();
            ui->pushButton->hide();
            ui->UserLineEdit->hide();
            ui->PassLineEdit->hide();
            ui->checkBox->hide();
            ui->HintLabel->hide();
        }
        else
        {
            ui->HintLabel->setText("密码输入错误！");
            ui->HintLabel->show();
        }
    }
    else
    {
        ui->HintLabel->setText("账号输入错误！");
        ui->HintLabel->show();
    }
}

void AdministratorW::on_KeyboardReturnPushButton_clicked()
{
    keyboard.hide();
    KeyboardWindow.hide();
    ui->KeyboardReturnPushButton->hide();
    ui->KeyboardSurePushButton->hide();
}

void AdministratorW::on_KeyboardSurePushButton_clicked()
{
    keyboard.hide();
    KeyboardWindow.hide();
    ui->KeyboardReturnPushButton->hide();
    ui->KeyboardSurePushButton->hide();

    if(UserAndPassLineEditFlag)
    {
        ui->UserLineEdit->setText(textInput->text());
    }
    else
    {
        ui->PassLineEdit->setText(textInput->text());
    }

}

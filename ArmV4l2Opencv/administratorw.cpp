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
    NextFlag = 0;
    SureFlag = false;

    connect(ui->UserLineEdit, SIGNAL(clicked()), this, SLOT(UserLineEditClicked()));
    connect(ui->PassLineEdit, SIGNAL(clicked()), this, SLOT(PassLineEditClicked()));
    connect(ui->nameLE, SIGNAL(clicked()), this, SLOT(nameLEClicked()));
    connect(ui->NumLineEdit, SIGNAL(clicked()), this, SLOT(NumLineEditClicked()));



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
           NextFlag = 1;
           ui->messageLable->setText("该员工已拍照完成,请点击下一步");
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
    NextFlag = 0;
    FaceNum = 1;
    SureFlag = false;
    ui->InIofoBt->hide();
    ui->NameBt->hide();
    ui->SureBt->hide();
    ui->NameaLabel->hide();
    ui->nameLE->hide();
    ui->NextBt->show();
    ui->TakePhotoBt->show();
    ui->ReturnAdMBt->show();
    ui->pushButton->hide();
    ui->retBt->hide();

    ui->messageLable->setText("请对新员工拍10张不同角度头像");
    ui->messageLable->show();
    ui->CameraLB->show();

    ui->ImageLb1->clear();
    ui->ImageLb2->clear();
    ui->ImageLb3->clear();
    ui->ImageLb4->clear();
    ui->ImageLb5->clear();
    ui->ImageLb6->clear();
    ui->ImageLb7->clear();
    ui->ImageLb8->clear();
    ui->ImageLb9->clear();
    ui->ImageLb10->clear();
    ui->ImageLb1->show();
    ui->ImageLb2->show();
    ui->ImageLb3->show();
    ui->ImageLb4->show();
    ui->ImageLb5->show();
    ui->ImageLb6->show();
    ui->ImageLb7->show();
    ui->ImageLb8->show();
    ui->ImageLb9->show();
    ui->ImageLb10->show();


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

    ui->messageLable->setText("新员工信息存储完成");
    SureFlag = true;
}

void AdministratorW::UserLineEditClicked()
{
    KeyboardSureLineEditFlag = 0;

    keyboard.show();
    KeyboardWindow.show();
    ui->KeyboardReturnPushButton->show();
    ui->KeyboardSurePushButton->show();

    textInput->setText(ui->UserLineEdit->text());
}

void AdministratorW::PassLineEditClicked()
{
    KeyboardSureLineEditFlag = 1;
    keyboard.show();
    KeyboardWindow.show();
    ui->KeyboardReturnPushButton->show();
    ui->KeyboardSurePushButton->show();

    textInput->setText(ui->PassLineEdit->text());
}

void AdministratorW::nameLEClicked()
{
    KeyboardSureLineEditFlag = 2;
    keyboard.show();
    KeyboardWindow.show();
    ui->KeyboardReturnPushButton->show();
    ui->KeyboardSurePushButton->show();

    textInput->setText(ui->nameLE->text());
}

void AdministratorW::NumLineEditClicked()
{
    KeyboardSureLineEditFlag = 3;
    keyboard.show();
    KeyboardWindow.show();
    ui->KeyboardReturnPushButton->show();
    ui->KeyboardSurePushButton->show();

    textInput->setText(ui->NumLineEdit->text());
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


    //隐藏删除员工界面
    ui->ReturnDelBt->hide();
    ui->DelNumLabel->hide();
    ui->TextLlabel->hide();
    ui->NumLineEdit->hide();
    ui->DelNumSureBt->hide();


    this->show();
}

void AdministratorW::on_pushButton_clicked()
{
    this->parentWidget()->show();
    this->hide();

    if(ui->checkBox->checkState() == Qt::Checked)
        SavePass = ui->PassLineEdit->text();
}

void AdministratorW::on_loginPushButton_clicked()
{
    ui->pushButton->show();

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
            ui->CameraLB->hide();
            ui->InIofoBt->show();
            ui->DelIofoBt->show();
            ui->NameBt->hide();
            ui->SureBt->hide();
            ui->NameaLabel->hide();
            ui->nameLE->hide();
            ui->NextBt->hide();
            ui->TakePhotoBt->hide();
            ui->messageLable->hide();

            ui->LoginLabel->hide();
            ui->loginPushButton->hide();
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

    switch (KeyboardSureLineEditFlag) {
    case 0:
        ui->UserLineEdit->setText(textInput->text());
        break;
    case 1:
        ui->PassLineEdit->setText(textInput->text());
        break;
    case 2:
        ui->nameLE->setText(textInput->text());
        break;
    case 3:
        ui->NumLineEdit->setText(textInput->text());
        break;
    default:
        break;
    }

}

void AdministratorW::on_NextBt_clicked()
{
    switch (NextFlag) {
    case 0:
        ui->TakePhotoBt->show();
        break;
    case 1:
        ui->InIofoBt->hide();
        ui->NameBt->show();
        ui->SureBt->hide();
        ui->NameaLabel->show();
        ui->nameLE->show();
        ui->NextBt->show();
        ui->TakePhotoBt->hide();
        ui->messageLable->setText("请输入新员工姓名");

        NextFlag = 2;
        break;
    case 2:
        ui->InIofoBt->hide();
        ui->NameBt->hide();
        ui->SureBt->show();
        ui->NameaLabel->hide();
        ui->nameLE->hide();
        ui->NextBt->hide();
        ui->TakePhotoBt->hide();
        ui->messageLable->setText("点击确认录入信息");

        NextFlag = 0;
        break;
    default:
        break;
    }
}

void AdministratorW::on_NameBt_clicked()
{
    KeyboardSureLineEditFlag = 2;

    keyboard.show();
    KeyboardWindow.show();
    ui->KeyboardReturnPushButton->show();
    ui->KeyboardSurePushButton->show();

    textInput->setText(ui->nameLE->text());
}

void AdministratorW::on_ReturnAdMBt_clicked()
{
    ui->CameraLB->hide();
    ui->ReturnAdMBt->hide();
    ui->NameBt->hide();
    ui->SureBt->hide();
    ui->NameaLabel->hide();
    ui->nameLE->hide();
    ui->NextBt->hide();
    ui->TakePhotoBt->hide();
    ui->messageLable->hide();
    ui->LoginLabel->hide();
    ui->loginPushButton->hide();
    ui->pushButton->hide();
    ui->UserLineEdit->hide();
    ui->PassLineEdit->hide();
    ui->checkBox->hide();
    ui->HintLabel->hide();

    ui->ImageLb1->hide();
    ui->ImageLb2->hide();
    ui->ImageLb3->hide();
    ui->ImageLb4->hide();
    ui->ImageLb5->hide();
    ui->ImageLb6->hide();
    ui->ImageLb7->hide();
    ui->ImageLb8->hide();
    ui->ImageLb9->hide();
    ui->ImageLb10->hide();

    ui->InIofoBt->show();
    ui->DelIofoBt->show();
    ui->pushButton->show();

    if(SureFlag == false)
    {
        char sys[512] = {0};
        sprintf(sys,"rm -rf ./faces/%d",DirFileNum+1);
        system(sys);
    }
}

void AdministratorW::on_DelIofoBt_clicked()
{
    ui->InIofoBt->hide();
    ui->DelIofoBt->hide();
    ui->pushButton->hide();

    ui->ReturnDelBt->show();
    ui->DelNumLabel->show();
    ui->TextLlabel->show();
    ui->NumLineEdit->show();
    ui->DelNumSureBt->show();

    ui->DelNumLabel->setText("请输入要删除的员工号");
}

void AdministratorW::on_DelNumSureBt_clicked()
{
    bool ok;
    int n = 0,dec = (ui->NumLineEdit->text()).toInt(&ok, 10);
    char sys[512] = {0};

    QString sql = QString("select * from info where id=%1").arg(dec);
    QSqlQuery query;
    query.exec(sql);

    if(query.first())
    {
        sql = QString("delete from info where id=%1").arg(dec);
        query.exec(sql);

        sprintf(sys,"rm -r ./faces/%d",dec);
        system(sys);

        /**更新数据库**/
        UpdateDatabase_imagePathId("faces");

        /**查看faces目录是否为空，如果为空则不进行训练**/
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

                n = DirName.toInt();
            }
        }

        if(n > 0)
        {
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
        }

        ui->DelNumLabel->setText("删除成功");
    }
    else
    {
        ui->DelNumLabel->setText("工号输入不正确");
    }
}

void AdministratorW::on_ReturnDelBt_clicked()
{
    ui->InIofoBt->show();
    ui->DelIofoBt->show();
    ui->pushButton->show();

    ui->ReturnDelBt->hide();
    ui->DelNumLabel->hide();
    ui->TextLlabel->hide();
    ui->NumLineEdit->hide();
    ui->DelNumSureBt->hide();
}

#ifndef V4L2API_H
#define V4L2API_H
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <string.h>
#include <exception>
#include <QThread>
#include <QImage>
#include <QObject>

#include <QSqlDatabase>
#include <QSqlQuery>

#include <opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/face.hpp>

using namespace  cv;
using namespace  std;

const int WIDTH = 640;
const int HEIGHT= 480;

//异常类
class VideoException : public exception
{
public:
    VideoException(string err):errStr(err) {}
    ~VideoException(){};
    const char* what()const  noexcept
    {
        return errStr.c_str();
    }
private:
    string errStr;
};


struct VideoFrame
{
    char *start; //保存内核空间映射到用户空间的空间首地址
    int length;//空间长度
};


class V4l2Api :public QThread
{
    Q_OBJECT
public:
    V4l2Api(const char *dname="/dev/video7", int count=4);
    ~V4l2Api();
    void open();
    void close();
    void grapImage(char *imageBuffer, int *length);
    bool yuyv_to_rgb888(unsigned char *yuyvdata, unsigned char *rgbdata, int picw=WIDTH, int pich=HEIGHT);

    //定义run函数
    void run();
    void jpeg_to_rgb888(unsigned char *jpegData, int size, unsigned char *rgbdata);

    void detectAndDisplay(Mat& frame,Mat& headImage);

    //打卡标志位
    bool PCard;
private:
    void video_init();
    void video_mmap();
private:
    string deviceName;
    int vfd;//保存文件描述符
    int count;//缓冲区个数

    vector<struct VideoFrame> framebuffers;
    //脸和眼睛分类器
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;

    Mat MyFace;
    bool FaceFlag;

signals:
    void sendImage(QImage,QImage);
    void sendPersonInfo(QString,int,int);
};

#endif // V4L2API_H

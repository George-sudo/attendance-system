#include "v4l2api.h"
#include <QDebug>
#include <QImage>
#include <jpeglib.h>

using namespace cv;
using namespace cv::face;

V4l2Api::V4l2Api(const char *dname, int count):deviceName(dname),count(count)
{
    this->open();
    //打卡标志位
    PCard = false;

    FaceFlag = false;
}


V4l2Api::~V4l2Api()
{
    this->close();
}


void V4l2Api::open()
{
    video_init();

    video_mmap();
#if 1
    //开始采集
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int ret  =  ioctl(this->vfd, VIDIOC_STREAMON, &type);
    if(ret < 0)
    {
        perror("start fail");
    }
#endif
}


void V4l2Api::close()
{
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int ret  =  ioctl(this->vfd, VIDIOC_STREAMOFF, &type);
    if(ret < 0)
    {
        perror("stop fail");
    }
    //释放映射
    for(int i=0; i<this->framebuffers.size(); i++)
    {
        munmap(framebuffers.at(i).start, framebuffers.at(i).length);
    }
}


/*抓取摄像头的一帧数据（一张图片）*/
void V4l2Api::grapImage(char *imageBuffer, int *length)
{
    struct v4l2_buffer readbuf;//内核结构体
    readbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    readbuf.memory = V4L2_MEMORY_MMAP;

    if(ioctl(this->vfd, VIDIOC_DQBUF, &readbuf)<0)//取一针数据
    {
        perror("read image fail");
    }

    *length = readbuf.length;
    memcpy(imageBuffer,framebuffers[readbuf.index].start, framebuffers[readbuf.index].length);

    //把用完的队列空间放回队列中重复使用
    if(ioctl(vfd, VIDIOC_QBUF, &readbuf)<0)
    {
        perror("destroy fail");
        exit(1);
    }
}


/*摄像头初始化*/
void V4l2Api::video_init()
{
    //1.打开设备
    this->vfd = ::open(deviceName.c_str(), O_RDWR);
    if(this->vfd < 0)
    {
        perror("open fail");
        VideoException vexp("open fail");//创建异常对象
        //抛异常
        throw vexp;
    }

    //2.配置采集属性
    struct v4l2_format vfmt;
    vfmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    vfmt.fmt.pix.width = WIDTH;
    vfmt.fmt.pix.height = HEIGHT;
    vfmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;//（设置视频输出格式，但是要摄像头支持4:2:2）
    //通过ioctl把属性写入设备
    int ret  = ioctl(this->vfd, VIDIOC_S_FMT, &vfmt);
    if(ret < 0)
    {
        VideoException vexp("set fail");//创建异常对象
        throw vexp;
    }
    //通过ioctl从设备获取属性
    memset(&vfmt, 0, sizeof(vfmt));
    vfmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = ioctl(this->vfd, VIDIOC_G_FMT, &vfmt);
    if(ret < 0)
    {
        VideoException vexp("get fail");//创建异常对象
        throw vexp;
    }

    if(vfmt.fmt.pix.width == WIDTH && vfmt.fmt.pix.height==HEIGHT
            && vfmt.fmt.pix.pixelformat == V4L2_PIX_FMT_YUYV)
    {

    }else {
        VideoException vexp("set error");//创建异常对象
        throw vexp;
    }
}


/*申请摄像头映射空间*/
void V4l2Api::video_mmap()
{
    //1、申请缓冲区队列
    struct v4l2_requestbuffers reqbuffer;
    reqbuffer.count = this->count;//申请缓冲区队列长度
    reqbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbuffer.memory = V4L2_MEMORY_MMAP;
    int ret = ioctl(this->vfd, VIDIOC_REQBUFS, &reqbuffer);
    if(ret < 0)
    {
        VideoException vexp("req buffer fail");//创建异常对象
        throw vexp;
    }

    //2、映射
    for(int i=0; i<this->count; i++)
    {
        struct VideoFrame frame;

        struct v4l2_buffer mapbuffer;
        mapbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        mapbuffer.index = i;
        mapbuffer.memory = V4L2_MEMORY_MMAP;
        //从队列中拿到内核空间
        ret  = ioctl(this->vfd, VIDIOC_QUERYBUF, &mapbuffer);
        if(ret < 0)
        {
            perror("query fail");
        }
        //映射
        frame.length = mapbuffer.length;
        frame.start = (char *)mmap(NULL, mapbuffer.length, PROT_READ|PROT_WRITE, MAP_SHARED, this->vfd, mapbuffer.m.offset);

        //空间放回队列中（内核空间）
        ret = ioctl(this->vfd, VIDIOC_QBUF, &mapbuffer);

        //把frame添加到容器framebuffers
        framebuffers.push_back(frame);
    }
}


#if 0
/*转换yuyv图片格式为rgb*/
bool V4l2Api::yuyv_to_rgb888(unsigned char *yuyvdata, unsigned char *rgbdata, int picw, int pich)
{
    int i, j;
    unsigned char y1,y2,u,v;
    int r1,g1,b1,r2,g2,b2;

    //确保所转的数据或要保存的地址有效
    if(yuyvdata == NULL || rgbdata == NULL)
    {
        return false;
    }

    int tmpw = picw/2;
    for(i=0; i<pich; i++)
    {
        for(j=0; j<tmpw; j++)// 640/2  == 320
        {
            //yuv422
            //R = 1.164*(Y-16) + 1.159*(V-128);
            //G = 1.164*(Y-16) - 0.380*(U-128)+ 0.813*(V-128);
            //B = 1.164*(Y-16) + 2.018*(U-128));

            //下面的四个像素为：[Y0 U0 V0] [Y1 U1 V1] -------------[Y2 U2 V2] [Y3 U3 V3]
            //存放的码流为：    Y0 U0 Y1 V1------------------------Y2 U2 Y3 V3
            //映射出像素点为：  [Y0 U0 V1] [Y1 U0 V1]--------------[Y2 U2 V3] [Y3 U2 V3]

            //获取每个像素yuyv数据   YuYv
            y1 = *(yuyvdata + (i*tmpw+j)*4);                //yuv像素的Y
            u  = *(yuyvdata + (i*tmpw+j)*4+1);              //yuv像素的U
            y2 = *(yuyvdata + (i*tmpw+j)*4+2);
            v  = *(yuyvdata + (i*tmpw+j)*4+3);

            //把yuyv数据转换为rgb数据
            r1 = y1 + 1.042*(v-128);
            g1 = y1 - 0.34414*(u-128);
            b1 = y1 + 1.772*(u-128);

            r2 = y2 + 1.042*(v-128);
            g2 = y2 - 0.34414*(u-128);
            b2 = y2 + 1.772*(u-128);

            if(r1 > 255) r1=255;
            else if(r1 < 0) r1 = 0;

            if(g1 > 255) g1=255;
            else if(g1 < 0) g1 = 0;

            if(b1 > 255) b1=255;
            else if(b1 < 0) b1 = 0;

            if(r2 > 255) r2=255;
            else if(r2 < 0) r2 = 0;

            if(g2 > 255) g2=255;
            else if(g2 < 0) g2 = 0;

            if(b2 > 255) b2=255;
            else if(b2 < 0) b2 = 0;

            //把rgb值保存于rgb空间 数据为反向
            rgbdata[((pich-1-i)*tmpw+j)*6]     = (unsigned char)b1;
            rgbdata[((pich-1-i)*tmpw+j)*6 + 1] = (unsigned char)g1;
            rgbdata[((pich-1-i)*tmpw+j)*6 + 2] = (unsigned char)r1;
            rgbdata[((pich-1-i)*tmpw+j)*6 + 3] = (unsigned char)b2;
            rgbdata[((pich-1-i)*tmpw+j)*6 + 4] = (unsigned char)g2;
            rgbdata[((pich-1-i)*tmpw+j)*6 + 5] = (unsigned char)r2;
        }
    }
    return true;
}

void V4l2Api::jpeg_to_rgb888(unsigned char *jpegData, int size, unsigned char *rgbdata)
{
    //解码jpeg图片
    //1.定义解码对象struct jpeg_decompress_struct 错误处理对象struct jpeg_error_mgr;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr err;

    //2.初始化错误jpeg_std_error(err)，创建初始化解码对象jpeg_create_decompress();
    cinfo.err = jpeg_std_error(&err);
    jpeg_create_decompress(&cinfo);

    //3.加载源数据jpeg_mem_src()
    jpeg_mem_src(&cinfo, jpegData, size);

    //4.获取jpeg图片头数据
    jpeg_read_header(&cinfo, true);

    //5.开始解码
    jpeg_start_decompress(&cinfo);

    //6.分配存储一行像素所需要的空间//---RGB数据
    //640--cinfo.output_width, 480--cinfo.output_height
    char *rowFrame=(char*)malloc(cinfo.output_width*3);

    int pos = 0;
    //7.一行一行循环读取（一次读取一行，要全部读完）
    while(cinfo.output_scanline<cinfo.output_height)
    {
            //读取一行数据--解码一行
            jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&rowFrame, 1);

            //把rgb像素显示在lcd上 mmp
            memcpy(rgbdata+pos, rowFrame,cinfo.output_width*3);
            pos += cinfo.output_width*3;
    }
    free(rowFrame);
    //8.解码完成
    jpeg_finish_decompress(&cinfo);
    //9.销毁解码对象
    jpeg_destroy_decompress(&cinfo);
}
#endif


void V4l2Api::run()
{

    static Mat yuvImage(HEIGHT,WIDTH,CV_8UC2);//CV_8UC2是代表RGB彩色图像–3通道图像，每个通道8bit
    static uchar *buffer = yuvImage.data;
    static Mat rgbImage,headImage,frame;
    static int len,predictedLabel,id,state;
    static QString sql,name;

    //加载分类器
    if( !face_cascade.load( "haarcascade_frontalface_alt.xml" ) )
    {
        cout << "--(!)Error loading face cascade\n";
        exit(-1);
    }

    if( !eyes_cascade.load( "haarcascade_eye_tree_eyeglasses.xml" ) )
    {
        cout << "--(!)Error loading eyes cascade\n";
        exit(-1);
    }

    while(1)
    { 
        grapImage((char *)buffer, &len);

        cvtColor(yuvImage, rgbImage, CV_YUV2RGB_YUYV);

        //创建图片副本,用于剪切脸部
        headImage = rgbImage.clone();

        //检测人脸和眼睛,并且剪切出脸部图像headImage
        detectAndDisplay( rgbImage, headImage);

        QImage Q_rgbImage(rgbImage.data, rgbImage.cols, rgbImage.rows, rgbImage.step1() , QImage::Format_RGB888);
        QImage Q_HeadImage(MyFace.data, MyFace.cols, MyFace.rows, MyFace.step1() , QImage::Format_RGB888);

        if(FaceFlag)
            emit sendImage(Q_rgbImage,Q_HeadImage);
        else
            emit sendImage(Q_rgbImage,Q_rgbImage);


        //打卡
        if((PCard == true) && (FaceFlag == true))
        {
            if(Q_HeadImage.width()==92 && Q_HeadImage.height()==112)
            {

                Q_HeadImage.save("10.jpg","jpg",100);
                frame = imread("10.jpg",0);

                Ptr<EigenFaceRecognizer> model =  EigenFaceRecognizer::create();
                model->read("MyFacePCAModel.xml");
                predictedLabel = model->predict(frame);

                //从数据库中查找该人员信息并且在窗口显示出来
                sql = QString("select * from info where id=%1").arg(predictedLabel);
                QSqlQuery query;
                query.exec(sql);

                if(query.next())
                {

                    name = query.value(2).toString();

                    id = query.value(0).toInt();

                    state = query.value(3).toInt();

                    //发送信号给ArmV4l2Opencv对象显示员工信息
                    emit sendPersonInfo(name,id,state);
                }

            } 
        }

        FaceFlag = false;
        PCard = false;
        msleep(5);
    }
}

//检测人脸和眼睛,并且剪切出脸部
void V4l2Api::detectAndDisplay( Mat& frame,Mat& Image )
{
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );

    //直方图均衡化,传入是8通道图像（灰度图像）
    equalizeHist( frame_gray, frame_gray );

    //检测脸
    std::vector<Rect> faces;
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_DO_ROUGH_SEARCH, Size(250, 250));

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        //计算检测出来脸部图像的中心
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );

        //在原来图像中人物脸上画椭型
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4 );

        /*
        //在脸部图像中检测眼睛
        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;
        eyes_cascade.detectMultiScale( faceROI, eyes ,1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_DO_ROUGH_SEARCH);

        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            //返回跟参数最接近的整数值，即四舍五入
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            //画圆
            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4 );
        }
        */

        //剪切脸部，重新设置大小
        Mat faceROI = Image(faces[i]);//对headImage图像重新设置大小和faces[i]一样
        if (faceROI.cols > 100)
        {
            //重新设置图片大小
            resize(faceROI, MyFace, Size(92, 112));
            FaceFlag = true;
        }
    }

}


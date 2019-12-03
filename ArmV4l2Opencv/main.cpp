#include "armv4l2opencv.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ArmV4l2Opencv w;
    w.show();

    return a.exec();
}

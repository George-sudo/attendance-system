#include "system_main.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    System_Main w;
    w.show();

    return a.exec();
}

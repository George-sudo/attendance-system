#include "system_main.h"
#include "ui_system_main.h"

System_Main::System_Main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::System_Main)
{
    ui->setupUi(this);
}

System_Main::~System_Main()
{
    delete ui;
}

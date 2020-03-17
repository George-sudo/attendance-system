#ifndef SYSTEM_MAIN_H
#define SYSTEM_MAIN_H

#include <QMainWindow>

namespace Ui {
class System_Main;
}

class System_Main : public QMainWindow
{
    Q_OBJECT

public:
    explicit System_Main(QWidget *parent = nullptr);
    ~System_Main();

private:
    Ui::System_Main *ui;
};

#endif // SYSTEM_MAIN_H

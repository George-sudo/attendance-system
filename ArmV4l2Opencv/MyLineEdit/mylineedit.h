#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H
#include <QLineEdit>
#include<QMouseEvent>

//添加mylineedit类继承QLineEdit
class MyLineEdit:public QLineEdit
{
 Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = 0);
     ~MyLineEdit();
protected:
    //添加并重写鼠标点击事件函数
    virtual void mousePressEvent(QMouseEvent *e);
signals:
    //点击信号函数
    void clicked();
};
#endif // MYLINEEDIT_H

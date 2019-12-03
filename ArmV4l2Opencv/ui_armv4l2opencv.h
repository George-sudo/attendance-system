/********************************************************************************
** Form generated from reading UI file 'armv4l2opencv.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARMV4L2OPENCV_H
#define UI_ARMV4L2OPENCV_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ArmV4l2Opencv
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pCardBt;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *DateLable;
    QLCDNumber *lcdNumber;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *systemLogBt;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLabel *numLable;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *nameLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLabel *stateLable;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLabel *timeLable;

    void setupUi(QMainWindow *ArmV4l2Opencv)
    {
        if (ArmV4l2Opencv->objectName().isEmpty())
            ArmV4l2Opencv->setObjectName(QStringLiteral("ArmV4l2Opencv"));
        ArmV4l2Opencv->resize(800, 480);
        centralWidget = new QWidget(ArmV4l2Opencv);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 621, 480));
        label->setMinimumSize(QSize(500, 480));
        label->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        pCardBt = new QPushButton(centralWidget);
        pCardBt->setObjectName(QStringLiteral("pCardBt"));
        pCardBt->setGeometry(QRect(620, 410, 181, 61));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pCardBt->sizePolicy().hasHeightForWidth());
        pCardBt->setSizePolicy(sizePolicy);
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(620, 0, 181, 81));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        DateLable = new QLabel(widget);
        DateLable->setObjectName(QStringLiteral("DateLable"));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        DateLable->setFont(font);
        DateLable->setStyleSheet(QStringLiteral("color: rgb(255, 8, 41);"));
        DateLable->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(DateLable);

        lcdNumber = new QLCDNumber(widget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setStyleSheet(QStringLiteral("color: rgb(255, 8, 41);"));
        lcdNumber->setDigitCount(8);

        verticalLayout_2->addWidget(lcdNumber);

        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(620, 90, 181, 131));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(widget1);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pushButton);

        systemLogBt = new QPushButton(widget1);
        systemLogBt->setObjectName(QStringLiteral("systemLogBt"));
        sizePolicy.setHeightForWidth(systemLogBt->sizePolicy().hasHeightForWidth());
        systemLogBt->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(systemLogBt);

        widget2 = new QWidget(centralWidget);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(620, 230, 181, 171));
        verticalLayout_3 = new QVBoxLayout(widget2);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(widget2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMaximumSize(QSize(50, 16777215));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(11);
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_5);

        numLable = new QLabel(widget2);
        numLable->setObjectName(QStringLiteral("numLable"));
        numLable->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(numLable);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(widget2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(50, 16777215));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        label_2->setFont(font2);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_2);

        nameLabel = new QLabel(widget2);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        nameLabel->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(nameLabel);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(widget2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(50, 16777215));
        label_3->setFont(font2);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_3);

        stateLable = new QLabel(widget2);
        stateLable->setObjectName(QStringLiteral("stateLable"));
        stateLable->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(stateLable);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(widget2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(50, 16777215));
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_4);

        timeLable = new QLabel(widget2);
        timeLable->setObjectName(QStringLiteral("timeLable"));
        timeLable->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(timeLable);


        verticalLayout_3->addLayout(horizontalLayout_3);

        ArmV4l2Opencv->setCentralWidget(centralWidget);

        retranslateUi(ArmV4l2Opencv);

        QMetaObject::connectSlotsByName(ArmV4l2Opencv);
    } // setupUi

    void retranslateUi(QMainWindow *ArmV4l2Opencv)
    {
        ArmV4l2Opencv->setWindowTitle(QApplication::translate("ArmV4l2Opencv", "ArmV4l2Opencv", 0));
        label->setText(QString());
        pCardBt->setText(QApplication::translate("ArmV4l2Opencv", "\346\211\223\345\215\241", 0));
        DateLable->setText(QString());
        pushButton->setText(QApplication::translate("ArmV4l2Opencv", "\345\274\200\345\220\257\346\211\223\345\215\241\347\263\273\347\273\237", 0));
        systemLogBt->setText(QApplication::translate("ArmV4l2Opencv", "\347\263\273\347\273\237\347\256\241\347\220\206\345\221\230\347\231\273\345\275\225", 0));
        label_5->setText(QApplication::translate("ArmV4l2Opencv", "\345\267\245\345\217\267:", 0));
        numLable->setText(QString());
        label_2->setText(QApplication::translate("ArmV4l2Opencv", "\345\247\223\345\220\215:", 0));
        nameLabel->setText(QString());
        label_3->setText(QApplication::translate("ArmV4l2Opencv", "\347\212\266\346\200\201:", 0));
        stateLable->setText(QString());
        label_4->setText(QApplication::translate("ArmV4l2Opencv", "\346\227\266\351\227\264:", 0));
        timeLable->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ArmV4l2Opencv: public Ui_ArmV4l2Opencv {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARMV4L2OPENCV_H

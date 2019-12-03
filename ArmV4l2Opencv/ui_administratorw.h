/********************************************************************************
** Form generated from reading UI file 'administratorw.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINISTRATORW_H
#define UI_ADMINISTRATORW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdministratorW
{
public:
    QWidget *centralwidget;
    QPushButton *retBt;
    QLabel *CameraLB;
    QPushButton *InIofoBt;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *ImageLb1;
    QLabel *ImageLb2;
    QLabel *ImageLb3;
    QLabel *ImageLb4;
    QLabel *ImageLb5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *ImageLb6;
    QLabel *ImageLb7;
    QLabel *ImageLb8;
    QLabel *ImageLb9;
    QLabel *ImageLb10;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QPushButton *TakePhotoBt;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *nameLE;
    QPushButton *SureBt;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *messageLable;
    QLabel *messageLable_2;
    QLabel *messageLable_3;
    QLabel *messageLable_4;

    void setupUi(QMainWindow *AdministratorW)
    {
        if (AdministratorW->objectName().isEmpty())
            AdministratorW->setObjectName(QStringLiteral("AdministratorW"));
        AdministratorW->resize(800, 480);
        centralwidget = new QWidget(AdministratorW);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        retBt = new QPushButton(centralwidget);
        retBt->setObjectName(QStringLiteral("retBt"));
        retBt->setGeometry(QRect(0, 0, 61, 61));
        CameraLB = new QLabel(centralwidget);
        CameraLB->setObjectName(QStringLiteral("CameraLB"));
        CameraLB->setGeometry(QRect(380, 0, 421, 241));
        CameraLB->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        InIofoBt = new QPushButton(centralwidget);
        InIofoBt->setObjectName(QStringLiteral("InIofoBt"));
        InIofoBt->setGeometry(QRect(71, 1, 301, 61));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InIofoBt->sizePolicy().hasHeightForWidth());
        InIofoBt->setSizePolicy(sizePolicy);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(300, 240, 499, 237));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        ImageLb1 = new QLabel(layoutWidget);
        ImageLb1->setObjectName(QStringLiteral("ImageLb1"));
        ImageLb1->setMinimumSize(QSize(92, 112));
        ImageLb1->setMaximumSize(QSize(92, 112));

        horizontalLayout->addWidget(ImageLb1);

        ImageLb2 = new QLabel(layoutWidget);
        ImageLb2->setObjectName(QStringLiteral("ImageLb2"));
        ImageLb2->setMinimumSize(QSize(92, 112));
        ImageLb2->setMaximumSize(QSize(92, 112));

        horizontalLayout->addWidget(ImageLb2);

        ImageLb3 = new QLabel(layoutWidget);
        ImageLb3->setObjectName(QStringLiteral("ImageLb3"));
        ImageLb3->setMinimumSize(QSize(92, 112));
        ImageLb3->setMaximumSize(QSize(92, 112));

        horizontalLayout->addWidget(ImageLb3);

        ImageLb4 = new QLabel(layoutWidget);
        ImageLb4->setObjectName(QStringLiteral("ImageLb4"));
        ImageLb4->setMinimumSize(QSize(92, 112));
        ImageLb4->setMaximumSize(QSize(92, 112));

        horizontalLayout->addWidget(ImageLb4);

        ImageLb5 = new QLabel(layoutWidget);
        ImageLb5->setObjectName(QStringLiteral("ImageLb5"));
        ImageLb5->setMinimumSize(QSize(92, 112));
        ImageLb5->setMaximumSize(QSize(92, 112));

        horizontalLayout->addWidget(ImageLb5);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        ImageLb6 = new QLabel(layoutWidget);
        ImageLb6->setObjectName(QStringLiteral("ImageLb6"));
        ImageLb6->setMinimumSize(QSize(92, 112));
        ImageLb6->setMaximumSize(QSize(92, 112));

        horizontalLayout_2->addWidget(ImageLb6);

        ImageLb7 = new QLabel(layoutWidget);
        ImageLb7->setObjectName(QStringLiteral("ImageLb7"));
        ImageLb7->setMinimumSize(QSize(92, 112));
        ImageLb7->setMaximumSize(QSize(92, 112));

        horizontalLayout_2->addWidget(ImageLb7);

        ImageLb8 = new QLabel(layoutWidget);
        ImageLb8->setObjectName(QStringLiteral("ImageLb8"));
        ImageLb8->setMinimumSize(QSize(92, 112));
        ImageLb8->setMaximumSize(QSize(92, 112));

        horizontalLayout_2->addWidget(ImageLb8);

        ImageLb9 = new QLabel(layoutWidget);
        ImageLb9->setObjectName(QStringLiteral("ImageLb9"));
        ImageLb9->setMinimumSize(QSize(92, 112));
        ImageLb9->setMaximumSize(QSize(92, 112));

        horizontalLayout_2->addWidget(ImageLb9);

        ImageLb10 = new QLabel(layoutWidget);
        ImageLb10->setObjectName(QStringLiteral("ImageLb10"));
        ImageLb10->setMinimumSize(QSize(92, 112));
        ImageLb10->setMaximumSize(QSize(92, 112));

        horizontalLayout_2->addWidget(ImageLb10);


        verticalLayout->addLayout(horizontalLayout_2);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 240, 291, 241));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        TakePhotoBt = new QPushButton(layoutWidget1);
        TakePhotoBt->setObjectName(QStringLiteral("TakePhotoBt"));
        sizePolicy.setHeightForWidth(TakePhotoBt->sizePolicy().hasHeightForWidth());
        TakePhotoBt->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(TakePhotoBt);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label);

        nameLE = new QLineEdit(layoutWidget1);
        nameLE->setObjectName(QStringLiteral("nameLE"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(nameLE->sizePolicy().hasHeightForWidth());
        nameLE->setSizePolicy(sizePolicy2);
        nameLE->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(nameLE);


        verticalLayout_2->addLayout(horizontalLayout_3);

        SureBt = new QPushButton(layoutWidget1);
        SureBt->setObjectName(QStringLiteral("SureBt"));
        sizePolicy.setHeightForWidth(SureBt->sizePolicy().hasHeightForWidth());
        SureBt->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(SureBt);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 70, 361, 171));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        messageLable = new QLabel(layoutWidget2);
        messageLable->setObjectName(QStringLiteral("messageLable"));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(11);
        messageLable->setFont(font);
        messageLable->setStyleSheet(QStringLiteral("color: rgb(82, 30, 255);"));

        verticalLayout_3->addWidget(messageLable);

        messageLable_2 = new QLabel(layoutWidget2);
        messageLable_2->setObjectName(QStringLiteral("messageLable_2"));
        messageLable_2->setFont(font);
        messageLable_2->setStyleSheet(QStringLiteral("color: rgb(82, 30, 255);"));

        verticalLayout_3->addWidget(messageLable_2);

        messageLable_3 = new QLabel(layoutWidget2);
        messageLable_3->setObjectName(QStringLiteral("messageLable_3"));
        messageLable_3->setFont(font);
        messageLable_3->setStyleSheet(QStringLiteral("color: rgb(82, 30, 255);"));

        verticalLayout_3->addWidget(messageLable_3);

        messageLable_4 = new QLabel(layoutWidget2);
        messageLable_4->setObjectName(QStringLiteral("messageLable_4"));
        messageLable_4->setFont(font);
        messageLable_4->setStyleSheet(QStringLiteral("color: rgb(82, 30, 255);"));
        messageLable_4->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(messageLable_4);

        AdministratorW->setCentralWidget(centralwidget);

        retranslateUi(AdministratorW);

        QMetaObject::connectSlotsByName(AdministratorW);
    } // setupUi

    void retranslateUi(QMainWindow *AdministratorW)
    {
        AdministratorW->setWindowTitle(QApplication::translate("AdministratorW", "MainWindow", 0));
        retBt->setText(QApplication::translate("AdministratorW", "\350\277\224\345\233\236", 0));
        CameraLB->setText(QString());
        InIofoBt->setText(QApplication::translate("AdministratorW", "\347\202\271\345\207\273\345\275\225\345\205\245\346\226\260\345\221\230\345\267\245\344\277\241\346\201\257", 0));
        ImageLb1->setText(QString());
        ImageLb2->setText(QString());
        ImageLb3->setText(QString());
        ImageLb4->setText(QString());
        ImageLb5->setText(QString());
        ImageLb6->setText(QString());
        ImageLb7->setText(QString());
        ImageLb8->setText(QString());
        ImageLb9->setText(QString());
        ImageLb10->setText(QString());
        TakePhotoBt->setText(QApplication::translate("AdministratorW", "\346\213\215\347\205\247", 0));
        label->setText(QApplication::translate("AdministratorW", "\345\220\215\345\255\227\357\274\232", 0));
        nameLE->setText(QString());
        SureBt->setText(QApplication::translate("AdministratorW", "\347\241\256\350\256\244", 0));
        messageLable->setText(QString());
        messageLable_2->setText(QString());
        messageLable_3->setText(QString());
        messageLable_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AdministratorW: public Ui_AdministratorW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINISTRATORW_H

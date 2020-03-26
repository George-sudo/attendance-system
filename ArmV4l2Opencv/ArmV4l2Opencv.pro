#-------------------------------------------------
#
# Project created by QtCreator 2019-08-12T14:29:02
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArmV4l2Opencv
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        armv4l2opencv.cpp \
    v4l2api.cpp \
    administratorw.cpp \
    MyLineEdit/mylineedit.cpp

HEADERS += \
        armv4l2opencv.h \
    v4l2api.h \
    administratorw.h \
    MyLineEdit/mylineedit.h

FORMS += \
        armv4l2opencv.ui \
    administratorw.ui

INCLUDEPATH +=/opt/arm-opencv/include
INCLUDEPATH +=/opt/arm-opencv/include/opencv
INCLUDEPATH +=/opt/arm-opencv/include/opencv2
INCLUDEPATH +=./libjpeg
LIBS +=-L./libjpeg -ljpeg
LIBS += -L/opt/arm-opencv/lib/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs \
-lopencv_calib3d     -lopencv_highgui    -lopencv_shape\
-lopencv_core        -lopencv_imgcodecs  -lopencv_stitching\
-lopencv_dnn         -lopencv_imgproc    -lopencv_superres\
-lopencv_face        -lopencv_ml         -lopencv_videoio\
-lopencv_features2d  -lopencv_objdetect  -lopencv_video\
-lopencv_flann       -lopencv_photo      -lopencv_videostab\


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

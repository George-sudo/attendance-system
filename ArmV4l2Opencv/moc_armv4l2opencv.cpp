/****************************************************************************
** Meta object code from reading C++ file 'armv4l2opencv.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "armv4l2opencv.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'armv4l2opencv.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ArmV4l2Opencv_t {
    QByteArrayData data[8];
    char stringdata0[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ArmV4l2Opencv_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ArmV4l2Opencv_t qt_meta_stringdata_ArmV4l2Opencv = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ArmV4l2Opencv"
QT_MOC_LITERAL(1, 14, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 9), // "recvImage"
QT_MOC_LITERAL(4, 47, 5), // "image"
QT_MOC_LITERAL(5, 53, 9), // "headImage"
QT_MOC_LITERAL(6, 63, 22), // "on_systemLogBt_clicked"
QT_MOC_LITERAL(7, 86, 18) // "on_pCardBt_clicked"

    },
    "ArmV4l2Opencv\0on_pushButton_clicked\0"
    "\0recvImage\0image\0headImage\0"
    "on_systemLogBt_clicked\0on_pCardBt_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ArmV4l2Opencv[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    2,   35,    2, 0x08 /* Private */,
       6,    0,   40,    2, 0x08 /* Private */,
       7,    0,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage, QMetaType::QImage,    4,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ArmV4l2Opencv::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ArmV4l2Opencv *_t = static_cast<ArmV4l2Opencv *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->recvImage((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 2: _t->on_systemLogBt_clicked(); break;
        case 3: _t->on_pCardBt_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject ArmV4l2Opencv::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ArmV4l2Opencv.data,
      qt_meta_data_ArmV4l2Opencv,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ArmV4l2Opencv::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ArmV4l2Opencv::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ArmV4l2Opencv.stringdata0))
        return static_cast<void*>(const_cast< ArmV4l2Opencv*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ArmV4l2Opencv::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

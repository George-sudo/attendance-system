/****************************************************************************
** Meta object code from reading C++ file 'administratorw.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "administratorw.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'administratorw.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AdministratorW_t {
    QByteArrayData data[6];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AdministratorW_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AdministratorW_t qt_meta_stringdata_AdministratorW = {
    {
QT_MOC_LITERAL(0, 0, 14), // "AdministratorW"
QT_MOC_LITERAL(1, 15, 16), // "on_retBt_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 22), // "on_TakePhotoBt_clicked"
QT_MOC_LITERAL(4, 56, 19), // "on_InIofoBt_clicked"
QT_MOC_LITERAL(5, 76, 17) // "on_SureBt_clicked"

    },
    "AdministratorW\0on_retBt_clicked\0\0"
    "on_TakePhotoBt_clicked\0on_InIofoBt_clicked\0"
    "on_SureBt_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AdministratorW[] = {

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
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AdministratorW::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AdministratorW *_t = static_cast<AdministratorW *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_retBt_clicked(); break;
        case 1: _t->on_TakePhotoBt_clicked(); break;
        case 2: _t->on_InIofoBt_clicked(); break;
        case 3: _t->on_SureBt_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AdministratorW::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_AdministratorW.data,
      qt_meta_data_AdministratorW,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AdministratorW::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AdministratorW::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AdministratorW.stringdata0))
        return static_cast<void*>(const_cast< AdministratorW*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int AdministratorW::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

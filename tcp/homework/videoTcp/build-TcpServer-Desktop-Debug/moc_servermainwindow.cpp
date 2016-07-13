/****************************************************************************
** Meta object code from reading C++ file 'servermainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TcpServer/servermainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'servermainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ServerMainWindow_t {
    QByteArrayData data[24];
    char stringdata[352];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ServerMainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ServerMainWindow_t qt_meta_stringdata_ServerMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 26),
QT_MOC_LITERAL(2, 44, 0),
QT_MOC_LITERAL(3, 45, 2),
QT_MOC_LITERAL(4, 48, 4),
QT_MOC_LITERAL(5, 53, 23),
QT_MOC_LITERAL(6, 77, 4),
QT_MOC_LITERAL(7, 82, 20),
QT_MOC_LITERAL(8, 103, 1),
QT_MOC_LITERAL(9, 105, 13),
QT_MOC_LITERAL(10, 119, 7),
QT_MOC_LITERAL(11, 127, 13),
QT_MOC_LITERAL(12, 141, 25),
QT_MOC_LITERAL(13, 167, 4),
QT_MOC_LITERAL(14, 172, 22),
QT_MOC_LITERAL(15, 195, 16),
QT_MOC_LITERAL(16, 212, 18),
QT_MOC_LITERAL(17, 231, 21),
QT_MOC_LITERAL(18, 253, 21),
QT_MOC_LITERAL(19, 275, 1),
QT_MOC_LITERAL(20, 277, 28),
QT_MOC_LITERAL(21, 306, 12),
QT_MOC_LITERAL(22, 319, 11),
QT_MOC_LITERAL(23, 331, 19)
    },
    "ServerMainWindow\0clientInfoUpdataOK_signals\0"
    "\0id\0info\0devInfoUpdataOK_signals\0name\0"
    "devWorkState_signals\0s\0showStateInfo\0"
    "message\0showLog_slots\0getClientThreadInfo_slots\0"
    "list\0getDevThreadInfo_slots\0"
    "updateUI_devName\0updataUI_devThread\0"
    "updataUI_clientThread\0updataUI_devThreadNum\0"
    "i\0updataUI_clientThreadDevName\0"
    "start_server\0stop_server\0recordLogInfo_slots\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   89,    2, 0x06,
       5,    2,   94,    2, 0x06,
       7,    1,   99,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       9,    1,  102,    2, 0x0a,
      11,    0,  105,    2, 0x09,
      12,    1,  106,    2, 0x09,
      14,    1,  109,    2, 0x09,
      15,    1,  112,    2, 0x09,
      16,    1,  115,    2, 0x09,
      17,    1,  118,    2, 0x09,
      18,    2,  121,    2, 0x09,
      20,    2,  126,    2, 0x09,
      21,    0,  131,    2, 0x09,
      22,    0,  132,    2, 0x09,
      23,    1,  133,    2, 0x09,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,    4,
    QMetaType::Void, QMetaType::Bool,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   13,
    QMetaType::Void, QMetaType::QStringList,   13,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    6,   19,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void ServerMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ServerMainWindow *_t = static_cast<ServerMainWindow *>(_o);
        switch (_id) {
        case 0: _t->clientInfoUpdataOK_signals((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->devInfoUpdataOK_signals((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->devWorkState_signals((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->showStateInfo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->showLog_slots(); break;
        case 5: _t->getClientThreadInfo_slots((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 6: _t->getDevThreadInfo_slots((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 7: _t->updateUI_devName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->updataUI_devThread((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->updataUI_clientThread((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->updataUI_devThreadNum((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->updataUI_clientThreadDevName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 12: _t->start_server(); break;
        case 13: _t->stop_server(); break;
        case 14: _t->recordLogInfo_slots((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ServerMainWindow::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ServerMainWindow::clientInfoUpdataOK_signals)) {
                *result = 0;
            }
        }
        {
            typedef void (ServerMainWindow::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ServerMainWindow::devInfoUpdataOK_signals)) {
                *result = 1;
            }
        }
        {
            typedef void (ServerMainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ServerMainWindow::devWorkState_signals)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject ServerMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ServerMainWindow.data,
      qt_meta_data_ServerMainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *ServerMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ServerMainWindow.stringdata))
        return static_cast<void*>(const_cast< ServerMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ServerMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void ServerMainWindow::clientInfoUpdataOK_signals(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ServerMainWindow::devInfoUpdataOK_signals(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ServerMainWindow::devWorkState_signals(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'cameraServer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TcpServer/cameraServer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cameraServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CameraServer_t {
    QByteArrayData data[30];
    char stringdata[406];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CameraServer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CameraServer_t qt_meta_stringdata_CameraServer = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 12),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 6),
QT_MOC_LITERAL(4, 34, 24),
QT_MOC_LITERAL(5, 59, 21),
QT_MOC_LITERAL(6, 81, 2),
QT_MOC_LITERAL(7, 84, 4),
QT_MOC_LITERAL(8, 89, 25),
QT_MOC_LITERAL(9, 115, 21),
QT_MOC_LITERAL(10, 137, 26),
QT_MOC_LITERAL(11, 164, 12),
QT_MOC_LITERAL(12, 177, 19),
QT_MOC_LITERAL(13, 197, 4),
QT_MOC_LITERAL(14, 202, 17),
QT_MOC_LITERAL(15, 220, 10),
QT_MOC_LITERAL(16, 231, 12),
QT_MOC_LITERAL(17, 244, 16),
QT_MOC_LITERAL(18, 261, 13),
QT_MOC_LITERAL(19, 275, 19),
QT_MOC_LITERAL(20, 295, 3),
QT_MOC_LITERAL(21, 299, 4),
QT_MOC_LITERAL(22, 304, 6),
QT_MOC_LITERAL(23, 311, 16),
QT_MOC_LITERAL(24, 328, 13),
QT_MOC_LITERAL(25, 342, 9),
QT_MOC_LITERAL(26, 352, 6),
QT_MOC_LITERAL(27, 359, 11),
QT_MOC_LITERAL(28, 371, 17),
QT_MOC_LITERAL(29, 389, 15)
    },
    "CameraServer\0_status_info\0\0_error\0"
    "clientThreadInfo_signals\0clientDevInfo_signals\0"
    "id\0name\0clientThreadClose_signals\0"
    "devThreadInfo_signals\0devThreadClientNum_signals\0"
    "hasUnloadDev\0clientClose_signals\0info\0"
    "devUnload_signals\0Dev_Socket\0freeS_Thread\0"
    "killClientThread\0killDevThread\0"
    "workClientCMD_slots\0cmd\0argv\0handle\0"
    "clientInfoUpdate\0devInfoUpdate\0unloadDev\0"
    "number\0thread_init\0clientClose_slots\0"
    "devUnload_slots\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  119,    2, 0x06,
       3,    1,  122,    2, 0x06,
       4,    1,  125,    2, 0x06,
       5,    2,  128,    2, 0x06,
       8,    1,  133,    2, 0x06,
       9,    1,  136,    2, 0x06,
      10,    2,  139,    2, 0x06,
      11,    1,  144,    2, 0x06,
      12,    2,  147,    2, 0x06,
      14,    2,  152,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      15,    2,  157,    2, 0x0a,
      16,    1,  162,    2, 0x0a,
      17,    1,  165,    2, 0x0a,
      18,    1,  168,    2, 0x0a,
      19,    3,  171,    2, 0x0a,
      23,    2,  178,    2, 0x0a,
      24,    2,  183,    2, 0x0a,
      25,    2,  188,    2, 0x09,
      27,    0,  193,    2, 0x09,
      28,    1,  194,    2, 0x08,
      29,    1,  197,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    6,    7,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    6,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,   13,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int,   20,   21,   22,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   22,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    7,   26,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void CameraServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CameraServer *_t = static_cast<CameraServer *>(_o);
        switch (_id) {
        case 0: _t->_status_info((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->_error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->clientThreadInfo_signals((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 3: _t->clientDevInfo_signals((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->clientThreadClose_signals((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->devThreadInfo_signals((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 6: _t->devThreadClientNum_signals((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->hasUnloadDev((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->clientClose_signals((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->devUnload_signals((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->Dev_Socket((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->freeS_Thread((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->killClientThread((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->killDevThread((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->workClientCMD_slots((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 15: _t->clientInfoUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 16: _t->devInfoUpdate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 17: _t->unloadDev((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 18: _t->thread_init(); break;
        case 19: _t->clientClose_slots((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->devUnload_slots((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CameraServer::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraServer::_status_info)) {
                *result = 0;
            }
        }
        {
            typedef void (CameraServer::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraServer::_error)) {
                *result = 1;
            }
        }
        {
            typedef void (CameraServer::*_t)(const QStringList & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraServer::clientThreadInfo_signals)) {
                *result = 2;
            }
        }
        {
            typedef void (CameraServer::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraServer::clientDevInfo_signals)) {
                *result = 3;
            }
        }
        {
            typedef void (CameraServer::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraServer::clientThreadClose_signals)) {
                *result = 4;
            }
        }
        {
            typedef void (CameraServer::*_t)(const QStringList & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraServer::devThreadInfo_signals)) {
                *result = 5;
            }
        }
        {
            typedef void (CameraServer::*_t)(const QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraServer::devThreadClientNum_signals)) {
                *result = 6;
            }
        }
        {
            typedef void (CameraServer::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraServer::hasUnloadDev)) {
                *result = 7;
            }
        }
        {
            typedef void (CameraServer::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraServer::clientClose_signals)) {
                *result = 8;
            }
        }
        {
            typedef void (CameraServer::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraServer::devUnload_signals)) {
                *result = 9;
            }
        }
    }
}

const QMetaObject CameraServer::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_CameraServer.data,
      qt_meta_data_CameraServer,  qt_static_metacall, 0, 0}
};


const QMetaObject *CameraServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CameraServer.stringdata))
        return static_cast<void*>(const_cast< CameraServer*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int CameraServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void CameraServer::_status_info(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CameraServer::_error(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CameraServer::clientThreadInfo_signals(const QStringList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CameraServer::clientDevInfo_signals(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CameraServer::clientThreadClose_signals(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CameraServer::devThreadInfo_signals(const QStringList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CameraServer::devThreadClientNum_signals(const QString & _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void CameraServer::hasUnloadDev(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void CameraServer::clientClose_signals(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void CameraServer::devUnload_signals(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_END_MOC_NAMESPACE

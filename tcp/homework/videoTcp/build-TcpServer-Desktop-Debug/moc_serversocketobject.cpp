/****************************************************************************
** Meta object code from reading C++ file 'serversocketobject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TcpServer/serversocketobject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serversocketobject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ServerSocketObject_t {
    QByteArrayData data[11];
    char stringdata[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ServerSocketObject_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ServerSocketObject_t qt_meta_stringdata_ServerSocketObject = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 13),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 16),
QT_MOC_LITERAL(4, 51, 25),
QT_MOC_LITERAL(5, 77, 3),
QT_MOC_LITERAL(6, 81, 4),
QT_MOC_LITERAL(7, 86, 6),
QT_MOC_LITERAL(8, 93, 12),
QT_MOC_LITERAL(9, 106, 7),
QT_MOC_LITERAL(10, 114, 18)
    },
    "ServerSocketObject\0send_dev_name\0\0"
    "free_WriteThread\0serverDealWithCMD_signals\0"
    "cmd\0argv\0handle\0writeContext\0context\0"
    "devWillClose_slots\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerSocketObject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06,
       3,    1,   44,    2, 0x06,
       4,    3,   47,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       8,    1,   54,    2, 0x0a,
      10,    0,   57,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int,    5,    6,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    9,
    QMetaType::Void,

       0        // eod
};

void ServerSocketObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ServerSocketObject *_t = static_cast<ServerSocketObject *>(_o);
        switch (_id) {
        case 0: _t->send_dev_name((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->free_WriteThread((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->serverDealWithCMD_signals((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->writeContext((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 4: _t->devWillClose_slots(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ServerSocketObject::*_t)(const QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ServerSocketObject::send_dev_name)) {
                *result = 0;
            }
        }
        {
            typedef void (ServerSocketObject::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ServerSocketObject::free_WriteThread)) {
                *result = 1;
            }
        }
        {
            typedef void (ServerSocketObject::*_t)(int , const QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ServerSocketObject::serverDealWithCMD_signals)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject ServerSocketObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ServerSocketObject.data,
      qt_meta_data_ServerSocketObject,  qt_static_metacall, 0, 0}
};


const QMetaObject *ServerSocketObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerSocketObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ServerSocketObject.stringdata))
        return static_cast<void*>(const_cast< ServerSocketObject*>(this));
    return QObject::qt_metacast(_clname);
}

int ServerSocketObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ServerSocketObject::send_dev_name(const QString & _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ServerSocketObject::free_WriteThread(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ServerSocketObject::serverDealWithCMD_signals(int _t1, const QString & _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE

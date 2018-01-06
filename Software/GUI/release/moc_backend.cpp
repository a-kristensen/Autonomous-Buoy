/****************************************************************************
** Meta object code from reading C++ file 'backend.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../backend.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Backend_t {
    QByteArrayData data[24];
    char stringdata0[250];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Backend_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Backend_t qt_meta_stringdata_Backend = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Backend"
QT_MOC_LITERAL(1, 8, 12), // "sensorChange"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 2), // "id"
QT_MOC_LITERAL(4, 25, 5), // "value"
QT_MOC_LITERAL(5, 31, 8), // "response"
QT_MOC_LITERAL(6, 40, 6), // "reboot"
QT_MOC_LITERAL(7, 47, 15), // "sigDisconnected"
QT_MOC_LITERAL(8, 63, 12), // "dataRecieved"
QT_MOC_LITERAL(9, 76, 4), // "data"
QT_MOC_LITERAL(10, 81, 12), // "slotAsyncMsg"
QT_MOC_LITERAL(11, 94, 11), // "slotSyncMsg"
QT_MOC_LITERAL(12, 106, 10), // "slotReboot"
QT_MOC_LITERAL(13, 117, 16), // "slotDisconnected"
QT_MOC_LITERAL(14, 134, 16), // "setMotorPosition"
QT_MOC_LITERAL(15, 151, 7), // "setMode"
QT_MOC_LITERAL(16, 159, 11), // "connectBouy"
QT_MOC_LITERAL(17, 171, 4), // "port"
QT_MOC_LITERAL(18, 176, 18), // "sendCommandFromQML"
QT_MOC_LITERAL(19, 195, 3), // "cmd"
QT_MOC_LITERAL(20, 199, 15), // "setCalModeMotor"
QT_MOC_LITERAL(21, 215, 1), // "b"
QT_MOC_LITERAL(22, 217, 20), // "setCalModeController"
QT_MOC_LITERAL(23, 238, 11) // "setCalNorth"

    },
    "Backend\0sensorChange\0\0id\0value\0response\0"
    "reboot\0sigDisconnected\0dataRecieved\0"
    "data\0slotAsyncMsg\0slotSyncMsg\0slotReboot\0"
    "slotDisconnected\0setMotorPosition\0"
    "setMode\0connectBouy\0port\0sendCommandFromQML\0"
    "cmd\0setCalModeMotor\0b\0setCalModeController\0"
    "setCalNorth"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Backend[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   94,    2, 0x06 /* Public */,
       5,    2,   99,    2, 0x06 /* Public */,
       6,    0,  104,    2, 0x06 /* Public */,
       7,    0,  105,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,  106,    2, 0x0a /* Public */,
      10,    2,  109,    2, 0x0a /* Public */,
      11,    2,  114,    2, 0x0a /* Public */,
      12,    0,  119,    2, 0x0a /* Public */,
      13,    0,  120,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      14,    1,  121,    2, 0x02 /* Public */,
      15,    1,  124,    2, 0x02 /* Public */,
      16,    1,  127,    2, 0x02 /* Public */,
      18,    3,  130,    2, 0x02 /* Public */,
      20,    1,  137,    2, 0x02 /* Public */,
      22,    1,  140,    2, 0x02 /* Public */,
      23,    0,  143,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QVariant, QMetaType::QVariant,    3,    4,
    QMetaType::Void, QMetaType::QVariant, QMetaType::QVariant,    3,    4,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    9,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Float,    3,    4,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,   19,    3,    9,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void,

       0        // eod
};

void Backend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Backend *_t = static_cast<Backend *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sensorChange((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 1: _t->response((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 2: _t->reboot(); break;
        case 3: _t->sigDisconnected(); break;
        case 4: _t->dataRecieved((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 5: _t->slotAsyncMsg((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 6: _t->slotSyncMsg((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 7: _t->slotReboot(); break;
        case 8: _t->slotDisconnected(); break;
        case 9: _t->setMotorPosition((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->setMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->connectBouy((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->sendCommandFromQML((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 13: _t->setCalModeMotor((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->setCalModeController((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->setCalNorth(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Backend::*_t)(QVariant , QVariant );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Backend::sensorChange)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Backend::*_t)(QVariant , QVariant );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Backend::response)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Backend::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Backend::reboot)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Backend::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Backend::sigDisconnected)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject Backend::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Backend.data,
      qt_meta_data_Backend,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Backend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Backend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Backend.stringdata0))
        return static_cast<void*>(const_cast< Backend*>(this));
    return QObject::qt_metacast(_clname);
}

int Backend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void Backend::sensorChange(QVariant _t1, QVariant _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Backend::response(QVariant _t1, QVariant _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Backend::reboot()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Backend::sigDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

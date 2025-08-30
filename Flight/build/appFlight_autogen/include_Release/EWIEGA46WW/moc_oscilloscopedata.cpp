/****************************************************************************
** Meta object code from reading C++ file 'oscilloscopedata.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../oscilloscopedata.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'oscilloscopedata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN16OscilloscopeDataE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN16OscilloscopeDataE = QtMocHelpers::stringData(
    "OscilloscopeData",
    "runningChanged",
    "",
    "bufferSizeChanged",
    "dataUpdated",
    "setRunning",
    "running",
    "clearBuffer",
    "setTimeScale",
    "timeScaleIndex",
    "getChannelData",
    "QVariantList",
    "channel",
    "getTimeData",
    "addDataPoint",
    "time",
    "value",
    "isRunning",
    "bufferSize"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN16OscilloscopeDataE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       2,   89, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x06,    3 /* Public */,
       3,    0,   69,    2, 0x06,    4 /* Public */,
       4,    0,   70,    2, 0x06,    5 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   71,    2, 0x02,    6 /* Public */,
       7,    0,   74,    2, 0x02,    8 /* Public */,
       8,    1,   75,    2, 0x02,    9 /* Public */,
      10,    1,   78,    2, 0x02,   11 /* Public */,
      13,    0,   81,    2, 0x02,   13 /* Public */,
      14,    3,   82,    2, 0x02,   14 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    0x80000000 | 11, QMetaType::Int,   12,
    0x80000000 | 11,
    QMetaType::Void, QMetaType::Int, QMetaType::Double, QMetaType::Double,   12,   15,   16,

 // properties: name, type, flags, notifyId, revision
      17, QMetaType::Bool, 0x00015001, uint(0), 0,
      18, QMetaType::Int, 0x00015001, uint(1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject OscilloscopeData::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN16OscilloscopeDataE.offsetsAndSizes,
    qt_meta_data_ZN16OscilloscopeDataE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN16OscilloscopeDataE_t,
        // property 'isRunning'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'bufferSize'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<OscilloscopeData, std::true_type>,
        // method 'runningChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'bufferSizeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'dataUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setRunning'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'clearBuffer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setTimeScale'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'getChannelData'
        QtPrivate::TypeAndForceComplete<QVariantList, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'getTimeData'
        QtPrivate::TypeAndForceComplete<QVariantList, std::false_type>,
        // method 'addDataPoint'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>
    >,
    nullptr
} };

void OscilloscopeData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<OscilloscopeData *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->runningChanged(); break;
        case 1: _t->bufferSizeChanged(); break;
        case 2: _t->dataUpdated(); break;
        case 3: _t->setRunning((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->clearBuffer(); break;
        case 5: _t->setTimeScale((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: { QVariantList _r = _t->getChannelData((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 7: { QVariantList _r = _t->getTimeData();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->addDataPoint((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (OscilloscopeData::*)();
            if (_q_method_type _q_method = &OscilloscopeData::runningChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (OscilloscopeData::*)();
            if (_q_method_type _q_method = &OscilloscopeData::bufferSizeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (OscilloscopeData::*)();
            if (_q_method_type _q_method = &OscilloscopeData::dataUpdated; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isRunning(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->bufferSize(); break;
        default: break;
        }
    }
}

const QMetaObject *OscilloscopeData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OscilloscopeData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN16OscilloscopeDataE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int OscilloscopeData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void OscilloscopeData::runningChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void OscilloscopeData::bufferSizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void OscilloscopeData::dataUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP

/****************************************************************************
** Meta object code from reading C++ file 'sinewavetest.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sinewavetest.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sinewavetest.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12SineWaveTestE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN12SineWaveTestE = QtMocHelpers::stringData(
    "SineWaveTest",
    "generateSample",
    "",
    "start",
    "stop",
    "isRunning",
    "setFrequency",
    "frequency",
    "setAmplitude",
    "amplitude",
    "getFrequency",
    "getAmplitude"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN12SineWaveTestE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x08,    1 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   63,    2, 0x02,    2 /* Public */,
       4,    0,   64,    2, 0x02,    3 /* Public */,
       5,    0,   65,    2, 0x102,    4 /* Public | MethodIsConst  */,
       6,    1,   66,    2, 0x02,    5 /* Public */,
       8,    1,   69,    2, 0x02,    7 /* Public */,
      10,    0,   72,    2, 0x102,    9 /* Public | MethodIsConst  */,
      11,    0,   73,    2, 0x102,   10 /* Public | MethodIsConst  */,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Double,
    QMetaType::Double,

       0        // eod
};

Q_CONSTINIT const QMetaObject SineWaveTest::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN12SineWaveTestE.offsetsAndSizes,
    qt_meta_data_ZN12SineWaveTestE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN12SineWaveTestE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SineWaveTest, std::true_type>,
        // method 'generateSample'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'start'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'isRunning'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setFrequency'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'setAmplitude'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'getFrequency'
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'getAmplitude'
        QtPrivate::TypeAndForceComplete<double, std::false_type>
    >,
    nullptr
} };

void SineWaveTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SineWaveTest *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->generateSample(); break;
        case 1: _t->start(); break;
        case 2: _t->stop(); break;
        case 3: { bool _r = _t->isRunning();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->setFrequency((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 5: _t->setAmplitude((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 6: { double _r = _t->getFrequency();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 7: { double _r = _t->getAmplitude();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *SineWaveTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SineWaveTest::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN12SineWaveTestE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SineWaveTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP

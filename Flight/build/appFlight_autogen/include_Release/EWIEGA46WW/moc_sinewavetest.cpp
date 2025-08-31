/****************************************************************************
** Meta object code from reading C++ file 'SineWaveTest.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../SineWaveTest.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SineWaveTest.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14SineWaveWorkerE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN14SineWaveWorkerE = QtMocHelpers::stringData(
    "SineWaveWorker",
    "start",
    "",
    "stop",
    "reconfigure",
    "GeneratorParams",
    "params",
    "generateSamples"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN14SineWaveWorkerE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x0a,    1 /* Public */,
       3,    0,   39,    2, 0x0a,    2 /* Public */,
       4,    1,   40,    2, 0x0a,    3 /* Public */,
       7,    0,   43,    2, 0x08,    5 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject SineWaveWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN14SineWaveWorkerE.offsetsAndSizes,
    qt_meta_data_ZN14SineWaveWorkerE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN14SineWaveWorkerE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SineWaveWorker, std::true_type>,
        // method 'start'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'reconfigure'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const GeneratorParams &, std::false_type>,
        // method 'generateSamples'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SineWaveWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SineWaveWorker *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->start(); break;
        case 1: _t->stop(); break;
        case 2: _t->reconfigure((*reinterpret_cast< std::add_pointer_t<GeneratorParams>>(_a[1]))); break;
        case 3: _t->generateSamples(); break;
        default: ;
        }
    }
}

const QMetaObject *SineWaveWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SineWaveWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN14SineWaveWorkerE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SineWaveWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN12SineWaveTestE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN12SineWaveTestE = QtMocHelpers::stringData(
    "SineWaveTest",
    "QML.Element",
    "auto",
    "runningChanged",
    "",
    "running",
    "sampleRateChanged",
    "rate",
    "bufferUsageChanged",
    "usage",
    "samplesReady",
    "QVariantList",
    "timestamps",
    "channel0",
    "channel1",
    "channel2",
    "channel3",
    "setSampleRate",
    "start",
    "QVariantMap",
    "params",
    "stop",
    "reconfigure",
    "flushToQml",
    "qmlOscilloscope",
    "sampleRate",
    "bufferUsage"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN12SineWaveTestE[] = {

 // content:
      12,       // revision
       0,       // classname
       1,   14, // classinfo
      10,   16, // methods
       3,  110, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   76,    4, 0x06,    4 /* Public */,
       6,    1,   79,    4, 0x06,    6 /* Public */,
       8,    1,   82,    4, 0x06,    8 /* Public */,
      10,    5,   85,    4, 0x06,   10 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      17,    1,   96,    4, 0x0a,   16 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      18,    0,   99,    4, 0x02,   18 /* Public */,
      18,    1,  100,    4, 0x02,   19 /* Public */,
      21,    0,  103,    4, 0x02,   21 /* Public */,
      22,    1,  104,    4, 0x02,   22 /* Public */,
      23,    1,  107,    4, 0x02,   24 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 11, 0x80000000 | 11, 0x80000000 | 11, 0x80000000 | 11,   12,   13,   14,   15,   16,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    7,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, QMetaType::QObjectStar,   24,

 // properties: name, type, flags, notifyId, revision
       5, QMetaType::Bool, 0x00015001, uint(0), 0,
      25, QMetaType::Double, 0x00015103, uint(1), 0,
      26, QMetaType::Int, 0x00015001, uint(2), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject SineWaveTest::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN12SineWaveTestE.offsetsAndSizes,
    qt_meta_data_ZN12SineWaveTestE,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'running'
        bool,
        // property 'sampleRate'
        double,
        // property 'bufferUsage'
        int,
        // Q_OBJECT / Q_GADGET
        SineWaveTest,
        // method 'runningChanged'
        void,
        bool,
        // method 'sampleRateChanged'
        void,
        double,
        // method 'bufferUsageChanged'
        void,
        int,
        // method 'samplesReady'
        void,
        const QVariantList &,
        const QVariantList &,
        const QVariantList &,
        const QVariantList &,
        const QVariantList &,
        // method 'setSampleRate'
        void,
        double,
        // method 'start'
        void,
        // method 'start'
        void,
        const QVariantMap &,
        // method 'stop'
        void,
        // method 'reconfigure'
        void,
        const QVariantMap &,
        // method 'flushToQml'
        void,
        QObject *
    >,
    nullptr
} };

void SineWaveTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SineWaveTest *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->runningChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->sampleRateChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 2: _t->bufferUsageChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->samplesReady((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[5]))); break;
        case 4: _t->setSampleRate((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 5: _t->start(); break;
        case 6: _t->start((*reinterpret_cast< std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 7: _t->stop(); break;
        case 8: _t->reconfigure((*reinterpret_cast< std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 9: _t->flushToQml((*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (SineWaveTest::*)(bool );
            if (_q_method_type _q_method = &SineWaveTest::runningChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (SineWaveTest::*)(double );
            if (_q_method_type _q_method = &SineWaveTest::sampleRateChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (SineWaveTest::*)(int );
            if (_q_method_type _q_method = &SineWaveTest::bufferUsageChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (SineWaveTest::*)(const QVariantList & , const QVariantList & , const QVariantList & , const QVariantList & , const QVariantList & );
            if (_q_method_type _q_method = &SineWaveTest::samplesReady; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->running(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->sampleRate(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->bufferUsage(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setSampleRate(*reinterpret_cast< double*>(_v)); break;
        default: break;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SineWaveTest::runningChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SineWaveTest::sampleRateChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SineWaveTest::bufferUsageChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SineWaveTest::samplesReady(const QVariantList & _t1, const QVariantList & _t2, const QVariantList & _t3, const QVariantList & _t4, const QVariantList & _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP

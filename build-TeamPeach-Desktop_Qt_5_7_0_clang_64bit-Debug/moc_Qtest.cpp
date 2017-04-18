/****************************************************************************
** Meta object code from reading C++ file 'Qtest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/tests/Qtest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Qtest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QTestCSVReader_t {
    QByteArrayData data[11];
    char stringdata0[196];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QTestCSVReader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QTestCSVReader_t qt_meta_stringdata_QTestCSVReader = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QTestCSVReader"
QT_MOC_LITERAL(1, 15, 19), // "QCSV_READER_TEST_01"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 19), // "QCSV_READER_TEST_02"
QT_MOC_LITERAL(4, 56, 19), // "QCSV_READER_TEST_03"
QT_MOC_LITERAL(5, 76, 19), // "QCSV_READER_TEST_04"
QT_MOC_LITERAL(6, 96, 19), // "QCSV_READER_TEST_05"
QT_MOC_LITERAL(7, 116, 19), // "QCSV_READER_TEST_06"
QT_MOC_LITERAL(8, 136, 19), // "QCSV_READER_TEST_07"
QT_MOC_LITERAL(9, 156, 19), // "QCSV_READER_TEST_08"
QT_MOC_LITERAL(10, 176, 19) // "QCSV_READER_TEST_09"

    },
    "QTestCSVReader\0QCSV_READER_TEST_01\0\0"
    "QCSV_READER_TEST_02\0QCSV_READER_TEST_03\0"
    "QCSV_READER_TEST_04\0QCSV_READER_TEST_05\0"
    "QCSV_READER_TEST_06\0QCSV_READER_TEST_07\0"
    "QCSV_READER_TEST_08\0QCSV_READER_TEST_09"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTestCSVReader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QTestCSVReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTestCSVReader *_t = static_cast<QTestCSVReader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->QCSV_READER_TEST_01(); break;
        case 1: _t->QCSV_READER_TEST_02(); break;
        case 2: _t->QCSV_READER_TEST_03(); break;
        case 3: _t->QCSV_READER_TEST_04(); break;
        case 4: _t->QCSV_READER_TEST_05(); break;
        case 5: _t->QCSV_READER_TEST_06(); break;
        case 6: _t->QCSV_READER_TEST_07(); break;
        case 7: _t->QCSV_READER_TEST_08(); break;
        case 8: _t->QCSV_READER_TEST_09(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject QTestCSVReader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QTestCSVReader.data,
      qt_meta_data_QTestCSVReader,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QTestCSVReader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTestCSVReader::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QTestCSVReader.stringdata0))
        return static_cast<void*>(const_cast< QTestCSVReader*>(this));
    return QObject::qt_metacast(_clname);
}

int QTestCSVReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
struct qt_meta_stringdata_QTestSortList_t {
    QByteArrayData data[5];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QTestSortList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QTestSortList_t qt_meta_stringdata_QTestSortList = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QTestSortList"
QT_MOC_LITERAL(1, 14, 13), // "QSORT_LIST_01"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 13), // "QSORT_LIST_02"
QT_MOC_LITERAL(4, 43, 13) // "QSORT_LIST_03"

    },
    "QTestSortList\0QSORT_LIST_01\0\0QSORT_LIST_02\0"
    "QSORT_LIST_03"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTestSortList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QTestSortList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTestSortList *_t = static_cast<QTestSortList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->QSORT_LIST_01(); break;
        case 1: _t->QSORT_LIST_02(); break;
        case 2: _t->QSORT_LIST_03(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject QTestSortList::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QTestSortList.data,
      qt_meta_data_QTestSortList,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QTestSortList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTestSortList::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QTestSortList.stringdata0))
        return static_cast<void*>(const_cast< QTestSortList*>(this));
    return QObject::qt_metacast(_clname);
}

int QTestSortList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

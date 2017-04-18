/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/gui/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[66];
    char stringdata0[1649];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 9), // "load_file"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 25), // "on_pres_load_file_clicked"
QT_MOC_LITERAL(4, 48, 24), // "on_pub_load_file_clicked"
QT_MOC_LITERAL(5, 73, 25), // "on_fund_load_file_clicked"
QT_MOC_LITERAL(6, 99, 26), // "on_teach_load_file_clicked"
QT_MOC_LITERAL(7, 126, 25), // "on_teach_new_sort_clicked"
QT_MOC_LITERAL(8, 152, 23), // "on_pub_new_sort_clicked"
QT_MOC_LITERAL(9, 176, 24), // "on_pres_new_sort_clicked"
QT_MOC_LITERAL(10, 201, 24), // "on_fund_new_sort_clicked"
QT_MOC_LITERAL(11, 226, 28), // "on_actionLoad_file_triggered"
QT_MOC_LITERAL(12, 255, 23), // "on_FromDate_dateChanged"
QT_MOC_LITERAL(13, 279, 4), // "date"
QT_MOC_LITERAL(14, 284, 21), // "on_ToDate_dateChanged"
QT_MOC_LITERAL(15, 306, 7), // "refresh"
QT_MOC_LITERAL(16, 314, 8), // "tabIndex"
QT_MOC_LITERAL(17, 323, 33), // "on_teach_sort_currentIndexCha..."
QT_MOC_LITERAL(18, 357, 5), // "index"
QT_MOC_LITERAL(19, 363, 31), // "on_pub_sort_currentIndexChanged"
QT_MOC_LITERAL(20, 395, 32), // "on_pres_sort_currentIndexChanged"
QT_MOC_LITERAL(21, 428, 32), // "on_fund_sort_currentIndexChanged"
QT_MOC_LITERAL(22, 461, 28), // "on_teach_delete_sort_clicked"
QT_MOC_LITERAL(23, 490, 26), // "on_pub_delete_sort_clicked"
QT_MOC_LITERAL(24, 517, 27), // "on_pres_delete_sort_clicked"
QT_MOC_LITERAL(25, 545, 27), // "on_fund_delete_sort_clicked"
QT_MOC_LITERAL(26, 573, 27), // "on_teach_pie_button_toggled"
QT_MOC_LITERAL(27, 601, 27), // "on_teach_bar_button_toggled"
QT_MOC_LITERAL(28, 629, 28), // "on_teach_line_button_toggled"
QT_MOC_LITERAL(29, 658, 31), // "on_teach_scatter_button_toggled"
QT_MOC_LITERAL(30, 690, 25), // "on_pub_pie_button_toggled"
QT_MOC_LITERAL(31, 716, 25), // "on_pub_bar_button_toggled"
QT_MOC_LITERAL(32, 742, 26), // "on_pub_line_button_toggled"
QT_MOC_LITERAL(33, 769, 29), // "on_pub_scatter_button_toggled"
QT_MOC_LITERAL(34, 799, 26), // "on_pres_pie_button_toggled"
QT_MOC_LITERAL(35, 826, 26), // "on_pres_bar_button_toggled"
QT_MOC_LITERAL(36, 853, 27), // "on_pres_line_button_toggled"
QT_MOC_LITERAL(37, 881, 30), // "on_pres_scatter_button_toggled"
QT_MOC_LITERAL(38, 912, 26), // "on_fund_pie_button_toggled"
QT_MOC_LITERAL(39, 939, 26), // "on_fund_bar_button_toggled"
QT_MOC_LITERAL(40, 966, 27), // "on_fund_line_button_toggled"
QT_MOC_LITERAL(41, 994, 30), // "on_fund_scatter_button_toggled"
QT_MOC_LITERAL(42, 1025, 24), // "on_teachTreeView_clicked"
QT_MOC_LITERAL(43, 1050, 22), // "on_pubTreeView_clicked"
QT_MOC_LITERAL(44, 1073, 23), // "on_presTreeView_clicked"
QT_MOC_LITERAL(45, 1097, 23), // "on_fundTreeView_clicked"
QT_MOC_LITERAL(46, 1121, 29), // "on_categoryTab_currentChanged"
QT_MOC_LITERAL(47, 1151, 32), // "on_teach_filter_from_textChanged"
QT_MOC_LITERAL(48, 1184, 30), // "on_teach_filter_to_textChanged"
QT_MOC_LITERAL(49, 1215, 30), // "on_pub_filter_from_textChanged"
QT_MOC_LITERAL(50, 1246, 28), // "on_pub_filter_to_textChanged"
QT_MOC_LITERAL(51, 1275, 31), // "on_pres_filter_from_textChanged"
QT_MOC_LITERAL(52, 1307, 29), // "on_pres_filter_to_textChanged"
QT_MOC_LITERAL(53, 1337, 31), // "on_fund_filter_from_textChanged"
QT_MOC_LITERAL(54, 1369, 29), // "on_fund_filter_to_textChanged"
QT_MOC_LITERAL(55, 1399, 27), // "on_teachPrintButton_clicked"
QT_MOC_LITERAL(56, 1427, 26), // "on_fundPrintButton_clicked"
QT_MOC_LITERAL(57, 1454, 26), // "on_presPrintButton_clicked"
QT_MOC_LITERAL(58, 1481, 25), // "on_pubPrintButton_clicked"
QT_MOC_LITERAL(59, 1507, 28), // "on_teachExportButton_clicked"
QT_MOC_LITERAL(60, 1536, 27), // "on_fundExportButton_clicked"
QT_MOC_LITERAL(61, 1564, 27), // "on_presExportButton_clicked"
QT_MOC_LITERAL(62, 1592, 26), // "on_pubExportButton_clicked"
QT_MOC_LITERAL(63, 1619, 10), // "closeEvent"
QT_MOC_LITERAL(64, 1630, 12), // "QCloseEvent*"
QT_MOC_LITERAL(65, 1643, 5) // "event"

    },
    "MainWindow\0load_file\0\0on_pres_load_file_clicked\0"
    "on_pub_load_file_clicked\0"
    "on_fund_load_file_clicked\0"
    "on_teach_load_file_clicked\0"
    "on_teach_new_sort_clicked\0"
    "on_pub_new_sort_clicked\0"
    "on_pres_new_sort_clicked\0"
    "on_fund_new_sort_clicked\0"
    "on_actionLoad_file_triggered\0"
    "on_FromDate_dateChanged\0date\0"
    "on_ToDate_dateChanged\0refresh\0tabIndex\0"
    "on_teach_sort_currentIndexChanged\0"
    "index\0on_pub_sort_currentIndexChanged\0"
    "on_pres_sort_currentIndexChanged\0"
    "on_fund_sort_currentIndexChanged\0"
    "on_teach_delete_sort_clicked\0"
    "on_pub_delete_sort_clicked\0"
    "on_pres_delete_sort_clicked\0"
    "on_fund_delete_sort_clicked\0"
    "on_teach_pie_button_toggled\0"
    "on_teach_bar_button_toggled\0"
    "on_teach_line_button_toggled\0"
    "on_teach_scatter_button_toggled\0"
    "on_pub_pie_button_toggled\0"
    "on_pub_bar_button_toggled\0"
    "on_pub_line_button_toggled\0"
    "on_pub_scatter_button_toggled\0"
    "on_pres_pie_button_toggled\0"
    "on_pres_bar_button_toggled\0"
    "on_pres_line_button_toggled\0"
    "on_pres_scatter_button_toggled\0"
    "on_fund_pie_button_toggled\0"
    "on_fund_bar_button_toggled\0"
    "on_fund_line_button_toggled\0"
    "on_fund_scatter_button_toggled\0"
    "on_teachTreeView_clicked\0"
    "on_pubTreeView_clicked\0on_presTreeView_clicked\0"
    "on_fundTreeView_clicked\0"
    "on_categoryTab_currentChanged\0"
    "on_teach_filter_from_textChanged\0"
    "on_teach_filter_to_textChanged\0"
    "on_pub_filter_from_textChanged\0"
    "on_pub_filter_to_textChanged\0"
    "on_pres_filter_from_textChanged\0"
    "on_pres_filter_to_textChanged\0"
    "on_fund_filter_from_textChanged\0"
    "on_fund_filter_to_textChanged\0"
    "on_teachPrintButton_clicked\0"
    "on_fundPrintButton_clicked\0"
    "on_presPrintButton_clicked\0"
    "on_pubPrintButton_clicked\0"
    "on_teachExportButton_clicked\0"
    "on_fundExportButton_clicked\0"
    "on_presExportButton_clicked\0"
    "on_pubExportButton_clicked\0closeEvent\0"
    "QCloseEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      59,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  309,    2, 0x08 /* Private */,
       3,    0,  310,    2, 0x08 /* Private */,
       4,    0,  311,    2, 0x08 /* Private */,
       5,    0,  312,    2, 0x08 /* Private */,
       6,    0,  313,    2, 0x08 /* Private */,
       7,    0,  314,    2, 0x08 /* Private */,
       8,    0,  315,    2, 0x08 /* Private */,
       9,    0,  316,    2, 0x08 /* Private */,
      10,    0,  317,    2, 0x08 /* Private */,
      11,    0,  318,    2, 0x08 /* Private */,
      12,    1,  319,    2, 0x08 /* Private */,
      14,    1,  322,    2, 0x08 /* Private */,
      15,    1,  325,    2, 0x08 /* Private */,
      17,    1,  328,    2, 0x08 /* Private */,
      19,    1,  331,    2, 0x08 /* Private */,
      20,    1,  334,    2, 0x08 /* Private */,
      21,    1,  337,    2, 0x08 /* Private */,
      22,    0,  340,    2, 0x08 /* Private */,
      23,    0,  341,    2, 0x08 /* Private */,
      24,    0,  342,    2, 0x08 /* Private */,
      25,    0,  343,    2, 0x08 /* Private */,
      26,    0,  344,    2, 0x08 /* Private */,
      27,    0,  345,    2, 0x08 /* Private */,
      28,    0,  346,    2, 0x08 /* Private */,
      29,    0,  347,    2, 0x08 /* Private */,
      30,    0,  348,    2, 0x08 /* Private */,
      31,    0,  349,    2, 0x08 /* Private */,
      32,    0,  350,    2, 0x08 /* Private */,
      33,    0,  351,    2, 0x08 /* Private */,
      34,    0,  352,    2, 0x08 /* Private */,
      35,    0,  353,    2, 0x08 /* Private */,
      36,    0,  354,    2, 0x08 /* Private */,
      37,    0,  355,    2, 0x08 /* Private */,
      38,    0,  356,    2, 0x08 /* Private */,
      39,    0,  357,    2, 0x08 /* Private */,
      40,    0,  358,    2, 0x08 /* Private */,
      41,    0,  359,    2, 0x08 /* Private */,
      42,    1,  360,    2, 0x08 /* Private */,
      43,    1,  363,    2, 0x08 /* Private */,
      44,    1,  366,    2, 0x08 /* Private */,
      45,    1,  369,    2, 0x08 /* Private */,
      46,    0,  372,    2, 0x08 /* Private */,
      47,    0,  373,    2, 0x08 /* Private */,
      48,    0,  374,    2, 0x08 /* Private */,
      49,    0,  375,    2, 0x08 /* Private */,
      50,    0,  376,    2, 0x08 /* Private */,
      51,    0,  377,    2, 0x08 /* Private */,
      52,    0,  378,    2, 0x08 /* Private */,
      53,    0,  379,    2, 0x08 /* Private */,
      54,    0,  380,    2, 0x08 /* Private */,
      55,    0,  381,    2, 0x08 /* Private */,
      56,    0,  382,    2, 0x08 /* Private */,
      57,    0,  383,    2, 0x08 /* Private */,
      58,    0,  384,    2, 0x08 /* Private */,
      59,    0,  385,    2, 0x08 /* Private */,
      60,    0,  386,    2, 0x08 /* Private */,
      61,    0,  387,    2, 0x08 /* Private */,
      62,    0,  388,    2, 0x08 /* Private */,
      63,    1,  389,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,   13,
    QMetaType::Void, QMetaType::QDate,   13,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   18,
    QMetaType::Void, QMetaType::QModelIndex,   18,
    QMetaType::Void, QMetaType::QModelIndex,   18,
    QMetaType::Void, QMetaType::QModelIndex,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 64,   65,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QString _r = _t->load_file();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: _t->on_pres_load_file_clicked(); break;
        case 2: _t->on_pub_load_file_clicked(); break;
        case 3: _t->on_fund_load_file_clicked(); break;
        case 4: _t->on_teach_load_file_clicked(); break;
        case 5: _t->on_teach_new_sort_clicked(); break;
        case 6: _t->on_pub_new_sort_clicked(); break;
        case 7: _t->on_pres_new_sort_clicked(); break;
        case 8: _t->on_fund_new_sort_clicked(); break;
        case 9: _t->on_actionLoad_file_triggered(); break;
        case 10: _t->on_FromDate_dateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 11: _t->on_ToDate_dateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 12: _t->refresh((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_teach_sort_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_pub_sort_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_pres_sort_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_fund_sort_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->on_teach_delete_sort_clicked(); break;
        case 18: _t->on_pub_delete_sort_clicked(); break;
        case 19: _t->on_pres_delete_sort_clicked(); break;
        case 20: _t->on_fund_delete_sort_clicked(); break;
        case 21: _t->on_teach_pie_button_toggled(); break;
        case 22: _t->on_teach_bar_button_toggled(); break;
        case 23: _t->on_teach_line_button_toggled(); break;
        case 24: _t->on_teach_scatter_button_toggled(); break;
        case 25: _t->on_pub_pie_button_toggled(); break;
        case 26: _t->on_pub_bar_button_toggled(); break;
        case 27: _t->on_pub_line_button_toggled(); break;
        case 28: _t->on_pub_scatter_button_toggled(); break;
        case 29: _t->on_pres_pie_button_toggled(); break;
        case 30: _t->on_pres_bar_button_toggled(); break;
        case 31: _t->on_pres_line_button_toggled(); break;
        case 32: _t->on_pres_scatter_button_toggled(); break;
        case 33: _t->on_fund_pie_button_toggled(); break;
        case 34: _t->on_fund_bar_button_toggled(); break;
        case 35: _t->on_fund_line_button_toggled(); break;
        case 36: _t->on_fund_scatter_button_toggled(); break;
        case 37: _t->on_teachTreeView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 38: _t->on_pubTreeView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 39: _t->on_presTreeView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 40: _t->on_fundTreeView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 41: _t->on_categoryTab_currentChanged(); break;
        case 42: _t->on_teach_filter_from_textChanged(); break;
        case 43: _t->on_teach_filter_to_textChanged(); break;
        case 44: _t->on_pub_filter_from_textChanged(); break;
        case 45: _t->on_pub_filter_to_textChanged(); break;
        case 46: _t->on_pres_filter_from_textChanged(); break;
        case 47: _t->on_pres_filter_to_textChanged(); break;
        case 48: _t->on_fund_filter_from_textChanged(); break;
        case 49: _t->on_fund_filter_to_textChanged(); break;
        case 50: _t->on_teachPrintButton_clicked(); break;
        case 51: _t->on_fundPrintButton_clicked(); break;
        case 52: _t->on_presPrintButton_clicked(); break;
        case 53: _t->on_pubPrintButton_clicked(); break;
        case 54: _t->on_teachExportButton_clicked(); break;
        case 55: _t->on_fundExportButton_clicked(); break;
        case 56: _t->on_presExportButton_clicked(); break;
        case 57: _t->on_pubExportButton_clicked(); break;
        case 58: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 59)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 59;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 59)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 59;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

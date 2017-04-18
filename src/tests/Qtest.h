#include <QtTest/QtTest>
#include <QWidget>
#include <QApplication>
#include <QtGui>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "gui/mainwindow.h"
#include "../database/CSVReader.h"
#include "../database/QSortListIO.h"

using namespace std;

class QTestCSVReader: public QObject
{
    Q_OBJECT
private slots:
    void QCSV_READER_TEST_01();
    void QCSV_READER_TEST_02();
    void QCSV_READER_TEST_03();
    void QCSV_READER_TEST_04();
    void QCSV_READER_TEST_05();
    void QCSV_READER_TEST_06();
    void QCSV_READER_TEST_07();
    void QCSV_READER_TEST_08();
    void QCSV_READER_TEST_09();
};

class QTestSortList: public QObject
{
    Q_OBJECT
private slots:
    void QSORT_LIST_01();
    void QSORT_LIST_02();
    void QSORT_LIST_03();
};

